// Pantalla de Configuración 2 – Brillo
// LVGL version: 8.3.11

#ifndef UI_CONFIG_BRIGHTNESS_H
#define UI_CONFIG_BRIGHTNESS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

// SCREEN: ui_config_brightness
extern void ui_config_brightness_screen_init(void);
extern void ui_config_brightness_screen_destroy(void);
extern void ui_event_config_brightness(lv_event_t *e);

extern lv_obj_t *ui_config_brightness;
extern lv_obj_t *ui_brightnessSlider;
extern lv_obj_t *ui_brightnessValLabel;

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
