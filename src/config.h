/**
 * @file config.h
 * @brief Configuración global del sistema IMOX Cloud
 * @author Equipo de Desarrollo IMOX
 * @date 2024-12-11
 * @version 1.0.0
 * 
 * Este archivo contiene todas las constantes de configuración del sistema.
 * Migrado y adaptado para el proyecto SquareLine UI.
 */

#ifndef CONFIG_H
#define CONFIG_H

// ============================================================================
// INFORMACIÓN DEL DISPOSITIVO
// ============================================================================
#define FIRMWARE_VERSION "1.0.0"
#define DEVICE_MODEL "IMOX-B1"
#define MANUFACTURER "Yex Acoustics"

// ============================================================================
// CONFIGURACIÓN DE HARDWARE - PZEM-004T
// ============================================================================
// Pines definidos para T-Display S3 (conector Qwiic/Extra)
#define PZEM_RX_PIN 44         // ESP32 RX (conectado a PZEM TX)
#define PZEM_TX_PIN 43         // ESP32 TX (conectado a PZEM RX)
#define PZEM_BAUD   9600       // Baudrate fijo del PZEM-004T
#define PZEM_ADDRESS 0x01      // Dirección Modbus del PZEM

// Intervalos de lectura
#define PZEM_READ_INTERVAL_MS 2000  // Leer cada 2 segundos
#define PZEM_TIMEOUT_MS 1000        // Timeout de respuesta UART

// ============================================================================
// CONFIGURACIÓN DE FREERTOS - TASKS
// ============================================================================
// UI Task (Core 1 - dedicado a renderizado, ejecutado en loop())
#define UI_TASK_CORE 1

// PZEM Task (Core 0 - I/O sensor)
#define PZEM_TASK_NAME "PZEMTask"
#define PZEM_TASK_STACK_SIZE 4096
#define PZEM_TASK_PRIORITY 1  
#define PZEM_TASK_CORE 0

// ============================================================================
// CONFIGURACIÓN DE UI - LVGL
// ============================================================================
#define LVGL_TICK_PERIOD_MS 5       // Tick de LVGL cada 5ms

// ============================================================================
// CONFIGURACIÓN DE DEBUGGING
// ============================================================================
#define SERIAL_BAUD_RATE 115200     // Baudrate del monitor serial

#endif // CONFIG_H
