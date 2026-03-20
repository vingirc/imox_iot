// Pantalla de Configuración 3 – Burnout Protection
// LVGL version: 8.3.11

#include "ui_burnout.h"
#include "../components/ui_comp_navdots.h"
#include "../ui.h"
#include "../ui_swipe_hint.h"
#include <stdio.h>

lv_obj_t *ui_burnout = NULL;
lv_obj_t *ui_burnoutEnableSwitch = NULL;
lv_obj_t *ui_dimSlider = NULL;
lv_obj_t *ui_offSlider = NULL;
lv_obj_t *ui_dimTimeLabel = NULL;
lv_obj_t *ui_offTimeLabel = NULL;

// Callbacks de hardware declarados en main.cpp
extern void hw_burnout_setup(bool enable, uint32_t dim_s, uint32_t off_s);
extern bool burnout_enabled;
extern uint32_t dim_timeout_s;
extern uint32_t off_timeout_s;
extern uint8_t user_brightness;

static void burnout_config_update_cb(lv_event_t *e) {
    bool en = lv_obj_has_state(ui_burnoutEnableSwitch, LV_STATE_CHECKED);
    uint32_t dim = lv_slider_get_value(ui_dimSlider);
    uint32_t off = lv_slider_get_value(ui_offSlider);

    char buf[16];
    snprintf(buf, sizeof(buf), "%us", dim);
    lv_label_set_text(ui_dimTimeLabel, buf);
    
    snprintf(buf, sizeof(buf), "%us", off);
    lv_label_set_text(ui_offTimeLabel, buf);

    hw_burnout_setup(en, dim, off);
}

