// Componente reutilizable: NavDots (Círculos de navegación customizables)
// LVGL version: 8.3.11

#ifndef UI_COMP_NAVDOTS_H
#define UI_COMP_NAVDOTS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

// Crea un panel con 'total_dots' círculos, donde el círculo 'active_dot'
// (0-indexado) está resaltado con UI_COLOR_TEXT_ACTIVE, y el resto con el
// fondo. Ideal para páginas de configuración donde el número de dots varía.
lv_obj_t *ui_navDots_create(lv_obj_t *parent, uint8_t total_dots,
                            uint8_t active_dot);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
