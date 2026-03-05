#include "config.h"
#include "ui/ui.h"
#include <Arduino.h>
#include <LV_Helper.h> // Necesario si usas la versión de la librería que requiere helper
#include <LilyGo_AMOLED.h>
#include <PZEM004Tv30.h>
#include <WiFi.h>
#include <ArduinoJson.h>
#include "mqtt_client.h"
#include "esp_tls.h"

// Definición de pines para UART2 (PZEM) tomados de config.h
#define PZEM_SERIAL Serial2

PZEM004Tv30 pzem(PZEM_SERIAL, PZEM_RX_PIN, PZEM_TX_PIN);

// Variables Globales para compartir datos entre núcleos
// (En el futuro, usa Semáforos/Mutex para protegerlas si hay conflictos de
// escritura/lectura simultánea)
float v_voltage = 0.0;
float v_current = 0.0;
float v_power = 0.0;
float v_energy = 0.0;
float v_frequency = 0.0;
float v_pf = 0.0;

esp_mqtt_client_handle_t mqtt_client = NULL;
bool mqtt_connected = false;
RTC_DATA_ATTR bool mqtt_sync_ever_happened = false;
RTC_DATA_ATTR unsigned long last_mqtt_sync_ms = 0; // Tiempo de la última sincronización Cloud exitosa
unsigned long boot_time_offset_ms = 0; // Offset para manejar reinicios

TaskHandle_t SensorTask; // Handle para la tarea del sensor

LilyGo_Class amoled;

// --- Funciones MQTT ---
static void mqtt_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data) {
    esp_mqtt_event_handle_t event = (esp_mqtt_event_handle_t)event_data;
    switch ((esp_mqtt_event_id_t)event_id) {
        case MQTT_EVENT_CONNECTED:
            Serial.println("MQTT: Conectado al Broker (WSS)");
            mqtt_connected = true;
            break;
        case MQTT_EVENT_DISCONNECTED:
            Serial.println("MQTT: Desconectado");
            mqtt_connected = false;
            break;
        case MQTT_EVENT_ERROR:
            Serial.println("MQTT: Error detectado");
            break;
        default:
            break;
    }
}

void sendTelemetry(float v, float i, float p, float e, float f, float pf) {
  if (!mqtt_connected || mqtt_client == NULL) {
    return;
  }

  JsonDocument doc;
  
  doc["iot_id"] = MQTT_IOT_ID;
  doc["user_id"] = MQTT_USER_ID;

  // Bloque eléctricas
  JsonObject electricas = doc["electricas"].to<JsonObject>();
  electricas["voltaje_v"] = v;
  electricas["corriente_a"] = i;
  electricas["potencia_w"] = p;
  electricas["energia_kwh"] = e;
  electricas["frecuencia_hz"] = f;
  electricas["factor_potencia"] = pf;

  // Bloque diagnóstico
  JsonObject diagnostico = doc["diagnostico"].to<JsonObject>();
  diagnostico["ip"] = WiFi.localIP().toString();
  diagnostico["rssi_dbm"] = WiFi.RSSI();
  diagnostico["pzem_status"] = isnan(v) ? "ERROR" : "OK";
  diagnostico["uptime_s"] = millis() / 1000;

  char buffer[512];
  serializeJson(doc, buffer);
  
  // Imprimir payload en Serial para depuración
  Serial.print("MQTT: Enviando Payload: ");
  Serial.println(buffer);
  
  int msg_id = esp_mqtt_client_publish(mqtt_client, MQTT_TOPIC_TELEMETRY, buffer, 0, 1, 0);
  if (msg_id != -1) {
    Serial.printf("MQTT: Telemetría enviada (ID: %d)\n", msg_id);
    last_mqtt_sync_ms = millis(); // Actualizar tiempo de última sincronización
    mqtt_sync_ever_happened = true;
  } else {
    Serial.println("MQTT: Error al publicar");
  }
}

