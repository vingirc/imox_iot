# Plan de Implementación: Provisionamiento Dinámico MQTT a través del Backend

Este documento es una guía paso a paso para implementar la asignación dinámica del `MQTT_IOT_ID` y `MQTT_DEVICE_SECRET` directamente desde el backend, de modo que **nunca más tengas que definir IDs manuales en `config.h`** al ensamblar nuevos equipos.

## ¿Cómo funcionará el nuevo flujo?
1. Se fabrican todos los ESP32 con el **mismo firmware** exacto.
2. El usuario vincula el dispositivo con la App usando BLE. La App le pide al ESP32 que se conecte a un WiFi.
3. El ESP32 se conecta al WiFi y hace un POST a `/iot/link` enviando **solo su MAC Address**.
4. El **backend** recibe la MAC Address, crea el registro en la base de datos, le asigna el ID secuencial disponible (ej. `4`) y genera un secreto aleatorio.
5. El servidor devuelve un JSON al ESP32 confirmando la vinculación, junto con el ID y el Secret.
6. El ESP32 toma este JSON y guarda el ID y Secret **permanentemente** en la memoria NVS.

---

## 1. Cambios requeridos en el Backend (API NestJS / Proxy)

Actualmente, el endpoint POST `/iot/link` recibe:
```json
{
  "macAddress": "A0:B1:C2:D3:E4:F5",
  "deviceSecret": "b67a81fa...",
  "userId": 1
}
```

**Deberás modificar el backend para:**
1. Ignorar el campo `deviceSecret` recibido del ESP32.
2. Generar el `deviceSecret` y asignar el `iot_id` (basado en el ID de la base de datos de dispositivos) en el servidor.
3. Responder con HTTP 200 y el siguiente payload:

```json
{
  "status": "success",
  "iot_id": 4,
  "device_secret": "a1b2c3d4e5f6..."
}
```

---

## 2. Cambios requeridos en el ESP32 (`src/main.cpp`)

Una vez que el backend esté listo para devolver las credenciales, en el código del ESP32 (dentro de la función `provisioningTaskCode`), buscarás el lugar donde se hace la petición HTTP y cambiarás el parseo de la respuesta:

```cpp
// 1. Ya NO enviar el MQTT_DEVICE_SECRET al backend
JsonDocument linkDoc;
linkDoc["macAddress"] = WiFi.macAddress();
linkDoc["userId"] = req.userId;
// linkDoc["deviceSecret"] = ... (Borrar)
```

**Modificar el bloque donde se recibe HTTP 200:**
```cpp
if (httpCode == 200) {
  // Parsear respuesta del servidor
  JsonDocument responseDoc;
  deserializeJson(responseDoc, response);
  
  if (responseDoc.containsKey("iot_id") && responseDoc.containsKey("device_secret")) {
    int nuevo_id = responseDoc["iot_id"];
    String nuevo_secret = responseDoc["device_secret"].as<String>();

    // 1. Actualizar memoria dinámica
    active_mqtt_id = nuevo_id;
    active_mqtt_secret = nuevo_secret;

    // 2. Guardar permanentemente en NVS
    Preferences prefs_iot;
    prefs_iot.begin("iot_cfg", false);
    prefs_iot.putInt("mqtt_id", active_mqtt_id);
    prefs_iot.putString("mqtt_secret", active_mqtt_secret);
    prefs_iot.end();

    // 3. Re-generar tópicos
    String base_topic = "imox/devices/" + String(active_mqtt_id);
    topic_telemetry = base_topic + "/telemetry";
    topic_history_res = base_topic + "/history/response";
    topic_ota_command = base_topic + "/ota/command";
    topic_ota_status = base_topic + "/ota/status";

    // 4. Guardar el WiFi
    Preferences prefs_wifi;
    prefs_wifi.begin("wifi", false);
    prefs_wifi.putString("ssid", String(req.ssid));
    prefs_wifi.putString("pass", String(req.password));
    prefs_wifi.end();

    // Continuar con el flujo original...
    sendBLENotification("success", "Dispositivo vinculado correctamente");
    // ...
```

## 3. Limpieza de `src/config.h`
Una vez implementado esto, **podrás borrar** por completo estas líneas en `config.h`:
```c
#define MQTT_IOT_ID           3
#define MQTT_DEVICE_SECRET    "b67a81fa475cacdc6a036c2e1395e8399b893764883a8c1b"
#define MQTT_TOPIC_BASE ...
// etc.
```

(En su lugar, podrías inicializar `active_mqtt_id` con `0` si el NVS está vacío, lo que evitará que intente conectarse al broker MQTT antes de ser provisionado por primera vez).
