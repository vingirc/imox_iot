// Pantalla de Configuración 3 – Burnout Proteccion
// LVGL version: 8.3.11

#include "ui_burnout.h"
#include "../components/ui_comp_navdots.h"
#include "../ui.h"
#include "../ui_swipe_hint.h"
#include <stdio.h>

lv_obj_t *ui_burnout = NULL;
lv_obj_t *ui_burnoutBtn = NULL;
lv_obj_t *ui_burnoutBtnLabel = NULL;
lv_obj_t *ui_dimSlider = NULL;
lv_obj_t *ui_offSlider = NULL;
lv_obj_t *ui_dimTimeLabel = NULL;
lv_obj_t *ui_offTimeLabel = NULL;
lv_obj_t *ui_dimTitleLabel = NULL;
lv_obj_t *ui_offTitleLabel = NULL;

// Callbacks de hardware declarados en main.cpp
extern void hw_burnout_setup(bool enable, uint32_t dim_s, uint32_t off_s);
extern bool burnout_enabled;
extern uint32_t dim_timeout_s;
extern uint32_t off_timeout_s;

/**
 * Actualiza el estado visual (habilitado/deshabilitado) de los controles
 * según el estado de la protección.
 */
static void ui_burnout_update_state(void) {
  if (burnout_enabled) {
    lv_label_set_text(ui_burnoutBtnLabel, "Proteccion: ON");
    lv_obj_set_style_bg_color(ui_burnoutBtn, lv_color_hex(0x2E7D32),
                              LV_PART_MAIN | LV_STATE_DEFAULT);

    // Habilitar sliders y labels
    lv_obj_clear_state(ui_dimSlider, LV_STATE_DISABLED);
    lv_obj_clear_state(ui_offSlider, LV_STATE_DISABLED);

    lv_obj_set_style_text_color(ui_dimTitleLabel, UI_COLOR_TEXT_ACTIVE,
                                LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui_offTitleLabel, UI_COLOR_TEXT_ACTIVE,
                                LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_text_color(ui_dimTimeLabel, UI_COLOR_ACCENT,
                                LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui_offTimeLabel, UI_COLOR_ACCENT,
                                LV_PART_MAIN | LV_STATE_DEFAULT);

    // Restaurar opacidad de sliders
    lv_obj_set_style_opa(ui_dimSlider, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_opa(ui_offSlider, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
  } else {
    lv_label_set_text(ui_burnoutBtnLabel, "Proteccion: OFF");
    lv_obj_set_style_bg_color(ui_burnoutBtn, lv_color_hex(0xC62828),
                              LV_PART_MAIN | LV_STATE_DEFAULT);

    // Deshabilitar sliders
    lv_obj_add_state(ui_dimSlider, LV_STATE_DISABLED);
    lv_obj_add_state(ui_offSlider, LV_STATE_DISABLED);

    // Todo en gris
    lv_obj_set_style_text_color(ui_dimTitleLabel, UI_COLOR_TEXT_INFO,
                                LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui_offTitleLabel, UI_COLOR_TEXT_INFO,
                                LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_text_color(ui_dimTimeLabel, UI_COLOR_TEXT_INFO,
                                LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui_offTimeLabel, UI_COLOR_TEXT_INFO,
                                LV_PART_MAIN | LV_STATE_DEFAULT);

    // Bajar opacidad para indicar bloqueo
    lv_obj_set_style_opa(ui_dimSlider, 100, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_opa(ui_offSlider, 100, LV_PART_MAIN | LV_STATE_DEFAULT);
  }
}

static void burnout_config_update_cb(lv_event_t *e) {
  uint32_t dim = lv_slider_get_value(ui_dimSlider);
  uint32_t off = lv_slider_get_value(ui_offSlider);

  // Snapping a minutos si pasa de 60s
  if (dim > 60) {
    dim = (dim / 60) * 60;
    lv_slider_set_value(ui_dimSlider, dim, LV_ANIM_OFF);
  }
  if (off > 60) {
    off = (off / 60) * 60;
    lv_slider_set_value(ui_offSlider, off, LV_ANIM_OFF);
  }

  // 3600s = OFF (0 en hardware significa nunca apagar)
  uint32_t real_off = (off == 3600) ? 0 : off;

  dim_timeout_s = dim;
  off_timeout_s = real_off;

  char buf[16];
  if (dim < 60) {
    snprintf(buf, sizeof(buf), "%us", dim);
  } else {
    snprintf(buf, sizeof(buf), "%uM", dim / 60);
  }
  lv_label_set_text(ui_dimTimeLabel, buf);

  if (off == 3600) {
    lv_label_set_text(ui_offTimeLabel, "OFF");
  } else if (off < 60) {
    snprintf(buf, sizeof(buf), "%us", off);
    lv_label_set_text(ui_offTimeLabel, buf);
  } else {
    snprintf(buf, sizeof(buf), "%uM", off / 60);
    lv_label_set_text(ui_offTimeLabel, buf);
  }

  hw_burnout_setup(burnout_enabled, dim, real_off);
}

static void burnout_toggle_btn_cb(lv_event_t *e) {
  burnout_enabled = !burnout_enabled;
  ui_burnout_update_state();
  hw_burnout_setup(burnout_enabled, dim_timeout_s, off_timeout_s);
}

void ui_event_burnout(lv_event_t *e) {
  lv_event_code_t event_code = lv_event_get_code(e);

  // Swipe RIGHT: Regresar a Config pág 2 (Brillo)
  if (event_code == LV_EVENT_GESTURE &&
      lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_RIGHT) {
    lv_indev_wait_release(lv_indev_get_act());
    ui_last_config_index = 1;
    _ui_screen_change(&ui_config_brightness, UI_ANIM_SWIPE_RIGHT,
                      UI_ANIM_SWIPE_DURATION, UI_ANIM_SWIPE_DELAY,
                      &ui_config_brightness_screen_init);
  }

  // Swipe LEFT: Ir a Config pág 1 (Ajustes) - Cíclico
  if (event_code == LV_EVENT_GESTURE &&
      lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_LEFT) {
    lv_indev_wait_release(lv_indev_get_act());
    ui_last_config_index = 0;
    _ui_screen_change(&ui_config, UI_ANIM_SWIPE_LEFT, UI_ANIM_SWIPE_DURATION,
                      UI_ANIM_SWIPE_DELAY, &ui_config_screen_init);
  }

  // Swipe UP (TOP): Regresar a la última pantalla vista
  if (event_code == LV_EVENT_GESTURE &&
      lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_TOP) {
    lv_indev_wait_release(lv_indev_get_act());
    _ui_screen_change_by_index(ui_last_screen_index);
  }
}

void ui_burnout_screen_init(void) {
  ui_burnout = lv_obj_create(NULL);
  lv_obj_clear_flag(ui_burnout, LV_OBJ_FLAG_SCROLLABLE);
  lv_obj_set_style_bg_color(ui_burnout, UI_COLOR_BG,
                            LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(ui_burnout, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

  // NavDots (index 2)
  ui_navDots_create(ui_burnout, 3, 2);

  lv_obj_t *main_container = lv_obj_create(ui_burnout);
  lv_obj_set_width(main_container, lv_pct(85));
  lv_obj_set_height(main_container, lv_pct(78));
  lv_obj_set_align(main_container, LV_ALIGN_CENTER);
  lv_obj_set_flex_flow(main_container, LV_FLEX_FLOW_COLUMN);
  lv_obj_set_flex_align(main_container, LV_FLEX_ALIGN_CENTER,
                        LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
  lv_obj_set_style_bg_opa(main_container, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_border_width(main_container, 0,
                                LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_gap(main_container, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_clear_flag(main_container, LV_OBJ_FLAG_SCROLLABLE);

  // Botón Principal (Toggle)
  ui_burnoutBtn = lv_btn_create(main_container);
  lv_obj_set_size(ui_burnoutBtn, lv_pct(100), 55);
  lv_obj_set_style_radius(ui_burnoutBtn, 15, LV_PART_MAIN | LV_STATE_DEFAULT);

  ui_burnoutBtnLabel = lv_label_create(ui_burnoutBtn);
  lv_obj_center(ui_burnoutBtnLabel);
  lv_obj_set_style_text_font(ui_burnoutBtnLabel, &ui_font_Qualy24,
                             LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_add_event_cb(ui_burnoutBtn, burnout_toggle_btn_cb, LV_EVENT_CLICKED,
                      NULL);

  // Layout de Dos Columnas
  lv_obj_t *row_sliders = lv_obj_create(main_container);
  lv_obj_set_size(row_sliders, lv_pct(100), LV_SIZE_CONTENT);
  lv_obj_set_flex_flow(row_sliders, LV_FLEX_FLOW_ROW);
  lv_obj_set_flex_align(row_sliders, LV_FLEX_ALIGN_SPACE_BETWEEN,
                        LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
  lv_obj_set_style_bg_opa(row_sliders, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_border_width(row_sliders, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_all(row_sliders, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_clear_flag(row_sliders, LV_OBJ_FLAG_SCROLLABLE);

  // --- COL. IZQ: Atenuar ---
  lv_obj_t *col_dim = lv_obj_create(row_sliders);
  lv_obj_set_size(col_dim, lv_pct(46), LV_SIZE_CONTENT);
  lv_obj_set_flex_flow(col_dim, LV_FLEX_FLOW_COLUMN);
  lv_obj_set_flex_align(col_dim, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER,
                        LV_FLEX_ALIGN_CENTER);
  lv_obj_set_style_bg_opa(col_dim, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_border_width(col_dim, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_gap(col_dim, 25, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_clear_flag(col_dim, LV_OBJ_FLAG_SCROLLABLE);

  // Cabecera: Titulo + Valor
  lv_obj_t *row_header_dim = lv_obj_create(col_dim);
  lv_obj_set_size(row_header_dim, lv_pct(100), LV_SIZE_CONTENT);
  lv_obj_set_flex_flow(row_header_dim, LV_FLEX_FLOW_ROW);
  lv_obj_set_flex_align(row_header_dim, LV_FLEX_ALIGN_SPACE_BETWEEN,
                        LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
  lv_obj_set_style_bg_opa(row_header_dim, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_border_width(row_header_dim, 0,
                                LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_all(row_header_dim, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

  ui_dimTitleLabel = lv_label_create(row_header_dim);
  lv_label_set_text(ui_dimTitleLabel, "Atenuar");
  lv_obj_set_style_text_font(ui_dimTitleLabel, &ui_font_Qualy24,
                             LV_PART_MAIN | LV_STATE_DEFAULT);

  ui_dimTimeLabel = lv_label_create(row_header_dim);
  char buf[16];
  if (dim_timeout_s < 60) {
    snprintf(buf, sizeof(buf), "%us", dim_timeout_s);
  } else {
    snprintf(buf, sizeof(buf), "%uM", dim_timeout_s / 60);
  }
  lv_label_set_text(ui_dimTimeLabel, buf);
  lv_obj_set_style_text_font(ui_dimTimeLabel, &ui_font_Qualy24,
                             LV_PART_MAIN | LV_STATE_DEFAULT);

  ui_dimSlider = lv_slider_create(col_dim);
  lv_obj_set_size(ui_dimSlider, lv_pct(85), 20); // Ancho reducido
  lv_slider_set_range(ui_dimSlider, 10, 600);
  lv_slider_set_value(ui_dimSlider, dim_timeout_s, LV_ANIM_OFF);
  lv_obj_clear_flag(ui_dimSlider, LV_OBJ_FLAG_GESTURE_BUBBLE);
  lv_obj_set_style_bg_color(ui_dimSlider, UI_COLOR_SLIDER_TRACK,
                            LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_color(ui_dimSlider, UI_COLOR_ACCENT,
                            LV_PART_INDICATOR | LV_STATE_DEFAULT);
  lv_obj_set_style_radius(ui_dimSlider, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_color(ui_dimSlider, UI_COLOR_CARD_BG,
                            LV_PART_KNOB | LV_STATE_DEFAULT);
  lv_obj_set_style_border_color(ui_dimSlider, UI_COLOR_TEXT_INFO,
                                LV_PART_KNOB | LV_STATE_DEFAULT);
  lv_obj_set_style_border_width(ui_dimSlider, 2,
                                LV_PART_KNOB | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_all(ui_dimSlider, 15, LV_PART_KNOB | LV_STATE_DEFAULT);
  lv_obj_add_event_cb(ui_dimSlider, burnout_config_update_cb,
                      LV_EVENT_VALUE_CHANGED, NULL);

  // --- COL. DER: Apagar ---
  lv_obj_t *col_off = lv_obj_create(row_sliders);
  lv_obj_set_size(col_off, lv_pct(46), LV_SIZE_CONTENT);
  lv_obj_set_flex_flow(col_off, LV_FLEX_FLOW_COLUMN);
  lv_obj_set_flex_align(col_off, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER,
                        LV_FLEX_ALIGN_CENTER);
  lv_obj_set_style_bg_opa(col_off, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_border_width(col_off, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_gap(col_off, 25, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_clear_flag(col_off, LV_OBJ_FLAG_SCROLLABLE);

  // Cabecera: Titulo + Valor
  lv_obj_t *row_header_off = lv_obj_create(col_off);
  lv_obj_set_size(row_header_off, lv_pct(100), LV_SIZE_CONTENT);
  lv_obj_set_flex_flow(row_header_off, LV_FLEX_FLOW_ROW);
  lv_obj_set_flex_align(row_header_off, LV_FLEX_ALIGN_SPACE_BETWEEN,
                        LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
  lv_obj_set_style_bg_opa(row_header_off, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_border_width(row_header_off, 0,
                                LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_all(row_header_off, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

  ui_offTitleLabel = lv_label_create(row_header_off);
  lv_label_set_text(ui_offTitleLabel, "Apagar");
  lv_obj_set_style_text_font(ui_offTitleLabel, &ui_font_Qualy24,
                             LV_PART_MAIN | LV_STATE_DEFAULT);

  ui_offTimeLabel = lv_label_create(row_header_off);
  if (off_timeout_s == 0 || off_timeout_s == 3600) {
    lv_label_set_text(ui_offTimeLabel, "OFF");
  } else if (off_timeout_s < 60) {
    snprintf(buf, sizeof(buf), "%us", off_timeout_s);
    lv_label_set_text(ui_offTimeLabel, buf);
  } else {
    snprintf(buf, sizeof(buf), "%uM", off_timeout_s / 60);
    lv_label_set_text(ui_offTimeLabel, buf);
  }
  lv_obj_set_style_text_font(ui_offTimeLabel, &ui_font_Qualy24,
                             LV_PART_MAIN | LV_STATE_DEFAULT);

  ui_offSlider = lv_slider_create(col_off);
  lv_obj_set_size(ui_offSlider, lv_pct(85), 20);
  lv_slider_set_range(ui_offSlider, 30, 3600);
  lv_slider_set_value(ui_offSlider, (off_timeout_s == 0) ? 3600 : off_timeout_s, LV_ANIM_OFF);
  lv_obj_clear_flag(ui_offSlider, LV_OBJ_FLAG_GESTURE_BUBBLE);
  lv_obj_set_style_bg_color(ui_offSlider, UI_COLOR_SLIDER_TRACK,
                            LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_color(ui_offSlider, UI_COLOR_ACCENT,
                            LV_PART_INDICATOR | LV_STATE_DEFAULT);
  lv_obj_set_style_radius(ui_offSlider, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_color(ui_offSlider, UI_COLOR_CARD_BG,
                            LV_PART_KNOB | LV_STATE_DEFAULT);
  lv_obj_set_style_border_color(ui_offSlider, UI_COLOR_TEXT_INFO,
                                LV_PART_KNOB | LV_STATE_DEFAULT);
  lv_obj_set_style_border_width(ui_offSlider, 2,
                                LV_PART_KNOB | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_all(ui_offSlider, 15, LV_PART_KNOB | LV_STATE_DEFAULT);
  lv_obj_add_event_cb(ui_offSlider, burnout_config_update_cb,
                      LV_EVENT_VALUE_CHANGED, NULL);

  // Sincronizar estado inicial
  ui_burnout_update_state();

  lv_obj_add_event_cb(ui_burnout, ui_event_burnout, LV_EVENT_ALL, NULL);

  // Swipe Hint
  ui_swipe_hint_create(ui_burnout, false);
}

void ui_burnout_screen_destroy(void) {
  if (ui_burnout)
    lv_obj_del(ui_burnout);
  ui_burnout = NULL;
}