void ui_event_burnout(lv_event_t *e) {
  lv_event_code_t event_code = lv_event_get_code(e);

  // Swipe RIGHT: Regresar a Config pág 2 (Brillo)
  if (event_code == LV_EVENT_GESTURE &&
      lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_RIGHT) {
    lv_indev_wait_release(lv_indev_get_act());
    ui_last_config_index = 1;
    _ui_screen_change(&ui_config_brightness, UI_ANIM_SWIPE_RIGHT, UI_ANIM_SWIPE_DURATION,
                      UI_ANIM_SWIPE_DELAY, &ui_config_brightness_screen_init);
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
  lv_obj_set_style_bg_color(ui_burnout, UI_COLOR_BG, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(ui_burnout, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

  // NavDots (3 dots, estamos en el tercero - index 2)
  ui_navDots_create(ui_burnout, 3, 2);

  lv_obj_t *main_container = lv_obj_create(ui_burnout);
  lv_obj_set_width(main_container, lv_pct(90));
  lv_obj_set_height(main_container, lv_pct(80));
  lv_obj_set_align(main_container, LV_ALIGN_CENTER);
  lv_obj_set_flex_flow(main_container, LV_FLEX_FLOW_COLUMN);
  lv_obj_set_flex_align(main_container, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
  lv_obj_set_style_bg_opa(main_container, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_border_width(main_container, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_gap(main_container, 20, LV_PART_MAIN | LV_STATE_DEFAULT);

  // Titulo
  lv_obj_t *title = lv_label_create(main_container);
  lv_label_set_text(title, "Protección Burnout");
  lv_obj_set_style_text_font(title, &ui_font_Qualy24, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_color(title, UI_COLOR_TEXT_ACTIVE, LV_PART_MAIN | LV_STATE_DEFAULT);

  // Switch habilitar
  lv_obj_t *row_en = lv_obj_create(main_container);
  lv_obj_set_size(row_en, lv_pct(100), LV_SIZE_CONTENT);
  lv_obj_set_flex_flow(row_en, LV_FLEX_FLOW_ROW);
  lv_obj_set_flex_align(row_en, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
  lv_obj_set_style_bg_opa(row_en, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_border_width(row_en, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

  lv_obj_t *lbl_en = lv_label_create(row_en);
  lv_label_set_text(lbl_en, "Activar protección");
  lv_obj_set_style_text_font(lbl_en, &ui_font_Qualy14, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_color(lbl_en, UI_COLOR_TEXT_INFO, LV_PART_MAIN | LV_STATE_DEFAULT);

  ui_burnoutEnableSwitch = lv_switch_create(row_en);
  if (burnout_enabled) lv_obj_add_state(ui_burnoutEnableSwitch, LV_STATE_CHECKED);
  else lv_obj_clear_state(ui_burnoutEnableSwitch, LV_STATE_CHECKED);
  lv_obj_add_event_cb(ui_burnoutEnableSwitch, burnout_config_update_cb, LV_EVENT_VALUE_CHANGED, NULL);

  // Slider Atenuacion
  lv_obj_t *lbl_dim = lv_label_create(main_container);
  lv_label_set_text(lbl_dim, "Tiempo para atenuar");
  lv_obj_set_style_text_font(lbl_dim, &ui_font_Qualy14, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_color(lbl_dim, UI_COLOR_TEXT_INFO, LV_PART_MAIN | LV_STATE_DEFAULT);

  lv_obj_t *row_dim = lv_obj_create(main_container);
  lv_obj_set_size(row_dim, lv_pct(100), LV_SIZE_CONTENT);
  lv_obj_set_flex_flow(row_dim, LV_FLEX_FLOW_ROW);
  lv_obj_set_style_bg_opa(row_dim, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_border_width(row_dim, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

  ui_dimSlider = lv_slider_create(row_dim);
  lv_obj_set_flex_grow(ui_dimSlider, 1);
  lv_slider_set_range(ui_dimSlider, 10, 300);
  lv_slider_set_value(ui_dimSlider, dim_timeout_s, LV_ANIM_OFF);
  lv_obj_add_event_cb(ui_dimSlider, burnout_config_update_cb, LV_EVENT_VALUE_CHANGED, NULL);

  ui_dimTimeLabel = lv_label_create(row_dim);
  char buf[16];
  snprintf(buf, sizeof(buf), "%us", dim_timeout_s);
  lv_label_set_text(ui_dimTimeLabel, buf);
  lv_obj_set_style_text_font(ui_dimTimeLabel, &ui_font_Qualy14, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_left(ui_dimTimeLabel, 10, 0);

  // Slider Apagado
  lv_obj_t *lbl_off = lv_label_create(main_container);
  lv_label_set_text(lbl_off, "Tiempo para apagar");
  lv_obj_set_style_text_font(lbl_off, &ui_font_Qualy14, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_color(lbl_off, UI_COLOR_TEXT_INFO, LV_PART_MAIN | LV_STATE_DEFAULT);

  lv_obj_t *row_off = lv_obj_create(main_container);
  lv_obj_set_size(row_off, lv_pct(100), LV_SIZE_CONTENT);
  lv_obj_set_flex_flow(row_off, LV_FLEX_FLOW_ROW);
  lv_obj_set_style_bg_opa(row_off, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_border_width(row_off, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

  ui_offSlider = lv_slider_create(row_off);
  lv_obj_set_flex_grow(ui_offSlider, 1);
  lv_slider_set_range(ui_offSlider, 30, 600);
  lv_slider_set_value(ui_offSlider, off_timeout_s, LV_ANIM_OFF);
  lv_obj_add_event_cb(ui_offSlider, burnout_config_update_cb, LV_EVENT_VALUE_CHANGED, NULL);

  ui_offTimeLabel = lv_label_create(row_off);
  snprintf(buf, sizeof(buf), "%us", off_timeout_s);
  lv_label_set_text(ui_offTimeLabel, buf);
  lv_obj_set_style_text_font(ui_offTimeLabel, &ui_font_Qualy14, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_left(ui_offTimeLabel, 10, 0);

  lv_obj_add_event_cb(ui_burnout, ui_event_burnout, LV_EVENT_ALL, NULL);
  
  // Swipe Hint
  ui_swipe_hint_create(ui_burnout, false);
}

void ui_burnout_screen_destroy(void) {
  if (ui_burnout) lv_obj_del(ui_burnout);
  ui_burnout = NULL;
}
