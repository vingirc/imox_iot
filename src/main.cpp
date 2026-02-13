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

void loop() {
    // 5. Manejador LVGL (Corre en el Núcleo 1, el default de loop())
    lv_task_handler();
    
    // [OPCIONAL] Aquí actualizarías la UI con los valores de las variables globales
    // Ejemplo: ui_set_voltage_text(v_voltage);
    
    delay(LVGL_TICK_PERIOD_MS);
}