// --- Tarea del Sensor (Core 0) ---
void sensorTaskCode(void *pvParameters) {
  Serial.print("SensorTask corriendo en el núcleo: ");
  Serial.println(xPortGetCoreID());

  uint8_t startup_skip_count = 0;
  const uint8_t MAX_STARTUP_SKIP =
      2; // Primeras 2 lecturas ignoradas, pues se generan picos falsos al
         // recien conectarse el sensor

  for (;;) {
    // Lee los datos del sensor (esto puede ser bloqueante o tardado, pero no
    // afecta la UI)
    float voltage = pzem.voltage();
    float current = pzem.current();
    float power = pzem.power();
    float energy = pzem.energy();
    float frequency = pzem.frequency();
    float pf = pzem.pf();

    if (!isnan(voltage)) {
      // 1. Filtro de inicialización
      if (startup_skip_count < MAX_STARTUP_SKIP) {
        startup_skip_count++;
        Serial.printf(
            "PZEM: Ignorando lectura válida de estabilización %d/%d...\n",
            startup_skip_count, MAX_STARTUP_SKIP);
        vTaskDelay(pdMS_TO_TICKS(PZEM_READ_INTERVAL_MS));
        continue;
      }

      // 2. Filtro de rango (Outlier Filter)
      bool is_valid = true;
      if (voltage > 450.0 || voltage < 0.0)
        is_valid = false;
      if (current > 100.0 || current < 0.0)
        is_valid = false;
      if (power > 25000.0 || power < 0.0)
        is_valid = false;

      if (is_valid) {
        // Actualizamos variables globales
        v_voltage = voltage;
        v_current = current;
        v_power = power;
        v_energy = energy;
        v_frequency = frequency;
        v_pf = pf;

        Serial.println("===== MEDICIONES PZEM (Core 0) =====");
        Serial.printf("Voltaje: %.2f V\n", voltage);
        Serial.printf("Corriente: %.3f A\n", current);
        Serial.printf("Potencia: %.2f W\n", power);
        Serial.println("===================================");
      } else {
        Serial.println(">>> PZEM SPIKE DETECTED: Lectura ignorada por valores "
                       "fuera de rango <<<");
        Serial.printf("V: %.2f, I: %.2f, P: %.2f\n", voltage, current, power);
      }
    } else {
      v_voltage = NAN; // Indicar error para la pantalla de diagnóstico
      Serial.println("Error leyendo PZEM (NAN)");
    }

    // Espera definida en config.h antes de la siguiente lectura
    vTaskDelay(pdMS_TO_TICKS(PZEM_READ_INTERVAL_MS));

    // Envío de telemetría por MQTT
    static unsigned long lastMQTTSendTime = 0;
    if (millis() - lastMQTTSendTime > TELEMETRY_SEND_INTERVAL_MS) {
      if (startup_skip_count >= MAX_STARTUP_SKIP && !isnan(v_voltage)) {
        sendTelemetry(v_voltage, v_current, v_power, v_energy, v_frequency, v_pf);
      }
      lastMQTTSendTime = millis();
    }
  }
}

void setup() {
  Serial.begin(SERIAL_BAUD_RATE);
  delay(500);

  // 0. Conexión WiFi (No bloqueante pero con espera inicial para MQTT)
  Serial.print("Iniciando WiFi...");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  
  Serial.print(" Esperando conexión...");
  unsigned long start_wifi = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - start_wifi < 10000) {
      delay(500);
      Serial.print(".");
  }

  if (WiFi.status() == WL_CONNECTED) {
      Serial.println(" ¡Conectado!");
      Serial.print("IP: ");
      Serial.println(WiFi.localIP());
  } else {
      Serial.println(" Timeout (conectando en segundo plano)");
  }
  
  // Configuración MQTT Nativa (WSS) - Estructura dinámica por versión
  esp_mqtt_client_config_t mqtt_cfg = {};

