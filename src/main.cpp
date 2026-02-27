#include <Arduino.h>
#include <LilyGo_AMOLED.h>
#include <LV_Helper.h> // Necesario si usas la versión de la librería que requiere helper
#include "ui/ui.h" 
#include "config.h" 

#include <PZEM004Tv30.h>

// Definición de pines para UART2 (PZEM) tomados de config.h
#define PZEM_SERIAL Serial2

PZEM004Tv30 pzem(PZEM_SERIAL, PZEM_RX_PIN, PZEM_TX_PIN);

// Variables Globales para compartir datos entre núcleos
// (En el futuro, usa Semáforos/Mutex para protegerlas si hay conflictos de escritura/lectura simultánea)
float v_voltage = 0.0;
float v_current = 0.0;
float v_power = 0.0;
float v_energy = 0.0;
float v_frequency = 0.0;
float v_pf = 0.0;

TaskHandle_t SensorTask; // Handle para la tarea del sensor

LilyGo_Class amoled;

// --- Tarea del Sensor (Core 0) ---
void sensorTaskCode(void * pvParameters) {
    Serial.print("SensorTask corriendo en el núcleo: ");
    Serial.println(xPortGetCoreID());

    for(;;) {
        // Lee los datos del sensor (esto puede ser bloqueante o tardado, pero no afecta la UI)
        float voltage = pzem.voltage();
        float current = pzem.current();
        float power   = pzem.power();
        float energy  = pzem.energy();
        float frequency = pzem.frequency();
        float pf = pzem.pf();

        if (!isnan(voltage)) {
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
            Serial.println("Error leyendo PZEM");
        }
        
        // Espera definidida en config.h antes de la siguiente lectura
        vTaskDelay(pdMS_TO_TICKS(PZEM_READ_INTERVAL_MS));
    }
}

void setup() {
    Serial.begin(SERIAL_BAUD_RATE);
    delay(500);
    
    // 1. Inicia Hardware
    bool res = amoled.begin();
    if (!res) {
        Serial.println("Display error!");
        while(1) delay(1000);
    }
    
    // 2. Inicia LVGL
    beginLvglHelper(amoled);
    
    // 3. Inicia UI de SquareLine
    ui_init();
    
    Serial.println("System Ready - UI Running");

    // 4. Crear tarea para el Sensor en el Núcleo 0
    // xTaskCreatePinnedToCore params:
    // func, name, stack size, params, priority, handle, core_id
    xTaskCreatePinnedToCore(
        sensorTaskCode,   /* Función de la tarea */
        PZEM_TASK_NAME,   /* Nombre de la tarea */
        PZEM_TASK_STACK_SIZE, /* Tamaño del stack (bytes) */
        NULL,             /* Parámetros */
        PZEM_TASK_PRIORITY, /* Prioridad */
        &SensorTask,      /* Handle de la tarea */
        PZEM_TASK_CORE);  /* Núcleo pinned (0) */
}

void updateUI() {
    // ----------------------------------------------------
    // VISTA 1: VOLTAJE (ui_voltaje)
    // ----------------------------------------------------
    if (ui_voltajeVal) {
        int int_voltage = (int)v_voltage;
        lv_label_set_text_fmt(ui_voltajeVal, "%d", int_voltage);
        if (ui_voltajeDecimal) {
            int dec_voltage = (int)((v_voltage - int_voltage) * 100);
            if (dec_voltage < 0) dec_voltage = 0;
            lv_label_set_text_fmt(ui_voltajeDecimal, ".%02d", dec_voltage);
        }
    }
    if (ui_frecuencia) {
        lv_label_set_text_fmt(ui_frecuencia, "%.1f", v_frequency);
    }
    if (ui_potencia) {
        lv_label_set_text_fmt(ui_potencia, "%.1f", v_power);
    }

    // ----------------------------------------------------
    // VISTA 2: CORRIENTE (ui_corriente)
    // ----------------------------------------------------
    if (ui_corrienteVal) {
        int int_current = (int)v_current;
        lv_label_set_text_fmt(ui_corrienteVal, "%d.", int_current); // Punto grande para corriente
        if (ui_corrienteDecimal) {
            int dec_current = (int)((v_current - int_current) * 100);
            if (dec_current < 0) dec_current = 0;
            lv_label_set_text_fmt(ui_corrienteDecimal, "%02d", dec_current); // Sin punto aquí
        }
    }
    if (ui_pactivaVal) {
        lv_label_set_text_fmt(ui_pactivaVal, "%.1f", v_power);
    }
    if (ui_preactivaVal) {
        // Cálculo aproximado de Reactiva: Q = sqrt(S^2 - P^2)
        // S = V * I
        float apparent = v_voltage * v_current;
        float reactive = 0.0;
        if (apparent > v_power) {
            reactive = sqrt((apparent * apparent) - (v_power * v_power));
        }
        lv_label_set_text_fmt(ui_preactivaVal, "%.1f", reactive);
    }

    // ----------------------------------------------------
    // VISTA 3: DASHBOARD (ui_dashboard)
    // ----------------------------------------------------
    if (ui_VoltajeValD) {
        lv_label_set_text_fmt(ui_VoltajeValD, "%.1f", v_voltage);
    }
    if (ui_CorrienteValD) {
        lv_label_set_text_fmt(ui_CorrienteValD, "%.2f", v_current);
    }
    if (ui_pactivaValD) {
        lv_label_set_text_fmt(ui_pactivaValD, "%.0f", v_power);
    }
    if (ui_energiaValD) {
        // Energía en kWh
        lv_label_set_text_fmt(ui_energiaValD, "%.3f", v_energy);
    }
    if (ui_frecuenciaValD) {
        lv_label_set_text_fmt(ui_frecuenciaValD, "%.1f", v_frequency);
    }
    if (ui_PotenciaValD) { // Factor de Potencia según análisis
        lv_label_set_text_fmt(ui_PotenciaValD, "%.2f", v_pf);
    }
}

void loop() {
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
