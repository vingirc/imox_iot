// Componente reutilizable: NavDots (Círculos de navegación customizables)
// LVGL version: 8.3.11

#include "ui_comp_navdots.h"
#include "../ui.h"


lv_obj_t *ui_navDots_create(lv_obj_t *parent, uint8_t total_dots,
                            uint8_t active_dot) {
  // Crear el contenedor flex
  lv_obj_t *panel = lv_obj_create(parent);
  lv_obj_set_width(panel, LV_SIZE_CONTENT);
  lv_obj_set_height(panel, LV_SIZE_CONTENT);
  lv_obj_set_align(
      panel, LV_ALIGN_TOP_MID); // Por defecto arriba, como pidió el usuario
  lv_obj_set_y(panel, 15);      // Un pequeño margen superior

  lv_obj_set_flex_flow(panel, LV_FLEX_FLOW_ROW);
  lv_obj_set_flex_align(panel, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER,
                        LV_FLEX_ALIGN_CENTER);
  lv_obj_clear_flag(panel, LV_OBJ_FLAG_SCROLLABLE);

  // Quitar fondos y bordes del contenedor
  lv_obj_set_style_bg_opa(panel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_border_width(panel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_all(panel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_column(
      panel, 8, LV_PART_MAIN | LV_STATE_DEFAULT); // Espacio entre dots

  // Crear los círculos
  for (uint8_t i = 0; i < total_dots; i++) {
    lv_obj_t *dot = lv_obj_create(panel);
    lv_obj_set_width(dot, 10);
    lv_obj_set_height(dot, 10);
    lv_obj_set_style_radius(dot, LV_RADIUS_CIRCLE,
                            LV_PART_MAIN | LV_STATE_DEFAULT);

    // Borde blanco
    lv_obj_set_style_border_color(dot, UI_COLOR_TEXT_ACTIVE,
                                  LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(dot, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(dot, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Relleno si está activo, vacío (bg) si no
    if (i == active_dot) {
      lv_obj_set_style_bg_color(dot, UI_COLOR_TEXT_ACTIVE,
                                LV_PART_MAIN | LV_STATE_DEFAULT);
      lv_obj_set_style_bg_opa(dot, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    } else {
      lv_obj_set_style_bg_color(dot, UI_COLOR_BG,
                                LV_PART_MAIN | LV_STATE_DEFAULT);
      lv_obj_set_style_bg_opa(
          dot, 0, LV_PART_MAIN | LV_STATE_DEFAULT); // Transparente por dentro
    }
  }

  return panel;
}
