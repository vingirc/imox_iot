// Componente reutilizable: Indicador de Swipe Parpadeante (Triángulo Unicode)
// LVGL version: 8.3.11

#ifndef UI_SWIPE_HINT_H
#define UI_SWIPE_HINT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

// Crea un label con un triángulo (▲ o ▼) que parpadea lentamente.
// point_up: true para '▲' (útil en top_mid o bottom_mid), false para '▼'
lv_obj_t *ui_swipe_hint_create(lv_obj_t *parent, bool point_up);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
