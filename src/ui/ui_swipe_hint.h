// Componente reutilizable: Indicador de Swipe Parpadeante (Triángulo Unicode)
// LVGL version: 8.3.11

#ifndef UI_SWIPE_HINT_H
#define UI_SWIPE_HINT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

// Crea un label con un triangulo que parpadea lentamente.
// is_top: true para colocarlo arriba (con flecha hacia abajo), false para
// colocarlo abajo (con flecha hacia arriba)
lv_obj_t *ui_swipe_hint_create(lv_obj_t *parent, bool is_top);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