#if ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(5, 0, 0)
  // SINTAXIS PARA NÚCLEOS ESP32 NUEVOS (Arduino v3.x / ESP-IDF 5)
  mqtt_cfg.broker.address.uri = MQTT_WSS_URI; 
  mqtt_cfg.credentials.username = "3";
  mqtt_cfg.credentials.authentication.password = MQTT_DEVICE_SECRET;
  mqtt_cfg.credentials.client_id = "IMOX-ESP32-3";
  mqtt_cfg.broker.verification.certificate = LET_S_ENCRYPT_CA;
  
  // Tamaño de buffer
  mqtt_cfg.task.stack_size = 12288;
  mqtt_cfg.buffer.size = 4096;
#else
  // SINTAXIS PARA NÚCLEOS ESP32 CLÁSICOS (Arduino v2.x / ESP-IDF 4.x)
  mqtt_cfg.uri = MQTT_WSS_URI;               
  mqtt_cfg.client_id = "IMOX-ESP32-3";
  mqtt_cfg.username = "3";
  mqtt_cfg.password = MQTT_DEVICE_SECRET;
  mqtt_cfg.cert_pem = LET_S_ENCRYPT_CA;
  
  // Tamaño de buffer
  mqtt_cfg.task_stack = 12288;
  mqtt_cfg.buffer_size = 4096;
#endif

  // Nota: Se omite intencionalmente skip_cert_common_name_check 
  // para permitir que la validación SNI de Tailscale funcione.
  
  mqtt_client = esp_mqtt_client_init(&mqtt_cfg);
  esp_mqtt_client_register_event(mqtt_client, (esp_mqtt_event_id_t)ESP_EVENT_ANY_ID, mqtt_event_handler, NULL);
  esp_mqtt_client_start(mqtt_client);
  Serial.println("MQTT: Cliente Iniciado");

  // 1. Inicia Hardware
  bool res = amoled.begin();
  if (!res) {
    Serial.println("Display error!");
    while (1)
      delay(1000);
  }

  // 2. Inicia LVGL
  beginLvglHelper(amoled);

  // 3. Inicia UI de SquareLine
  ui_init();

  Serial.println("System Ready - UI Running");

  // 4. Crear tarea para el Sensor en el Núcleo 0
  xTaskCreatePinnedToCore(sensorTaskCode,       /* Función de la tarea */
                          PZEM_TASK_NAME,       /* Nombre de la tarea */
                          PZEM_TASK_STACK_SIZE, /* Tamaño del stack (bytes) */
                          NULL,                 /* Parámetros */
                          PZEM_TASK_PRIORITY,   /* Prioridad */
                          &SensorTask,          /* Handle de la tarea */
                          PZEM_TASK_CORE);      /* Núcleo pinned (0) */
}

