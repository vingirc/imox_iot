// Pantalla de Configuración 2 – Brillo
// LVGL version: 8.3.11

#include "ui_config_brightness.h"
#include "../components/ui_comp_navdots.h"
#include "../ui.h"
#include "../ui_swipe_hint.h"
#include <stdio.h>

extern const lv_font_t ui_font_symbols_24;

lv_obj_t *ui_config_brightness = NULL;
lv_obj_t *ui_brightnessSlider = NULL;
lv_obj_t *ui_brightnessValLabel = NULL;

// Callback declarado en ui_events.c
extern void onBrightnessChange(int32_t value);

// Callback local para el slider (actualiza label y notifica hardware)
static void brightness_slider_cb(lv_event_t *e) {
  lv_obj_t *slider = lv_event_get_target(e);
  int32_t v = lv_slider_get_value(slider);

  char buf[16];
  // Calcular porcentaje de 0 a 255
  int pct = (v * 100) / 255;
  snprintf(buf, sizeof(buf), "%d%%", pct);
  lv_label_set_text(ui_brightnessValLabel, buf);

  // Llamar al callback de hardware
  onBrightnessChange(v);
}

// Callback para el botón de apagar pantalla
static void turn_off_btn_cb(lv_event_t *e) {
  // Llama a la función global para apagar
  extern void onTurnOffScreen(void);
  onTurnOffScreen();
}

void ui_event_config_brightness(lv_event_t *e) {
  lv_event_code_t event_code = lv_event_get_code(e);

  // Swipe RIGHT: Regresar a Config pág 1 (Ajustes)
  if (event_code == LV_EVENT_GESTURE &&
      lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_RIGHT) {
    lv_indev_wait_release(lv_indev_get_act());
    ui_last_config_index = 0;
    _ui_screen_change(&ui_config, UI_ANIM_SWIPE_RIGHT, UI_ANIM_SWIPE_DURATION,
                      UI_ANIM_SWIPE_DELAY, &ui_config_screen_init);
  }

  // Swipe LEFT: Ir a la siguiente pág (Burnout - pág 3)
  if (event_code == LV_EVENT_GESTURE &&
      lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_LEFT) {
    lv_indev_wait_release(lv_indev_get_act());
    ui_last_config_index = 2;
    _ui_screen_change(&ui_burnout, UI_ANIM_SWIPE_LEFT, UI_ANIM_SWIPE_DURATION,
                      UI_ANIM_SWIPE_DELAY, &ui_burnout_screen_init);
  }

  // Swipe UP (TOP): Regresar a la última pantalla vista
  if (event_code == LV_EVENT_GESTURE &&
      lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_TOP) {
    lv_indev_wait_release(lv_indev_get_act());
    _ui_screen_change_by_index(
        ui_last_screen_index); // Función que agregaremos en ui_helpers.c
  }
}

