// Componente reutilizable: Indicador de Swipe Parpadeante
// LVGL version: 8.3.11

#include "ui_swipe_hint.h"
#include "ui.h"

extern const lv_font_t ui_font_symbols_14;

// Callback de animación para la opacidad
static void swipe_hint_anim_cb(void *var, int32_t v) {
  lv_obj_set_style_text_opa((lv_obj_t *)var, v,
                            LV_PART_MAIN | LV_STATE_DEFAULT);
}

lv_obj_t *ui_swipe_hint_create(lv_obj_t *parent, bool is_top) {
  lv_obj_t *hint = lv_label_create(parent);

  // Usar el triángulo Unicode según la posición (arriba -> indica hacer swipe
  // abajo)
  if (is_top) {
    lv_label_set_text(hint, "▼");
  } else {
    lv_label_set_text(hint, "▲");
  }

  // Estilo base
  lv_obj_set_style_text_color(hint, UI_COLOR_TEXT_INFO,
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_font(hint, &ui_font_symbols_14,
                             LV_PART_MAIN | LV_STATE_DEFAULT);

  // Posicionamiento
  if (is_top) {
    lv_obj_set_align(hint, LV_ALIGN_TOP_MID);
    lv_obj_set_y(hint, 5); // Margen superior
  } else {
    lv_obj_set_align(hint, LV_ALIGN_BOTTOM_MID);
    lv_obj_set_y(hint, -5); // Margen inferior
  }

  // Animación de parpadeo (fade in/out muy suave y lento)
  lv_anim_t a;
  lv_anim_init(&a);
  lv_anim_set_var(&a, hint);
  lv_anim_set_values(
      &a, 50,
      200); // Rango de opacidad (no llega a desaparecer ni a brillar 100%)
  lv_anim_set_time(&a, 2500); // 2.5 segundos por fade
  lv_anim_set_playback_time(&a, 2500);
  lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE);
  lv_anim_set_exec_cb(&a, swipe_hint_anim_cb);
  lv_anim_set_path_cb(&a, lv_anim_path_ease_in_out); // Suavizado en los picos
  lv_anim_start(&a);

  return hint;
}