void updateUI() {
  // Pre-validamos los valores para evitar picos o NAN en la UI
  float display_v = isnan(v_voltage) ? 0.0 : v_voltage;
  float display_i = isnan(v_current) ? 0.0 : v_current;
  float display_p = isnan(v_power) ? 0.0 : v_power;
  float display_e = isnan(v_energy) ? 0.0 : v_energy;
  float display_f = isnan(v_frequency) ? 0.0 : v_frequency;
  float display_pf = isnan(v_pf) ? 0.0 : v_pf;

  // ----------------------------------------------------
  // VISTA 1: VOLTAJE (ui_voltaje)
  // ----------------------------------------------------
  if (ui_voltajeVal) {
    int int_voltage = (int)display_v;
    lv_label_set_text_fmt(ui_voltajeVal, "%d", int_voltage);
    if (ui_voltajeDecimal) {
      lv_label_set_text(ui_voltajeDecimal,
                        ""); // No decimals as per client request
    }
  }
  if (ui_frecuencia) {
    lv_label_set_text_fmt(ui_frecuencia, "%.1f", display_f);
  }
  if (ui_potencia) {
    lv_label_set_text_fmt(ui_potencia, "%.1f", display_p);
  }

  // ----------------------------------------------------
  // VISTA 6: DIAGNÓSTICO (ui_diagnostic)
  // ----------------------------------------------------
  if (ui_elementVal3) { // Uptime
    uint32_t sec = millis() / 1000;
    uint32_t min = sec / 60;
    uint32_t hr = min / 60;
    lv_label_set_text_fmt(ui_elementVal3, "%02d:%02d:%02d", hr, min % 60,
                          sec % 60);
  }

  // --- NUEVO: Estado de Conexión WiFi ---
  if (ui_elementVal) { // IP Local
    if (WiFi.status() == WL_CONNECTED) {
        lv_label_set_text(ui_elementVal, WiFi.localIP().toString().c_str());
    } else {
        lv_label_set_text(ui_elementVal, "DESCONECTADO");
    }
  }
  if (ui_elementVal1) { // RSSI
    if (WiFi.status() == WL_CONNECTED) {
        lv_label_set_text_fmt(ui_elementVal1, "%d dBm", WiFi.RSSI());
    } else {
        lv_label_set_text(ui_elementVal1, "--- dBm");
    }
  }

  // --- NUEVO: Estado de MQTT ---
  if (ui_elementVal4) { // MQTT Broker Status
    if (mqtt_connected) {
        lv_label_set_text(ui_elementVal4, "CONECTADO");
    } else {
        lv_label_set_text(ui_elementVal4, "DESCONECTADO");
    }
  }
  if (ui_elementVal7) { // Last Sync (Cloud)
    if (!mqtt_sync_ever_happened) {
        lv_label_set_text(ui_elementVal7, "NUNCA");
    } else {
        unsigned long current_ms = millis();
        uint32_t diff_s = (current_ms - last_mqtt_sync_ms) / 1000;

        if (diff_s < 5) {
            lv_label_set_text(ui_elementVal7, "AHORA");
        } else if (diff_s < 60) {
            lv_label_set_text_fmt(ui_elementVal7, "HACE %u s", diff_s);
        } else {
            uint32_t diff_m = diff_s / 60;
            lv_label_set_text_fmt(ui_elementVal7, "HACE %u m", diff_m);
        }
    }
  }
  if (ui_elementVal5) { // MAC
    lv_label_set_text(ui_elementVal5, WiFi.macAddress().c_str());
  }
  if (ui_elementVal6) { // PZEM Status
    if (!isnan(v_voltage) && v_voltage > 0) {
      lv_label_set_text(ui_elementVal6, "CONECTADO");
    } else {
      lv_label_set_text(ui_elementVal6, "ERROR / DESCONECTADO");
    }
  }
  if (ui_elementVal8) { // Memory & Core Info
    uint32_t freeHeap = ESP.getFreeHeap() / 1024;
    uint32_t totalHeap = ESP.getHeapSize() / 1024;
    
    // Monitoreo de Stack (High Water Mark en palabras de 4 bytes)
    UBaseType_t sensorStackFree = uxTaskGetStackHighWaterMark(SensorTask);
    UBaseType_t uiStackFree = uxTaskGetStackHighWaterMark(NULL); // Tarea actual (UI/Loop)

    // Abreviado para evitar superposición: Heap | Core | Stacks
    lv_label_set_text_fmt(ui_elementVal8, "H: %uK | C: %d | S: %u/%u", 
                          freeHeap, xPortGetCoreID(), 
                          (uint32_t)uiStackFree, (uint32_t)sensorStackFree);
    
    // Verificación por Serial también
    static unsigned long lastLog = 0;
    if (millis() - lastLog > 5000) {
        Serial.printf("DEBUG: Heap: %uKB, Core: %d, UI_Stack_HWM: %u, Sensor_Stack_HWM: %u\n", 
                      freeHeap, xPortGetCoreID(), (uint32_t)uiStackFree, (uint32_t)sensorStackFree);
        lastLog = millis();
    }
  }

  // ----------------------------------------------------
  // VISTA 2: CORRIENTE (ui_corriente)
  // ----------------------------------------------------
  if (ui_corrienteVal) {
    int int_current = (int)display_i;
    lv_label_set_text_fmt(ui_corrienteVal, "%d.",
                          int_current); // Punto grande para corriente
    if (ui_corrienteDecimal) {
      int dec_current = (int)((display_i - int_current) * 100);
      if (dec_current < 0)
        dec_current = 0;
      lv_label_set_text_fmt(ui_corrienteDecimal, "%02d",
                            dec_current); // Sin punto aquí
    }
  }
  if (ui_pactivaVal) {
    lv_label_set_text_fmt(ui_pactivaVal, "%.1f", display_p);
  }
  if (ui_preactivaVal) {
    // Cálculo aproximado de Reactiva: Q = sqrt(S^2 - P^2)
    // S = V * I
    float apparent = display_v * display_i;
    float reactive = 0.0;
    if (apparent > display_p) {
      reactive = sqrt((apparent * apparent) - (display_p * display_p));
    }
    lv_label_set_text_fmt(ui_preactivaVal, "%.1f", reactive);
  }

  // ----------------------------------------------------
  // VISTA 3: DASHBOARD (ui_dashboard)
  // ----------------------------------------------------
  if (ui_VoltajeValD) {
    lv_label_set_text_fmt(ui_VoltajeValD, "%.0f", display_v);
  }
  if (ui_CorrienteValD) {
    lv_label_set_text_fmt(ui_CorrienteValD, "%.2f", display_i);
  }
  if (ui_pactivaValD) {
    lv_label_set_text_fmt(ui_pactivaValD, "%.0f", display_p);
  }
  if (ui_energiaValD) {
    // Energía en kWh
    lv_label_set_text_fmt(ui_energiaValD, "%.3f", display_e);
  }
  if (ui_frecuenciaValD) {
    lv_label_set_text_fmt(ui_frecuenciaValD, "%.1f", display_f);
  }
  if (ui_PotenciaValD) { // Factor de Potencia según análisis
    lv_label_set_text_fmt(ui_PotenciaValD, "%.2f", display_pf);
  }
}

