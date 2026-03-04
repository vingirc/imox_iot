// Pantalla de Configuración 1 – WiFi y Reiniciar
// LVGL version: 8.3.11

#ifndef UI_CONFIG_H
#define UI_CONFIG_H

#include "lvgl.h"

#ifdef __cplusplus
extern "C" {
#endif

// SCREEN: ui_config
extern void ui_config_screen_init(void);
extern void ui_config_screen_destroy(void);
extern void ui_event_config(lv_event_t *e);

extern lv_obj_t *ui_config;

// Botones y Labels
extern lv_obj_t *ui_wifiBtn;
extern lv_obj_t *ui_wifiBtnLabel;
extern lv_obj_t *ui_restartBtn;
extern lv_obj_t *ui_restartBtnLabel;

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