void ui_config_brightness_screen_init(void) {
  ui_config_brightness = lv_obj_create(NULL);
  lv_obj_clear_flag(ui_config_brightness, LV_OBJ_FLAG_SCROLLABLE);
  lv_obj_set_style_bg_color(ui_config_brightness, UI_COLOR_BG,
                            LV_PART_MAIN | LV_STATE_DEFAULT);
  // Fondo oscuro
  lv_obj_set_style_bg_opa(ui_config_brightness, 255,
                          LV_PART_MAIN | LV_STATE_DEFAULT);

  // NavDots (3 dots, estamos en el segundo - index 1)
  ui_navDots_create(ui_config_brightness, 3, 1);

  // Slider de brillo, muy grueso y centrado
  ui_brightnessSlider = lv_slider_create(ui_config_brightness);
  lv_obj_set_width(ui_brightnessSlider, 300);
  lv_obj_set_height(ui_brightnessSlider, 20); // Track grueso
  lv_obj_set_align(ui_brightnessSlider, LV_ALIGN_TOP_MID);
  lv_obj_set_y(ui_brightnessSlider, 80);
  lv_slider_set_range(ui_brightnessSlider, 20, 255);
  // Usar el brillo real almacenado en NVS (no el default de compilación)
  uint8_t current_brightness = hw_get_brightness();
  lv_slider_set_value(ui_brightnessSlider, current_brightness, LV_ANIM_OFF);
  lv_obj_clear_flag(ui_brightnessSlider, LV_OBJ_FLAG_GESTURE_BUBBLE); // Evitar que el slider active el swipe de pantalla
  lv_obj_remove_style(ui_brightnessSlider, NULL,
                      LV_PART_INDICATOR); // Quitamos indicador default

  // Estilo del track (fondo)
  lv_obj_set_style_bg_color(ui_brightnessSlider, UI_COLOR_SLIDER_TRACK,
                            LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(ui_brightnessSlider, 255,
                          LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_radius(ui_brightnessSlider, 10,
                          LV_PART_MAIN | LV_STATE_DEFAULT);

  // Estilo del indicador (la parte llena)
  lv_obj_set_style_bg_color(ui_brightnessSlider, UI_COLOR_ACCENT,
                            LV_PART_INDICATOR | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(ui_brightnessSlider, 255,
                          LV_PART_INDICATOR | LV_STATE_DEFAULT);
  lv_obj_set_style_radius(ui_brightnessSlider, 10,
                          LV_PART_INDICATOR | LV_STATE_DEFAULT);

  // Estilo del knob
  lv_obj_set_style_bg_color(ui_brightnessSlider, UI_COLOR_CARD_BG,
                            LV_PART_KNOB | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(ui_brightnessSlider, 255,
                          LV_PART_KNOB | LV_STATE_DEFAULT);
  lv_obj_set_style_border_color(ui_brightnessSlider, UI_COLOR_TEXT_INFO,
                                LV_PART_KNOB | LV_STATE_DEFAULT);
  lv_obj_set_style_border_width(ui_brightnessSlider, 2,
                                LV_PART_KNOB | LV_STATE_DEFAULT);
  lv_obj_set_style_radius(ui_brightnessSlider, LV_RADIUS_CIRCLE,
                          LV_PART_KNOB | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_all(ui_brightnessSlider, 15,
                           LV_PART_KNOB |
                               LV_STATE_DEFAULT); // Hace el knob más grande

  // Añadir el icono del sol DENTRO del slider (posicionado sobre el knob
  // mediante un label alineado pero eso es difícil dinámico, es más fácil
  // ponerlo fijo a la izquierda o añadirlo al knob si el tema lo permite) En
  // LVGL 8, no hay hijo directo para el knob transparente, así que los iconos a
  // los lados son la convención más fácil. Pongamos un icono fijo a la
  // izquierda del slider y la etiqueta a la derecha.

  lv_obj_t *sun_icon = lv_label_create(ui_config_brightness);
  lv_obj_align_to(sun_icon, ui_brightnessSlider, LV_ALIGN_OUT_LEFT_MID, -20, 0);
  lv_label_set_text(sun_icon, "\xE2\x98\x80"); // Sun icon ☀
  lv_obj_set_style_text_color(sun_icon, UI_COLOR_TEXT_INFO,
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_font(
      sun_icon, &ui_font_symbols_24,
      LV_PART_MAIN | LV_STATE_DEFAULT); // Fuente exclusivamente de símbolos

  // Label del porcentaje a la derecha (calculamos el inicial)
  ui_brightnessValLabel = lv_label_create(ui_config_brightness);
  lv_obj_align_to(ui_brightnessValLabel, ui_brightnessSlider,
                  LV_ALIGN_OUT_RIGHT_MID, 20, 0);
  {
    int pct = (current_brightness * 100) / 255;
    char buf[16];
    snprintf(buf, sizeof(buf), "%d%%", pct);
    lv_label_set_text(ui_brightnessValLabel, buf);
  }
  lv_obj_set_style_text_color(ui_brightnessValLabel, UI_COLOR_TEXT_ACTIVE,
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_font(ui_brightnessValLabel, &ui_font_Qualy24,
                             LV_PART_MAIN | LV_STATE_DEFAULT);

  // Registrar evento local
  lv_obj_add_event_cb(ui_brightnessSlider, brightness_slider_cb,
                      LV_EVENT_VALUE_CHANGED, NULL);
  lv_obj_add_event_cb(ui_config_brightness, ui_event_config_brightness,
                      LV_EVENT_ALL, NULL);

  // Botón apagar pantalla (más corto y solo "Apagar")
  lv_obj_t *ui_turnOffBtn = lv_btn_create(ui_config_brightness);
  lv_obj_set_width(ui_turnOffBtn, 140);
  lv_obj_set_height(ui_turnOffBtn, 60);
  lv_obj_set_align(ui_turnOffBtn, LV_ALIGN_TOP_MID);
  lv_obj_set_y(ui_turnOffBtn, 140);
  lv_obj_set_style_bg_color(ui_turnOffBtn, lv_color_hex(0x666666),
                            LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_radius(ui_turnOffBtn, 15, LV_PART_MAIN | LV_STATE_DEFAULT);

  lv_obj_t *ui_turnOffLabel = lv_label_create(ui_turnOffBtn);
  lv_label_set_text(ui_turnOffLabel, "Apagar");
  lv_obj_center(ui_turnOffLabel);
  lv_obj_set_style_text_font(ui_turnOffLabel, &ui_font_Qualy14,
                             LV_PART_MAIN | LV_STATE_DEFAULT);

  lv_obj_add_event_cb(ui_turnOffBtn, turn_off_btn_cb, LV_EVENT_CLICKED, NULL);

  // Swipe Hint: Triangulo apuntando hacia arriba en la parte inferior (is_top =
  // false)
  lv_obj_t *hint = ui_swipe_hint_create(ui_config_brightness, false);
}

void ui_config_brightness_screen_destroy(void) {
  if (ui_config_brightness)
    lv_obj_del(ui_config_brightness);
  ui_config_brightness = NULL;
  ui_brightnessSlider = NULL;
  ui_brightnessValLabel = NULL;
}
