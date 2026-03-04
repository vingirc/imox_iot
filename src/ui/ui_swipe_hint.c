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

  // Usar el triángulo según la dirección sugerida
  // Si está arriba, punta hacia abajo (▼) para indicar que arrastres hacia
  // abajo Si está abajo, punta hacia arriba (▲) para indicar que arrastres
  // hacia arriba
  if (is_top) {
    lv_label_set_text(hint, "▼");
  } else {
    lv_label_set_text(hint, "▲");
  }

  // Estilo base: Blanco para que se vea bien
  lv_obj_set_style_text_color(hint, lv_color_white(),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_font(hint, &ui_font_symbols_14,
                             LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_add_flag(hint, LV_OBJ_FLAG_IGNORE_LAYOUT);

  // Posicionamiento
  if (is_top) {
    lv_obj_set_align(hint, LV_ALIGN_TOP_MID);
    lv_obj_set_y(hint, 10);
  } else {
    lv_obj_set_align(hint, LV_ALIGN_BOTTOM_MID);
    lv_obj_set_y(hint, -10);
  }

  lv_obj_move_foreground(hint);

  // Animación: Visible -> Parpadeo rápido -> Visible
  lv_anim_t a;
  lv_anim_init(&a);
  lv_anim_set_var(&a, hint);
  lv_anim_set_values(&a, 255,
                     0);     // Invertido: empieza en 255 (visible) y baja a 0
  lv_anim_set_time(&a, 200); // Bajada rápida
  lv_anim_set_playback_time(&a, 200); // Subida rápida
  lv_anim_set_repeat_delay(
      &a, 800); // Pausa en estado visible (255) antes de repetir
  lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE);
  lv_anim_set_exec_cb(&a, swipe_hint_anim_cb);
  lv_anim_set_path_cb(&a, lv_anim_path_linear);
  lv_anim_start(&a);

  return hint;
}
