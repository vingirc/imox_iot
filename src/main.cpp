#include "config.h"
#include "ui/ui.h"
#include <Arduino.h>
#include <LV_Helper.h> // Necesario si usas la versión de la librería que requiere helper
#include <LilyGo_AMOLED.h>
#include <PZEM004Tv30.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Preferences.h>
#include <NimBLEDevice.h>
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

// Historial para Gráficas (7 puntos para semanal, 24 para diario)
lv_coord_t history_voltage[7] = {0};
lv_coord_t history_watts[7] = {0};
lv_coord_t history_daily_24h[24] = {0};
bool history_data_ready = false;

esp_mqtt_client_handle_t mqtt_client = NULL;
bool mqtt_connected = false;
bool wifi_enabled_by_user = true; // Rastrea si el WiFi debería estar activo
RTC_DATA_ATTR bool mqtt_sync_ever_happened = false;
RTC_DATA_ATTR unsigned long last_mqtt_sync_ms = 0; // Tiempo de la última sincronización Cloud exitosa
unsigned long boot_time_offset_ms = 0; // Offset para manejar reinicios
unsigned long last_activity_ms = 0;    // Rastrea el último toque en pantalla
uint32_t dim_timeout_s = 30;           // Tiempo para atenuar (default 30s)
uint32_t off_timeout_s = 60;           // Tiempo para apagar (default 60s)
bool burnout_enabled = true;           // Switch maestro de protección
bool is_dimmed = false;
bool is_screen_off = false;
uint8_t user_brightness = UI_BRIGHTNESS_DEFAULT; // Brillo elegido por el usuario

TaskHandle_t SensorTask; // Handle para la tarea del sensor
TaskHandle_t ProvisionTask; // Handle para la tarea de provisioning BLE

LilyGo_Class amoled;

// --- WiFi Activo (cargado desde NVS o config.h) ---
String active_wifi_ssid = WIFI_SSID;
String active_wifi_pass = WIFI_PASSWORD;

// --- BLE Globals ---
NimBLEServer* pBLEServer = nullptr;
NimBLECharacteristic* pNotifyChar = nullptr;
bool ble_client_connected = false;

// Estructura para comunicación BLE -> Provisioning Task (via FreeRTOS Queue)
struct ProvisioningRequest {
  char ssid[64];
  char password[64];
  int userId;
};
QueueHandle_t provQueue = NULL; // Cola de 1 elemento

