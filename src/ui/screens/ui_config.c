// Pantalla de Configuración 1 – WiFi y Reiniciar
// LVGL version: 8.3.11

#include "ui_config.h"
#include "../components/ui_comp_navdots.h"
#include "../ui.h"
#include "../ui_events.h"
#include "../ui_swipe_hint.h"
#include <stdio.h>

extern const lv_font_t ui_font_symbols_24;

lv_obj_t *ui_config = NULL;
lv_obj_t *ui_wifiBtn = NULL;
lv_obj_t *ui_wifiBtnIcon = NULL;
lv_obj_t *ui_wifiBtnLabel = NULL;
lv_obj_t *ui_restartBtn = NULL;
lv_obj_t *ui_restartBtnIcon = NULL;
lv_obj_t *ui_restartBtnLabel = NULL;

// Variables estáticas para los modales
static lv_obj_t *active_modal = NULL;
static lv_obj_t *modal_overlay = NULL;
static bool pending_wifi_state = false; // estado al que queremos cambiar

// Callback para cerrar cualquier modal
static void close_modal_cb(lv_event_t *e) {
  if (modal_overlay) {
    lv_obj_del(modal_overlay);
    modal_overlay = NULL;
    active_modal = NULL;
  }
}

// Helpers para crear el modal
static void create_modal_overlay(void) {
  if (modal_overlay)
    return;

  modal_overlay = lv_obj_create(ui_config);
  lv_obj_set_width(modal_overlay, lv_pct(100));
  lv_obj_set_height(modal_overlay, lv_pct(100));
  lv_obj_set_style_bg_color(modal_overlay, UI_COLOR_MODAL_OVERLAY,
                            LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(modal_overlay, 200, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_border_width(modal_overlay, 0,
                                LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_radius(modal_overlay, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  // Interceptar clicks fuera del modal
  lv_obj_add_flag(modal_overlay, LV_OBJ_FLAG_CLICKABLE);
}

static lv_obj_t *create_modal_card(const char *title) {
  create_modal_overlay();

  lv_obj_t *card = lv_obj_create(modal_overlay);
  lv_obj_set_width(card, 300);
  lv_obj_set_height(card, LV_SIZE_CONTENT);
  lv_obj_set_align(card, LV_ALIGN_CENTER);
  lv_obj_set_flex_flow(card, LV_FLEX_FLOW_COLUMN);
  lv_obj_set_flex_align(card, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER,
                        LV_FLEX_ALIGN_START);

  lv_obj_set_style_bg_color(card, UI_COLOR_CARD_BG,
                            LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(card, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_border_color(card, UI_COLOR_TEXT_INFO,
                                LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_border_width(card, 1, LV_PART_MAIN | LV_STATE_DEFAULT);

  lv_obj_t *title_label = lv_label_create(card);
  lv_label_set_text(title_label, title);
  lv_obj_set_style_text_color(title_label, UI_COLOR_TEXT_INFO,
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_font(title_label, &ui_font_Qualy24,
                             LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_label_set_long_mode(title_label, LV_LABEL_LONG_WRAP);
  lv_obj_set_style_text_align(title_label, LV_TEXT_ALIGN_CENTER,
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_width(title_label, lv_pct(100));
  lv_obj_set_style_pad_bottom(title_label, 30, LV_PART_MAIN | LV_STATE_DEFAULT);

  return card;
}

static lv_obj_t *create_modal_buttons(lv_obj_t *card,
                                      lv_event_cb_t confirm_cb) {
  lv_obj_t *btn_row = lv_obj_create(card);
  lv_obj_set_width(btn_row, lv_pct(100));
  lv_obj_set_height(btn_row, LV_SIZE_CONTENT);
  lv_obj_set_flex_flow(btn_row, LV_FLEX_FLOW_ROW);
  lv_obj_set_flex_align(btn_row, LV_FLEX_ALIGN_SPACE_EVENLY,
                        LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
  lv_obj_set_style_bg_opa(btn_row, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_border_width(btn_row, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

  // Botón Cancelar
  lv_obj_t *btn_cancel = lv_btn_create(btn_row);
  lv_obj_set_height(btn_cancel, 65);
  lv_obj_set_style_bg_color(btn_cancel, lv_color_hex(0x666666),
                            LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_t *label_cancel = lv_label_create(btn_cancel);
  lv_obj_set_style_text_font(label_cancel, &ui_font_Qualy14,
                             LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_label_set_text(label_cancel, "Cancelar");
  lv_obj_add_event_cb(btn_cancel, close_modal_cb, LV_EVENT_CLICKED, NULL);

  // Botón Confirmar
  lv_obj_t *btn_confirm = lv_btn_create(btn_row);
  lv_obj_set_height(btn_confirm, 65);
  lv_obj_set_style_bg_color(btn_confirm, UI_COLOR_ACCENT,
                            LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_t *label_confirm = lv_label_create(btn_confirm);
  lv_obj_set_style_text_font(label_confirm, &ui_font_Qualy14,
                             LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_label_set_text(label_confirm, "Confirmar");
  lv_obj_add_event_cb(btn_confirm, confirm_cb, LV_EVENT_CLICKED, NULL);
  lv_obj_add_event_cb(btn_confirm, close_modal_cb, LV_EVENT_CLICKED,
                      NULL); // cerrar tras confirmar

  return btn_row;
}

// Callback cuando se confirma en el modal de WiFi
static void modal_confirm_wifi_cb(lv_event_t *e) {
  // Llamar a main.cpp
  onWifiConfirm(pending_wifi_state);

  // Aquí idealmente leeríamos el estado real, pero como es asíncrono,
  // actualizamos la UI asumiendo que el comando se envió.
  // En un sistema real, un evento del WiFi actualizaría este label.
  if (pending_wifi_state) {
    lv_label_set_text(ui_wifiBtnLabel, "WiFi: ACTIVO");
    lv_obj_set_style_bg_color(ui_wifiBtn, lv_color_hex(0x2E7D32),
                              LV_PART_MAIN | LV_STATE_DEFAULT); // Verde oscuro
  } else {
    lv_label_set_text(ui_wifiBtnLabel, "WiFi: INACTIVO");
    lv_obj_set_style_bg_color(ui_wifiBtn, lv_color_hex(0xC62828),
                              LV_PART_MAIN | LV_STATE_DEFAULT); // Rojo oscuro
  }
}

// Callback del botón de WiFi
static void wifi_btn_cb(lv_event_t *e) {
  // Asumimos el estado leyendo el texto actual (hack simple para UI)
  const char *current_text = lv_label_get_text(ui_wifiBtnLabel);
  bool is_currently_active = strstr(current_text, "ACTIVO") != NULL &&
                             strstr(current_text, "INACTIVO") == NULL;

  pending_wifi_state = !is_currently_active; // Invertir estado

  const char *title = pending_wifi_state ? "Encender WiFi" : "Apagar WiFi";
  lv_obj_t *card = create_modal_card(title);
  create_modal_buttons(card, modal_confirm_wifi_cb);
}

static void do_restart_timer_cb(lv_timer_t * timer) {
    onRestartConfirm();
}

// Callback cuando se confirma el reinicio
static void modal_confirm_restart_cb(lv_event_t *e) {
    lv_obj_t * btn = lv_event_get_target(e);
    lv_obj_t * btn_row = lv_obj_get_parent(btn);
    lv_obj_t * card = lv_obj_get_parent(btn_row);
    
    // Obtenemos el title_label (índice 0 del card)
    lv_obj_t * title_label = lv_obj_get_child(card, 0);
    lv_label_set_text(title_label, "Reiniciando...");
    
    // Ocultar botones
    lv_obj_add_flag(btn_row, LV_OBJ_FLAG_HIDDEN);
    
    // Llamar a reiniciar despues de 200 ms para permitir que LVGL dibuje el texto
    lv_timer_create(do_restart_timer_cb, 200, NULL);
}

// Callback del botón de reiniciar
static void restart_btn_cb(lv_event_t *e) {
  lv_obj_t *card = create_modal_card("Reiniciar Dispositivo");
  
  lv_obj_t *btn_row = lv_obj_create(card);
  lv_obj_set_width(btn_row, lv_pct(100));
  lv_obj_set_height(btn_row, LV_SIZE_CONTENT);
  lv_obj_set_flex_flow(btn_row, LV_FLEX_FLOW_ROW);
  lv_obj_set_flex_align(btn_row, LV_FLEX_ALIGN_SPACE_EVENLY, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
  lv_obj_set_style_bg_opa(btn_row, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_border_width(btn_row, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

  // Botón Cancelar
  lv_obj_t *btn_cancel = lv_btn_create(btn_row);
  lv_obj_set_height(btn_cancel, 65);
  lv_obj_set_style_bg_color(btn_cancel, lv_color_hex(0x666666), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_t *label_cancel = lv_label_create(btn_cancel);
  lv_obj_set_style_text_font(label_cancel, &ui_font_Qualy14, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_label_set_text(label_cancel, "Cancelar");
  lv_obj_add_event_cb(btn_cancel, close_modal_cb, LV_EVENT_CLICKED, NULL);

  // Botón Confirmar
  lv_obj_t *btn_confirm = lv_btn_create(btn_row);
  lv_obj_set_height(btn_confirm, 65);
  lv_obj_set_style_bg_color(btn_confirm, UI_COLOR_ACCENT, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_t *label_confirm = lv_label_create(btn_confirm);
  lv_obj_set_style_text_font(label_confirm, &ui_font_Qualy14, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_label_set_text(label_confirm, "Confirmar");
  lv_obj_add_event_cb(btn_confirm, modal_confirm_restart_cb, LV_EVENT_CLICKED, NULL);
}

// Eventos de la pantalla principal
void ui_event_config(lv_event_t *e) {
  lv_event_code_t event_code = lv_event_get_code(e);

  // Swipe LEFT: ir a Config Brightness (pág 2)
  if (event_code == LV_EVENT_GESTURE &&
      lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_LEFT) {
    lv_indev_wait_release(lv_indev_get_act());
    ui_last_config_index = 1;
    _ui_screen_change(&ui_config_brightness, UI_ANIM_SWIPE_LEFT,
                      UI_ANIM_SWIPE_DURATION, UI_ANIM_SWIPE_DELAY,
                      &ui_config_brightness_screen_init);
  }

  // Swipe RIGHT: Regresar a Config Brightness de forma cíclica (pág 2)
  if (event_code == LV_EVENT_GESTURE &&
      lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_RIGHT) {
    lv_indev_wait_release(lv_indev_get_act());
    ui_last_config_index = 1;
    _ui_screen_change(&ui_config_brightness, UI_ANIM_SWIPE_RIGHT,
                      UI_ANIM_SWIPE_DURATION, UI_ANIM_SWIPE_DELAY,
                      &ui_config_brightness_screen_init);
  }

  // Swipe UP (TOP): regresar a la última pantalla
  if (event_code == LV_EVENT_GESTURE &&
      lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_TOP) {
    lv_indev_wait_release(lv_indev_get_act());
    _ui_screen_change_by_index(ui_last_screen_index);
  }
}

void ui_config_screen_init(void) {
  ui_config = lv_obj_create(NULL);
  lv_obj_clear_flag(ui_config, LV_OBJ_FLAG_SCROLLABLE);
  lv_obj_set_style_bg_color(ui_config, UI_COLOR_BG,
                            LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(ui_config, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

  ui_navDots_create(ui_config, 2, 0); // 2 dots, estamos en el primero (index 0)

  // Contenedor layout para centrar los botones
  lv_obj_t *main_container = lv_obj_create(ui_config);
  lv_obj_set_width(main_container, lv_pct(80));  // 80% del ancho
  lv_obj_set_height(main_container, lv_pct(70)); // 70% del alto
  lv_obj_set_align(main_container, LV_ALIGN_CENTER);
  lv_obj_set_flex_flow(main_container, LV_FLEX_FLOW_COLUMN);
  lv_obj_set_flex_align(main_container, LV_FLEX_ALIGN_SPACE_EVENLY,
                        LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
  lv_obj_set_style_bg_opa(main_container, 0,
                          LV_PART_MAIN | LV_STATE_DEFAULT); // Transparente
  lv_obj_set_style_border_width(main_container, 0,
                                LV_PART_MAIN | LV_STATE_DEFAULT);

  // Gran Botón WiFi
  ui_wifiBtn = lv_btn_create(main_container);
  lv_obj_set_width(ui_wifiBtn, lv_pct(100));
  lv_obj_set_height(ui_wifiBtn, 60); // Botón alto
  // Empezamos asumiendo inactivo (rojo) por defecto
  lv_obj_set_style_bg_color(ui_wifiBtn, lv_color_hex(0xC62828),
                            LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_radius(ui_wifiBtn, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_flex_flow(ui_wifiBtn, LV_FLEX_FLOW_ROW);
  lv_obj_set_flex_align(ui_wifiBtn, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER,
                        LV_FLEX_ALIGN_CENTER);
  lv_obj_set_style_pad_column(ui_wifiBtn, 10, LV_PART_MAIN | LV_STATE_DEFAULT);

  ui_wifiBtnLabel = lv_label_create(ui_wifiBtn);
  if (is_wifi_enabled) {
    lv_label_set_text(ui_wifiBtnLabel, "WiFi: ACTIVO");
    lv_obj_set_style_bg_color(ui_wifiBtn, lv_color_hex(0x2E7D32),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  } else {
    lv_label_set_text(ui_wifiBtnLabel, "WiFi: INACTIVO");
    lv_obj_set_style_bg_color(ui_wifiBtn, lv_color_hex(0xC62828),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  }
  lv_obj_set_style_text_font(ui_wifiBtnLabel, &ui_font_Qualy24,
                             LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_add_event_cb(ui_wifiBtn, wifi_btn_cb, LV_EVENT_CLICKED, NULL);

  // Gran Botón Reiniciar
  ui_restartBtn = lv_btn_create(main_container);
  lv_obj_set_width(ui_restartBtn, lv_pct(100));
  lv_obj_set_height(ui_restartBtn, 60);
  lv_obj_set_style_bg_color(ui_restartBtn, UI_COLOR_ACCENT,
                            LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_radius(ui_restartBtn, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_flex_flow(ui_restartBtn, LV_FLEX_FLOW_ROW);
  lv_obj_set_flex_align(ui_restartBtn, LV_FLEX_ALIGN_CENTER,
                        LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
  lv_obj_set_style_pad_column(ui_restartBtn, 10,
                              LV_PART_MAIN | LV_STATE_DEFAULT);

  ui_restartBtnLabel = lv_label_create(ui_restartBtn);
  lv_label_set_text(ui_restartBtnLabel, "Reiniciar Dispositivo");
  lv_obj_set_style_text_font(ui_restartBtnLabel, &ui_font_Qualy24,
                             LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_add_event_cb(ui_restartBtn, restart_btn_cb, LV_EVENT_CLICKED, NULL);

  lv_obj_add_event_cb(ui_config, ui_event_config, LV_EVENT_ALL, NULL);

  // Indicador de Swipe (▲) - en la configuracion debe ir ABAJO
  ui_swipe_hint_create(ui_config, false);
}

void ui_config_screen_destroy(void) {
  if (ui_config)
    lv_obj_del(ui_config);
  ui_config = NULL;
  ui_wifiBtn = NULL;
  ui_wifiBtnIcon = NULL;
  ui_wifiBtnLabel = NULL;
  ui_restartBtn = NULL;
  ui_restartBtnIcon = NULL;
  ui_restartBtnLabel = NULL;
  modal_overlay = NULL;
  active_modal = NULL;
}
