// Pantalla de Configuración 3 – Burnout Proteccion
// LVGL version: 8.3.11

#ifndef UI_BURNOUT_H
#define UI_BURNOUT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

// SCREEN: ui_burnout
extern void ui_burnout_screen_init(void);
extern void ui_burnout_screen_destroy(void);
extern void ui_event_burnout(lv_event_t *e);

extern lv_obj_t *ui_burnout;
extern lv_obj_t *ui_burnoutBtn;
extern lv_obj_t *ui_burnoutBtnLabel;
extern lv_obj_t *ui_dimSlider;
extern lv_obj_t *ui_offSlider;
extern lv_obj_t *ui_dimTimeLabel;
extern lv_obj_t *ui_offTimeLabel;

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