void loop() {
  // El cliente nativo maneja su propia tarea y reconexión en segundo plano
  
  // 5. Manejador LVGL (Corre en el Núcleo 1, el default de loop())
  lv_task_handler();

  // Actualizar UI periódicamente (ej. cada 500ms)
  // No es necesario hacerlo en cada ciclo de loop
  static unsigned long lastUIUpdate = 0;
  if (millis() - lastUIUpdate > 500) {
    updateUI();
    lastUIUpdate = millis();
  }

  delay(LVGL_TICK_PERIOD_MS);
}

// ================================================================
// HARDWARE BRIDGE: Funciones llamadas desde UI (C-linkage)
// ================================================================
extern "C" {

void hw_set_brightness(uint8_t val) {
  amoled.setBrightness(val);
  Serial.printf("Brillo ajustado a: %d\n", val);
}

void hw_wifi_toggle(bool enable) {
  if (enable) {
    WiFi.reconnect();
    Serial.println("WiFi: Reconectando...");
  } else {
    WiFi.disconnect(true);
    Serial.println("WiFi: Desconectado");
  }
}

void hw_restart(void) {
  Serial.println("Reiniciando dispositivo...");
  
  // Guardamos el "tiempo transcurrido desde la última sincronización" en RTC
  // para que al volver del reinicio, el contador continúe (asumiendo ~1s de reboot)
  if (mqtt_sync_ever_happened) {
      unsigned long elapsed = millis() - last_mqtt_sync_ms;
      // Guardamos como un valor negativo para que al sumarle millis() (que será 0) 
      // dé el tiempo relativo correcto. Sumamos 2000ms por el tiempo de boot.
      last_mqtt_sync_ms = 0 - (elapsed + 2000); 
  }

  delay(500); // Dar tiempo al serial
  ESP.restart();
}

void hw_turn_off_screen(void) {
  amoled.setBrightness(0);
  Serial.println("Pantalla apagada (Brillo 0)");
}

} // extern "C"