// --- Funciones MQTT ---
static void mqtt_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data) {
    esp_mqtt_event_handle_t event = (esp_mqtt_event_handle_t)event_data;
    switch ((esp_mqtt_event_id_t)event_id) {
        case MQTT_EVENT_CONNECTED:
            Serial.printf("MQTT: Conectado al Broker (WSS) en %s\n", MQTT_WSS_URI);
            mqtt_connected = true;
            // Suscribirse a tópicos de respuesta
            esp_mqtt_client_subscribe(mqtt_client, MQTT_TOPIC_HISTORY_RES, 1);
            Serial.println("MQTT: Suscrito a historia/response");
            break;
        case MQTT_EVENT_DISCONNECTED:
            Serial.println("MQTT: Desconectado");
            mqtt_connected = false;
            break;
        case MQTT_EVENT_DATA: {
            Serial.printf("MQTT: Datos recibidos en tópico: %.*s\n", event->topic_len, event->topic);
            if (strncmp(event->topic, MQTT_TOPIC_HISTORY_RES, event->topic_len) == 0) {
                JsonDocument doc;
                DeserializationError error = deserializeJson(doc, event->data, event->data_len);
                if (!error) {
                    if (!doc["data"].isNull()) {
                        JsonArray dataRows = doc["data"];
                        JsonArray columns = doc["columns"];
                        
                        // Encontrar índices de columnas
                        int idx_v = -1, idx_p = -1, idx_t = -1;
                        for(int i=0; i<columns.size(); i++) {
                            if(strcmp(columns[i], "voltaje") == 0) idx_v = i;
                            if(strcmp(columns[i], "potencia") == 0) idx_p = i;
                            if(strcmp(columns[i], "timestamp") == 0) idx_t = i;
                        }

                        // Llenar arrays (asumiendo que vienen en orden cronológico)
                        int count = dataRows.size();
                        for(int i=0; i < count; i++) {
                            if (i < 7) {
                              if(idx_v != -1) history_voltage[i] = (lv_coord_t)dataRows[i][idx_v].as<float>();
                              if(idx_p != -1) history_watts[i] = (lv_coord_t)dataRows[i][idx_p].as<float>();
                            }
                            if (i < 24) {
                              if(idx_p != -1) history_daily_24h[i] = (lv_coord_t)dataRows[i][idx_p].as<float>();
                            }
                        }
                        history_data_ready = true;
                        Serial.println("MQTT: Historial procesado correctamente");
                    } else if (!doc["error"].isNull()) {
                        Serial.printf("MQTT: Error de servidor: %s\n", doc["error"].as<const char*>());
                    }
                } else {
                    Serial.println("MQTT: Error al parsear JSON de historial");
                }
            }
            break;
        }
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

// ================================================================
// BLE: Funciones y Callbacks
// ================================================================

// Envía una notificación JSON al cliente BLE (App Móvil)
void sendBLENotification(const char* status, const char* message) {
  if (!pNotifyChar || !ble_client_connected) return;
  JsonDocument doc;
  doc["status"] = status;
  doc["message"] = message;
  char buf[256];
  serializeJson(doc, buf);
  pNotifyChar->setValue((uint8_t*)buf, strlen(buf));
  pNotifyChar->notify();
  Serial.printf("BLE: Notificación -> %s\n", buf);
}

// Callbacks del servidor BLE
class BLEServerCB : public NimBLEServerCallbacks {
  void onConnect(NimBLEServer* server) override {
    ble_client_connected = true;
    Serial.println("BLE: Cliente conectado");
  }
  void onDisconnect(NimBLEServer* server) override {
    ble_client_connected = false;
    Serial.println("BLE: Cliente desconectado");
    NimBLEDevice::startAdvertising(); // Re-habilitar advertising
  }
};

// Callback cuando la App escribe datos en la característica BLE
// Espera JSON: {"ssid": "...", "password": "...", "userId": 1}
class BLEWriteCB : public NimBLECharacteristicCallbacks {
  void onWrite(NimBLECharacteristic* pChar) override {
    std::string val = pChar->getValue();
    Serial.printf("BLE: Recibidos %d bytes\n", val.length());

    JsonDocument doc;
    DeserializationError err = deserializeJson(doc, val.c_str());
    if (err) {
      Serial.printf("BLE: Error JSON: %s\n", err.c_str());
      sendBLENotification("error", "JSON invalido");
      return;
    }

    ProvisioningRequest req;
    strlcpy(req.ssid, doc["ssid"] | "", sizeof(req.ssid));
    strlcpy(req.password, doc["password"] | "", sizeof(req.password));
    req.userId = doc["userId"] | 0;

    // Validar campos requeridos
    if (strlen(req.ssid) == 0 || req.userId == 0) {
      sendBLENotification("error", "Campos ssid y userId son requeridos");
      return;
    }

    // Enviar a la cola (no bloqueante)
    if (xQueueSend(provQueue, &req, 0) != pdTRUE) {
      sendBLENotification("error", "Provisioning en progreso, espere");
      return;
    }

    Serial.printf("BLE: Provisioning solicitado - SSID: %s, Pass: %s, UserID: %d\n",
                  req.ssid, req.password, req.userId);
    sendBLENotification("progress", "Solicitud recibida, procesando...");
  }
};

// Inicialización del servidor BLE
void setupBLE() {
  // Nombre único: IMOX-0003 (basado en el MQTT_IOT_ID)
  char bleName[16];
  snprintf(bleName, sizeof(bleName), "%s-%04d", BLE_DEVICE_PREFIX, MQTT_IOT_ID);

  NimBLEDevice::init(bleName);
  NimBLEDevice::setPower(ESP_PWR_LVL_P9); // Potencia máxima BLE

  pBLEServer = NimBLEDevice::createServer();
  pBLEServer->setCallbacks(new BLEServerCB());

  NimBLEService* pService = pBLEServer->createService(BLE_SERVICE_UUID);

  // Característica de escritura: App -> IoT (recibe credenciales)
  NimBLECharacteristic* pWriteChar = pService->createCharacteristic(
    BLE_CHAR_WRITE_UUID,
    NIMBLE_PROPERTY::WRITE
  );
  pWriteChar->setCallbacks(new BLEWriteCB());

  // Característica de notificación: IoT -> App (envía estado)
  pNotifyChar = pService->createCharacteristic(
    BLE_CHAR_NOTIFY_UUID,
    NIMBLE_PROPERTY::NOTIFY | NIMBLE_PROPERTY::READ
  );

  pService->start();

  // Configurar advertising
  NimBLEAdvertising* pAdv = NimBLEDevice::getAdvertising();
  pAdv->addServiceUUID(pService->getUUID());
  pAdv->setScanResponse(true);
  pAdv->start();

  Serial.printf("BLE: Servidor '%s' iniciado y anunciando\n", bleName);
}

// ================================================================
// PROVISIONING TASK (Core 0) - Maneja vinculación WiFi + API
// ================================================================
void provisioningTaskCode(void* pvParameters) {
  Serial.printf("ProvisioningTask corriendo en núcleo: %d\n", xPortGetCoreID());

  ProvisioningRequest req;

  for (;;) {
    // Esperar hasta que llegue una solicitud por la cola (bloquea hasta 500ms)
    if (xQueueReceive(provQueue, &req, pdMS_TO_TICKS(500)) == pdTRUE) {
      Serial.printf("Provisioning: Iniciando - SSID: %s, Pass: %s, UserID: %d\n", req.ssid, req.password, req.userId);
      sendBLENotification("progress", "Conectando al WiFi...");

      // --- PASO 1: Conectar al WiFi proporcionado ---
      WiFi.disconnect(true);
      vTaskDelay(pdMS_TO_TICKS(1000));
      WiFi.begin(req.ssid, req.password);

      unsigned long startMs = millis();
      while (WiFi.status() != WL_CONNECTED && millis() - startMs < 15000) {
        vTaskDelay(pdMS_TO_TICKS(500));
        Serial.print(".");
      }
      Serial.println();

      if (WiFi.status() != WL_CONNECTED) {
        Serial.println("Provisioning: WiFi FALLÓ - timeout");
        sendBLENotification("error", "No se pudo conectar al WiFi");
        // Reconectar al WiFi anterior
        if (active_wifi_ssid.length() > 0) {
          WiFi.begin(active_wifi_ssid.c_str(), active_wifi_pass.c_str());
        }
        continue;
      }

      Serial.printf("Provisioning: WiFi OK - IP: %s\n", WiFi.localIP().toString().c_str());
      sendBLENotification("progress", "Registrando dispositivo en la nube...");

      // --- PASO 2: POST /iot/link ---
      WiFiClientSecure secureClient;
      secureClient.setCACert(LET_S_ENCRYPT_CA);

      HTTPClient http;
      http.begin(secureClient, API_LINK_URL);
      http.addHeader("Content-Type", "application/json");
      http.setTimeout(10000);

      // Construir payload: {macAddress, deviceSecret, userId}
      JsonDocument linkDoc;
      linkDoc["macAddress"] = WiFi.macAddress();
      linkDoc["deviceSecret"] = MQTT_DEVICE_SECRET;
      linkDoc["userId"] = req.userId;

      char payload[256];
      serializeJson(linkDoc, payload);
      Serial.printf("Provisioning: POST %s -> %s\n", API_LINK_URL, payload);

      int httpCode = http.POST(payload);
      String response = http.getString();
      http.end();

      Serial.printf("Provisioning: HTTP %d - %s\n", httpCode, response.c_str());

      if (httpCode == 200) {
        // --- ÉXITO: Guardar credenciales en NVS ---
        sendBLENotification("success", "Dispositivo vinculado correctamente");

        active_wifi_ssid = String(req.ssid);
        active_wifi_pass = String(req.password);

        Preferences prefs;
        prefs.begin("wifi", false);
        prefs.putString("ssid", active_wifi_ssid);
        prefs.putString("pass", active_wifi_pass);
        prefs.end();
        Serial.println("Provisioning: Credenciales WiFi guardadas en NVS");
        // MQTT se reconectará automáticamente al detectar WiFi activo
      } else {
        // --- ERROR: Informar y reconectar WiFi anterior ---
        char errMsg[128];
        snprintf(errMsg, sizeof(errMsg), "Error del servidor: HTTP %d", httpCode);
        sendBLENotification("error", errMsg);
        if (active_wifi_ssid.length() > 0) {
          WiFi.begin(active_wifi_ssid.c_str(), active_wifi_pass.c_str());
        }
      }
    }
  }
}

void setup() {
  Serial.begin(SERIAL_BAUD_RATE);
  delay(500);

  // 0. Cargar credenciales WiFi desde NVS (si fueron provisionadas previamente)
  {
    Preferences prefs;
    prefs.begin("wifi", true); // Solo lectura
    if (prefs.isKey("ssid")) {
      active_wifi_ssid = prefs.getString("ssid", WIFI_SSID);
      active_wifi_pass = prefs.getString("pass", WIFI_PASSWORD);
      Serial.printf("WiFi: Credenciales cargadas desde NVS (SSID: %s, Pass: %s)\n", active_wifi_ssid.c_str(), active_wifi_pass.c_str());
    } else {
      Serial.println("WiFi: Usando credenciales por defecto (config.h)");
    }
    prefs.end();

    // Cargar Burnout settings
    prefs.begin("burnout", true);
    burnout_enabled = prefs.getBool("enabled", true);
    dim_timeout_s = prefs.getUInt("dim_s", 30);
    off_timeout_s = prefs.getUInt("off_s", 60);
    user_brightness = prefs.getUChar("bright", UI_BRIGHTNESS_DEFAULT);
    prefs.end();
    Serial.println("Burnout: Configuración cargada desde NVS");
  }

  // 1. Conexión WiFi (No bloqueante pero con espera inicial para MQTT)
  // IMPORTANTE: Inicializar modo Station para levantar el stack TCP/IP (LwIP)
  // de lo contrario, el cliente MQTT crasheará con "tcpip_send_msg_wait_sem"
  WiFi.mode(WIFI_STA);
  
  if (active_wifi_ssid.length() > 0) {
    Serial.printf("Iniciando WiFi para SSID: %s (Pass: %s)...\n", active_wifi_ssid.c_str(), active_wifi_pass.c_str());
    WiFi.setAutoReconnect(true);
    WiFi.begin(active_wifi_ssid.c_str(), active_wifi_pass.c_str());
    
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
  } else {
    Serial.println("WiFi: Sin credenciales (Esperando Provisioning BLE)");
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

  // 5. Inicializar BLE Server (Provisioning)
  provQueue = xQueueCreate(1, sizeof(ProvisioningRequest));
  setupBLE();

  // 6. Crear tarea de Provisioning en Core 0
  xTaskCreatePinnedToCore(provisioningTaskCode,
                          PROV_TASK_NAME,
                          PROV_TASK_STACK_SIZE,
                          NULL,
                          PROV_TASK_PRIORITY,
                          &ProvisionTask,
                          PROV_TASK_CORE);

  // 7. Inicializar temporizador de actividad
  last_activity_ms = millis();
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

  // --- NUEVO: Ocultar botón de WiFi si no hay credenciales ---
  if (ui_wifiBtn) {
    if (active_wifi_ssid.length() == 0) {
        lv_obj_add_flag(ui_wifiBtn, LV_OBJ_FLAG_HIDDEN);
    } else {
        lv_obj_clear_flag(ui_wifiBtn, LV_OBJ_FLAG_HIDDEN);
    }
  }

  // --- NUEVO: Estado de Conexión WiFi ---
  if (ui_elementVal) { // IP Local
    if (!wifi_enabled_by_user) {
        lv_label_set_text(ui_elementVal, "APAGADO");
    } else if (WiFi.status() == WL_CONNECTED) {
        lv_label_set_text(ui_elementVal, WiFi.localIP().toString().c_str());
    } else {
        lv_label_set_text(ui_elementVal, "DESCONECTADO");
    }
  }
  if (ui_elementVal1) { // RSSI
    if (WiFi.status() == WL_CONNECTED) {
        int rssi = WiFi.RSSI();
        lv_label_set_text_fmt(ui_elementVal1, "%d dBm", rssi);
        
        if (ui_rssiBar) {
          // Mapeo: -100 dBm (0%) a -30 dBm (100%)
          int pct = (rssi + 100) * 100 / 70;
          if (pct < 0) pct = 0;
          if (pct > 100) pct = 100;
          lv_bar_set_value(ui_rssiBar, pct, LV_ANIM_OFF);
        }
    } else {
        lv_label_set_text(ui_elementVal1, "--- dBm");
        if (ui_rssiBar) lv_bar_set_value(ui_rssiBar, 0, LV_ANIM_OFF);
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

  // Actualizar gráficas si hay datos nuevos
  if (history_data_ready) {
    if (ui_voltageChart) lv_chart_refresh(ui_voltageChart);
    if (ui_wattsChart) lv_chart_refresh(ui_wattsChart);
    
    // Actualizar paneles de Modo Diario (24h) si el objeto existe
    if (ui_Modo_Diario_24hrs) {
      lv_obj_t* panels[] = {ui_valoresPanel4, ui_valoresPanel5, ui_valoresPanel6, ui_valoresPanel7, ui_valoresPanel8, 
                            ui_valoresPanel10, ui_valoresPanel11, ui_valoresPanel12, ui_valoresPanel13, ui_valoresPanel14};
      // Nota: ui_Modo_Diario_24hrs.c tiene menos paneles que 24 horas, ajustamos a lo que hay
      int num_panels = sizeof(panels) / sizeof(panels[0]);
      for (int i=0; i < num_panels && i < 24; i++) {
        if (panels[i]) {
          // Ajustar altura basado en potencia (ej. max 60px)
          int height = (int)((history_daily_24h[i] * 60) / 25000.0); // Asumiendo 25kW max o algo razonable
          if (height < 2) height = 2;
          if (height > 100) height = 100;
          lv_obj_set_height(panels[i], height);
        }
      }
    }
    
    history_data_ready = false;
  }
}

extern "C" void hw_set_brightness(uint8_t val);
extern void onTurnOffScreen(void);

void loop() {
  // --- Detección de Actividad (User Interaction) ---
  lv_indev_t *indev = lv_indev_get_act();
  if (indev && indev->proc.state == LV_INDEV_STATE_PR) {
    last_activity_ms = millis();
    if (is_screen_off) {
      // De lo restante se encarga el wake_layer en ui_events.c
      // pero actualizamos el estado aquí por seguridad
      is_screen_off = false;
    }
    if (is_dimmed) {
      hw_set_brightness(user_brightness);
      is_dimmed = false;
    }
  }

  // --- Lógica de Burnout (Auto-dim / Auto-off) ---
  if (burnout_enabled && !is_screen_off) {
    unsigned long inactive_time = (millis() - last_activity_ms) / 1000;
    
    if (inactive_time >= off_timeout_s) {
      onTurnOffScreen(); // Llama a la lógica de UI y hardware (apaga)
      is_screen_off = true;
    } 
    else if (inactive_time >= dim_timeout_s && !is_dimmed) {
      hw_set_brightness(20); // Atenuación extrema (20/255)
      is_dimmed = true;
      Serial.println("Burnout: Pantalla atenuada por inactividad");
    }
  }

  // El cliente nativo maneja su propia tarea y reconexión en segundo plano
  
  // --- Gestión de Reconexión WiFi en Segundo Plano ---
  static unsigned long lastWifiCheck = 0;
  if (wifi_enabled_by_user && active_wifi_ssid.length() > 0 && (millis() - lastWifiCheck > 15000)) { // Revisar cada 15 segundos
    if (WiFi.status() != WL_CONNECTED) {
      Serial.println("WiFi: Conexión perdida, reintentando WiFi.begin()...");
      WiFi.begin(active_wifi_ssid.c_str(), active_wifi_pass.c_str());
    }
    lastWifiCheck = millis();
  }

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
void hw_burnout_setup(bool enable, uint32_t dim_s, uint32_t off_s) {
  burnout_enabled = enable;
  dim_timeout_s = dim_s;
  off_timeout_s = off_s;
  last_activity_ms = millis(); // Reset al cambiar config
  
  // Persistir
  Preferences prefs;
  prefs.begin("burnout", false);
  prefs.putBool("enabled", enable);
  prefs.putUInt("dim_s", dim_s);
  prefs.putUInt("off_s", off_s);
  prefs.end();

  Serial.printf("Burnout Config: %s, Dim: %ds, Off: %ds (Persistido)\n", 
                enable ? "ON" : "OFF", dim_s, off_s);
}

void hw_reset_activity(void) {
  last_activity_ms = millis();
}

void hw_set_brightness(uint8_t val) {
  if (!is_dimmed && !is_screen_off) {
      user_brightness = val; // Guardar el brillo deseado por el usuario
      Preferences prefs;
      prefs.begin("burnout", false);
      prefs.putUChar("bright", val);
      prefs.end();
  }
  amoled.setBrightness(val);
  Serial.printf("Brillo ajustado a: %d\n", val);
}

void hw_wifi_toggle(bool enable) {
  wifi_enabled_by_user = enable;
  if (enable) {
    WiFi.mode(WIFI_STA);
    if (active_wifi_ssid.length() > 0) {
      WiFi.begin(active_wifi_ssid.c_str(), active_wifi_pass.c_str());
    }
    Serial.println("WiFi: Activado por el usuario");
  } else {
    WiFi.disconnect(true);
    WiFi.mode(WIFI_OFF);
    Serial.println("WiFi: Desactivado por el usuario (Radio APAGADA)");
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

void hw_request_history(const char* startDate, const char* endDate) {
  if (!mqtt_connected || mqtt_client == NULL) {
    Serial.println("MQTT: No se puede pedir historial (no conectado)");
    return;
  }

  JsonDocument doc;
  doc["startDate"] = startDate;
  doc["endDate"] = endDate;

  char buffer[256];
  serializeJson(doc, buffer);
  
  Serial.printf("MQTT: Pidiendo historial: %s\n", buffer);
  esp_mqtt_client_publish(mqtt_client, MQTT_TOPIC_HISTORY_REQ, buffer, 0, 1, 0);
}

} // extern "C"