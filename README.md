# IMOX SquareLine UI - Firmware ESP32-S3

![Version](https://img.shields.io/badge/version-1.0.0-blue.svg)
![Platform](https://img.shields.io/badge/platform-ESP32--S3-green.svg)
![License](https://img.shields.io/badge/license-Proprietary-red.svg)
![UI Framework](https://img.shields.io/badge/UI-LVGL_8.3-blueviolet.svg)

> Firmware para el ecosistema IoT de monitoreo de calidad eléctrica **IMOX-B1** de Yex Acoustics. Este repositorio contiene el proyecto UI generado con SquareLine Studio junto con el código fuente del firmware ESP32-S3.

---

## Tabla de Contenidos

- [Descripción](#descripción)
- [Características](#características)
- [Hardware Requerido](#hardware-requerido)
- [Arquitectura del Sistema](#arquitectura-del-sistema)
- [Instalación](#instalación)
- [Configuración](#configuración)
- [Estructura del Proyecto](#estructura-del-proyecto)
- [Desarrollo](#desarrollo)
- [Actualización OTA](#actualización-ota)
- [Documentación](#documentación)

---

## Descripción

El firmware IMOX es el componente Edge del ecosistema IoT propietario de Yex Acoustics para monitoreo de calidad eléctrica en tiempo real. Permite visualización local en pantalla AMOLED táctil de 1.91", conectividad a nube privada vía MQTT WebSocket y provisioning simplificado mediante Bluetooth Low Energy (BLE).

### Diferencias con el Repo Anterior

Este repositorio usa **SquareLine Studio** para el diseño de la interfaz de usuario, separando el diseño visual (archivos `.scj`) del código generado (`.c`/`.h`). El proyecto anterior usaba LVGL directamente sin herramienta visual.

---

## Características

### Interfaz Gráfica (AMOLED Touch)

- **9+ Pantallas navegables por gestos**:
  - Dashboard: Vista principal con todos los parámetros
  - Voltaje: Medición de voltaje con lectura grande
  - Corriente: Corriente en amperes
  - Frecuencia: Lectura de frecuencia (Hz)
  - Diagnóstico: Información de red (IP, RSSI)
  - Estadísticas Voltaje: Gráfico semanal/mensual
  - Estadísticas Watts: Gráfico de consumo
  - Modo Diario 24h: Consumo por hora
  - Configuración: Brillo, protección burn-in, WiFi

- **Optimización AMOLED**: Fondo negro puro para eficiencia energética
- **Protección Burn-in**: 
  - Atenuación automática configurable (10-300 segundos)
  - Apagado de pantalla configurable
  - Pantalla de protección con imagen

### Conectividad

- **WiFi**: Reconexión automática resiliente
- **MQTT over WebSocket**: Publicación de telemetría a broker privado (wss://)
- **BLE**: Provisioning de credenciales WiFi sin servidor local

### Monitoreo Eléctrico

- **Sensor**: PZEM-004T V3.0 (protocolo UART)
- **Variables**: Voltaje, Corriente, Potencia Activa, Frecuencia, Factor de Potencia
- **Intervalo de lectura**: 2 segundos

### Actualización OTA

- Actualizaciones de firmware remotas vía MQTT
- Verificación SHA256 del firmware descargado
- Estados: PENDING → DOWNLOADING → VERIFYING → APPLYING → COMPLETED

### Arquitectura de Software

- **FreeRTOS**: Multitarea (UI, PZEM, MQTT, BLE, OTA)
- **Dual Core ESP32-S3**: Core 1 dedicado a UI, Core 0 para I/O
- **SquareLine Studio**: Diseño visual de UI exportado a código C

---

## Hardware Requerido

| Componente | Modelo | Descripción |
|------------|--------|-------------|
| **MCU** | ESP32-S3 (Dual Core) | Microcontrolador principal |
| **Display** | LilyGo T-Display-S3 AMOLED | Pantalla táctil 1.91" 240×536 px |
| **Sensor** | PZEM-004T V3.0 | Módulo de medición eléctrica |

### Pinout

```
ESP32-S3 → PZEM-004T
   RX 43  →  TX
   TX 44  →  RX
   5V     →  VCC
   GND    →  GND
```

---

## Arquitectura del Sistema

```
┌─────────────────────────────────────────────┐
│              EDGE DEVICE (IMOX-B1)          │
│  ┌────────────┐  ┌──────────┐  ┌─────────┐ │
│  │ AMOLED UI  │  │ PZEM-004T│  │  MQTT   │ │
│  │ (Core 1)   │  │ (Core 0) │  │(Core 0) │ │
│  └────────────┘  └──────────┘  └─────────┘ │
│         ↑              ↑            ↑       │
│  ┌──────────────────────────────────────┐  │
│  │          SquareLine Studio UI        │  │
│  │     (screens/*.scj + src/ui/)       │  │
│  └──────────────────────────────────────┘  │
│                 FreeRTOS                   │
└─────────────────────────────────────────────┘
                      │
                      ↓
        ┌─────────────────────────┐
        │   IMOX Cloud Backend   │
        │  (Node.js + MQTT WSS)  │
        └─────────────────────────┘
```

---

## Instalación

### Requisitos Previos

- [PlatformIO](https://platformio.org/) (CLI o extensión VSCode)
- Python 3.8+
- Git

### Compilar

```bash
# En el directorio del proyecto
pio run
```

### Flashear al ESP32-S3

```bash
pio run -t upload
```

### Monitor Serial

```bash
pio device monitor -b 115200
```

### Simulador LVGL (Opcional)

Para probar la interfaz sin hardware:

```bash
# Ejecutar simulador
./run_sim.sh
```

---

## Configuración

### Archivo `src/config.h`

Constantes principales del sistema:

```cpp
#define FIRMWARE_VERSION "1.0.0"
#define DEVICE_MODEL "IMOX-B1"
#define MANUFACTURER "Yex Acoustics"

// PZEM-004T
#define PZEM_RX_PIN 43
#define PZEM_TX_PIN 44
#define PZEM_BAUD 9600

// MQTT WebSocket
#define MQTT_WSS_URI "wss://tu-servidor.com:443/mqtt"
#define MQTT_DEVICE_SECRET "tu_secret_device"

// BLE
#define BLE_DEVICE_PREFIX "IMOX"
```

### Provisioning BLE

1. Flashear el firmware sin credenciales WiFi
2. El dispositivo activará BLE con nombre `IMOX-XXXXXX`
3. Usar la app móvil para enviar credenciales
4. El dispositivo se conecta automáticamente

---

## Estructura del Proyecto

```
imox_square-line_ui/
├── assets/                    # Recursos (imágenes, iconos)
├── boards/                    # Definiciones de hardware
├── components/                 # Componentes SquareLine (.ecomp)
├── fonts/                      # Fuentes personalizadas
├── screens/                    # Proyectos SquareLine (.scj)
│   ├── dashboard.scj           # Pantalla principal
│   ├── voltaje.scj             # Lectura de voltaje
│   ├── corriente.scj           # Lectura de corriente
│   ├── frecuencia.scj          # Lectura de frecuencia
│   ├── diagnostic.scj          # Diagnóstico de red
│   ├── config.scj              # Configuración
│   ├── voltageStats.scj        # Estadísticas voltaje
│   ├── statsWatts.scj          # Estadísticas watts
│   └── Modo_Diario_24hrs.scj   # Consumo 24 horas
├── simulador/                  # LVGL Simulator
├── src/
│   ├── config.h                # Configuración global
│   ├── main.cpp                # Entry point + tareas FreeRTOS
│   └── ui/                     # UI generada por SquareLine
│       ├── ui.c                # Inicialización UI
│       ├── ui.h                # Headers UI
│       ├── ui_events.c         # Callbacks de eventos
│       ├── ui_events.h
│       ├── ui_globals.h        # Variables globales UI
│       ├── ui_helpers.c        # Funciones helper
│       ├── ui_theme_manager.c  # Gestión de temas
│       ├── screens/             # Pantallas generadas
│       ├── components/          # Componentes UI
│       └── fonts/               # Fuentes UI
├── SquareLine_Project.sll      # Proyecto SquareLine
├── SquareLine_Project.spj      # Configuración SquareLine
├── Themes.slt                  # Temas SquareLine
├── platformio.ini              # Configuración PlatformIO
├── run_sim.sh                  # Script simulador
└── README.md
```

---

## Desarrollo

### Convenciones de Código

- **Estilo**: Google C++ Style Guide
- **Nomenclatura**:
  - Funciones: `camelCase` (ej. `updateDisplay()`)
  - Constantes: `UPPER_SNAKE_CASE`
  - Variables globales UI: `ui_nombreObjeto`

### Modificar la UI

1. Abrir `SquareLine_Project.spj` en SquareLine Studio
2. Editar pantallas en el editor visual
3. Exportar proyecto (SquareLine Studio → Export → Export to SquareLine)
4. Compilar y flashear:

```bash
pio run -t upload
```

### Debugging

```bash
# Ver logs completos
pio device monitor -b 115200

# Filtrar solo errores
pio device monitor -b 115200 --filter direct
```

---

## Actualización OTA

El dispositivo puede recibir actualizaciones de firmware de forma remota vía MQTT:

### Flujo OTA

1. El servidor envía comando al tópico `imox/devices/{id}/ota/command`:
   ```json
   {
     "version": "1.0.1",
     "url": "https://servidor.com/firmware.bin",
     "hash": "sha256_del_firmware"
   }
   ```

2. El dispositivo descarga, verifica y aplica

3. Estados reportados al tópico `imox/devices/{id}/ota/status`:
   - PENDING → DOWNLOADING → VERIFYING → APPLYING → COMPLETED/FAILED

### Seguridad

- Verificación mandatory de hash SHA256
- Certificados TLS validados (Let's Encrypt)
- Solo una actualización a la vez (protección contra comandos duplicados)

---

## Documentación

### Documentos Técnicos

- **Manual de Usuario**: Disponible en el repositorio (formato LaTeX para Overleaf)
- **Protocolo MQTT**: Configuración de tópicos en `src/config.h`

### API Cloud

- Endpoint de vinculación: `POST /iot/link`
- Tópicos MQTT configurados en `src/config.h`

---

## Licencia

Proprietary - Yex Acoustics. Todos los derechos reservados.
