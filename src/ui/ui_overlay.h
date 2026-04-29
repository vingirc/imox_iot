/**
 * @file ui_overlay.h
 * @brief Modales informativos globales (Vinculación BLE y Actualización OTA).
 *
 * Estos overlays se dibujan sobre lv_layer_top(), por lo que aparecen
 * encima de cualquier pantalla activa de la aplicación.
 *
 * IMPORTANTE: Todas las funciones de este módulo deben llamarse
 * exclusivamente desde el hilo de LVGL (Core 1 / loop()).
 * Si necesitas activarlos desde otro núcleo (BLE, OTA), usa flags
 * volátiles y revísalos en loop().
 */

#ifndef UI_OVERLAY_H
#define UI_OVERLAY_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

// ---- Modal de Vinculación BLE ----
void ui_overlay_show_linking(void);
void ui_overlay_update_linking(const char *msg);
void ui_overlay_hide_linking(void);

// ---- Modal de Actualización OTA ----
void ui_overlay_show_ota(const char *version);
void ui_overlay_update_ota(const char *step);
void ui_overlay_hide_ota(void);

#ifdef __cplusplus
}
#endif

#endif // UI_OVERLAY_H
