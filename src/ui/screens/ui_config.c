// Pantalla de Configuración 1 – WiFi, Reiniciar y Factory Reset
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

// ================================================================
// MODAL HELPERS (Compartidos)
// ================================================================

// Callback para cerrar cualquier modal
static void close_modal_cb(lv_event_t *e) {
  if (modal_overlay) {
    lv_obj_del(modal_overlay);
    modal_overlay = NULL;
    active_modal = NULL;
  }
}

// Helpers para crear el modal estándar
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

// ================================================================
// WIFI MODAL
// ================================================================

// Callback cuando se confirma en el modal de WiFi
static void modal_confirm_wifi_cb(lv_event_t *e) {
  // Llamar a main.cpp
  onWifiConfirm(pending_wifi_state);

  if (pending_wifi_state) {
    lv_label_set_text(ui_wifiBtnLabel, "WiFi: ACTIVO");
    lv_obj_set_style_bg_color(ui_wifiBtn, lv_color_hex(0x2E7D32),
                              LV_PART_MAIN | LV_STATE_DEFAULT); // Verde oscuro
    lv_obj_set_style_text_color(ui_wifiBtnLabel, UI_COLOR_TEXT_ACTIVE,
                                LV_PART_MAIN | LV_STATE_DEFAULT);
  } else {
    lv_label_set_text(ui_wifiBtnLabel, "WiFi: INACTIVO");
    lv_obj_set_style_bg_color(ui_wifiBtn, lv_color_hex(0xC62828),
                              LV_PART_MAIN | LV_STATE_DEFAULT); // Rojo oscuro
    lv_obj_set_style_text_color(ui_wifiBtnLabel, UI_COLOR_TEXT_ACTIVE,
                                LV_PART_MAIN | LV_STATE_DEFAULT);
    
    // Si la última vista fue una gráfica, redirigir a la tercera (Dashboard - index 2)
    if (ui_last_screen_index == 3 || ui_last_screen_index == 4) {
      ui_last_screen_index = 2;
    }
  }
}

// Callback del botón de WiFi
static void wifi_btn_cb(lv_event_t *e) {
  // Si no hay credenciales, el botón no debería responder (está deshabilitado)
  if (!hw_has_wifi_credentials()) return;

  // Asumimos el estado leyendo el texto actual
  const char *current_text = lv_label_get_text(ui_wifiBtnLabel);
  bool is_currently_active = strstr(current_text, "ACTIVO") != NULL &&
                             strstr(current_text, "INACTIVO") == NULL;

  pending_wifi_state = !is_currently_active; // Invertir estado

  const char *title = pending_wifi_state ? "Encender WiFi" : "Apagar WiFi";
  lv_obj_t *card = create_modal_card(title);

  // Botones del modal
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
  lv_obj_add_event_cb(btn_confirm, modal_confirm_wifi_cb, LV_EVENT_CLICKED, NULL);
  lv_obj_add_event_cb(btn_confirm, close_modal_cb, LV_EVENT_CLICKED, NULL);
}

// ================================================================
// RESTART MODAL (Click corto)
// ================================================================

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

// Callback del botón de reiniciar (click corto)
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

// ================================================================
// LONG-PRESS DETECTION (Timer-based, 3 seconds)
// ================================================================

static lv_timer_t *long_press_timer = NULL;
static bool long_press_triggered = false;

// Forward declaration
static void restart_long_press_cb(lv_event_t *e);

// Timer callback: dispara el factory reset modal tras 3 segundos
static void long_press_timer_cb(lv_timer_t *timer) {
  long_press_triggered = true;
  long_press_timer = NULL;
  // Simular un "evento" llamando directamente a la función
  restart_long_press_cb(NULL);
}

// Callback cuando se presiona el botón (PRESSED)
static void restart_pressed_cb(lv_event_t *e) {
  long_press_triggered = false;
  // Crear timer de 3 segundos (one-shot)
  if (long_press_timer) {
    lv_timer_del(long_press_timer);
  }
  long_press_timer = lv_timer_create(long_press_timer_cb, UI_FACTORY_RESET_LONG_PRESS_MS, NULL);
  lv_timer_set_repeat_count(long_press_timer, 1); // Solo 1 vez
}

// Callback cuando se suelta el botón (RELEASED)
static void restart_released_cb(lv_event_t *e) {
  if (long_press_timer) {
    // Se soltó antes de 3s → Cancelar timer
    lv_timer_del(long_press_timer);
    long_press_timer = NULL;
  }
  
  if (!long_press_triggered && !modal_overlay) {
    // Click corto → Mostrar modal de reinicio normal
    restart_btn_cb(e);
  }
}

// ================================================================
// FACTORY RESET MODAL (Long-press 3s) — Estilo rojo de peligro
// ================================================================

static void do_factory_reset_timer_cb(lv_timer_t * timer) {
    hw_factory_reset();
}

// Callback cuando se confirma el factory reset
static void modal_confirm_factory_reset_cb(lv_event_t *e) {
    lv_obj_t * btn = lv_event_get_target(e);
    lv_obj_t * btn_row = lv_obj_get_parent(btn);
    lv_obj_t * card = lv_obj_get_parent(btn_row);
    
    // Cambiar titulo
    lv_obj_t * title_label = lv_obj_get_child(card, 0);
    lv_label_set_text(title_label, "Restableciendo...");
    lv_obj_set_style_text_color(title_label, UI_COLOR_DANGER,
                                LV_PART_MAIN | LV_STATE_DEFAULT);
    
    // Cambiar el subtitulo para indicar progreso
    lv_obj_t * subtitle = lv_obj_get_child(card, 1);
    if (subtitle) {
      lv_label_set_text(subtitle, "Borrando datos\ny reiniciando...");
      lv_obj_set_style_text_color(subtitle, UI_COLOR_TEXT_LABEL,
                                  LV_PART_MAIN | LV_STATE_DEFAULT);
    }
    
    // Ocultar botones
    lv_obj_add_flag(btn_row, LV_OBJ_FLAG_HIDDEN);
    
    // Ejecutar factory reset tras 300ms (tiempo para que LVGL dibuje)
    lv_timer_create(do_factory_reset_timer_cb, 300, NULL);
}

// Callback del long-press del botón de reiniciar → Modal Factory Reset
static void restart_long_press_cb(lv_event_t *e) {
  // Si ya hay un modal abierto, no abrir otro
  if (modal_overlay) return;
  
  // --- Crear overlay con tinte rojizo ---
  modal_overlay = lv_obj_create(ui_config);
  lv_obj_set_width(modal_overlay, lv_pct(100));
  lv_obj_set_height(modal_overlay, lv_pct(100));
  lv_obj_set_style_bg_color(modal_overlay, UI_COLOR_DANGER_OVERLAY,
                            LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(modal_overlay, 220, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_border_width(modal_overlay, 0,
                                LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_radius(modal_overlay, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_add_flag(modal_overlay, LV_OBJ_FLAG_CLICKABLE);

  // --- Card con estilo de peligro ---
  lv_obj_t *card = lv_obj_create(modal_overlay);
  lv_obj_set_width(card, 320);
  lv_obj_set_height(card, LV_SIZE_CONTENT);
  lv_obj_set_align(card, LV_ALIGN_CENTER);
  lv_obj_set_flex_flow(card, LV_FLEX_FLOW_COLUMN);
  lv_obj_set_flex_align(card, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER,
                        LV_FLEX_ALIGN_START);
  lv_obj_set_style_bg_color(card, UI_COLOR_DANGER_BG,
                            LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(card, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_border_color(card, UI_COLOR_DANGER_BORDER,
                                LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_border_width(card, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_radius(card, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_all(card, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_row(card, 12, LV_PART_MAIN | LV_STATE_DEFAULT);

  // --- Titulo ---
  lv_obj_t *title_label = lv_label_create(card);
  lv_label_set_text(title_label, "Restablecer dispositivo");
  lv_obj_set_style_text_color(title_label, UI_COLOR_DANGER,
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_font(title_label, &ui_font_Qualy24,
                             LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_align(title_label, LV_TEXT_ALIGN_CENTER,
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_width(title_label, lv_pct(100));

  // --- Descripcion ---
  lv_obj_t *desc_label = lv_label_create(card);
  lv_label_set_text(desc_label, 
    "Se borraran todas las\n"
    "configuraciones y el\n"
    "dispositivo volvera a\n"
    "su estado de fabrica.");
  lv_obj_set_style_text_color(desc_label, UI_COLOR_TEXT_LABEL,
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_font(desc_label, &ui_font_Qualy14,
                             LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_label_set_long_mode(desc_label, LV_LABEL_LONG_WRAP);
  lv_obj_set_style_text_align(desc_label, LV_TEXT_ALIGN_CENTER,
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_width(desc_label, lv_pct(100));
  lv_obj_set_style_pad_bottom(desc_label, 10, LV_PART_MAIN | LV_STATE_DEFAULT);

  // --- Fila de botones ---
  lv_obj_t *btn_row = lv_obj_create(card);
  lv_obj_set_width(btn_row, lv_pct(100));
  lv_obj_set_height(btn_row, LV_SIZE_CONTENT);
  lv_obj_set_flex_flow(btn_row, LV_FLEX_FLOW_ROW);
  lv_obj_set_flex_align(btn_row, LV_FLEX_ALIGN_SPACE_EVENLY,
                        LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
  lv_obj_set_style_bg_opa(btn_row, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_border_width(btn_row, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_top(btn_row, 5, LV_PART_MAIN | LV_STATE_DEFAULT);

  // --- Botón CANCELAR (resaltado / acción segura) ---
  lv_obj_t *btn_cancel = lv_btn_create(btn_row);
  lv_obj_set_width(btn_cancel, 140);
  lv_obj_set_height(btn_cancel, 65);
  lv_obj_set_style_bg_color(btn_cancel, UI_COLOR_SAFE_BTN,
                            LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_radius(btn_cancel, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
  // Efecto de brillo/sombra para resaltar como acción preferida
  lv_obj_set_style_shadow_color(btn_cancel, UI_COLOR_SAFE_BTN,
                                LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_shadow_width(btn_cancel, 15,
                                LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_shadow_opa(btn_cancel, 120,
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_t *label_cancel = lv_label_create(btn_cancel);
  lv_obj_set_align(label_cancel, LV_ALIGN_CENTER);
  lv_obj_set_style_text_font(label_cancel, &ui_font_Qualy14,
                             LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_color(label_cancel, UI_COLOR_TEXT_ACTIVE,
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_label_set_text(label_cancel, "Cancelar");
  lv_obj_add_event_cb(btn_cancel, close_modal_cb, LV_EVENT_CLICKED, NULL);

  // --- Botón RESTABLECER (peligroso, estilo sutil) ---
  lv_obj_t *btn_reset = lv_btn_create(btn_row);
  lv_obj_set_width(btn_reset, 120);
  lv_obj_set_height(btn_reset, 55);
  lv_obj_set_style_bg_color(btn_reset, lv_color_hex(0x2D0000),
                            LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_radius(btn_reset, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_border_color(btn_reset, UI_COLOR_DANGER,
                                LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_border_width(btn_reset, 1,
                                LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_t *label_reset = lv_label_create(btn_reset);
  lv_obj_set_align(label_reset, LV_ALIGN_CENTER);
  lv_obj_set_style_text_font(label_reset, &ui_font_Qualy12,
                             LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_color(label_reset, UI_COLOR_DANGER_DARK,
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_label_set_text(label_reset, "Restablecer");
  lv_obj_add_event_cb(btn_reset, modal_confirm_factory_reset_cb, LV_EVENT_CLICKED, NULL);

  active_modal = card;
}

// ================================================================
// SCREEN EVENTS (Swipe navigation)
// ================================================================

// Eventos de la pantalla principal
void ui_event_config(lv_event_t *e) {
  lv_event_code_t event_code = lv_event_get_code(e);

  // Bloquear swipes si hay un modal abierto O el boton de reinicio esta presionado
  // (evita navegacion accidental durante long-press o con modal visible)
  if ((modal_overlay || long_press_timer) && event_code == LV_EVENT_GESTURE) return;

  // Swipe LEFT: ir a Config Brightness (pág 2)
  if (event_code == LV_EVENT_GESTURE &&
      lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_LEFT) {
    lv_indev_wait_release(lv_indev_get_act());
    ui_last_config_index = 1;
    _ui_screen_change(&ui_config_brightness, UI_ANIM_SWIPE_LEFT,
                      UI_ANIM_SWIPE_DURATION, UI_ANIM_SWIPE_DELAY,
                      &ui_config_brightness_screen_init);
  }

  // Swipe RIGHT: Ir a la última pág (Burnout - pág 3)
  if (event_code == LV_EVENT_GESTURE &&
      lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_RIGHT) {
    lv_indev_wait_release(lv_indev_get_act());
    ui_last_config_index = 2;
    _ui_screen_change(&ui_burnout, UI_ANIM_SWIPE_RIGHT,
                      UI_ANIM_SWIPE_DURATION, UI_ANIM_SWIPE_DELAY,
                      &ui_burnout_screen_init);
  }

  // Swipe UP (TOP): regresar a la última pantalla
  if (event_code == LV_EVENT_GESTURE &&
      lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_TOP) {
    lv_indev_wait_release(lv_indev_get_act());
    _ui_screen_change_by_index(ui_last_screen_index);
  }
}

// ================================================================
// SCREEN INIT
// ================================================================

void ui_config_screen_init(void) {
  ui_config = lv_obj_create(NULL);
  lv_obj_clear_flag(ui_config, LV_OBJ_FLAG_SCROLLABLE);
  lv_obj_set_style_bg_color(ui_config, UI_COLOR_BG,
                            LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(ui_config, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

  ui_navDots_create(ui_config, 3, 0); // 3 dots, estamos en el primero (index 0)

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

  // ---- Gran Botón WiFi ----
  ui_wifiBtn = lv_btn_create(main_container);
  lv_obj_set_width(ui_wifiBtn, lv_pct(100));
  lv_obj_set_height(ui_wifiBtn, 60); // Botón alto
  lv_obj_set_style_radius(ui_wifiBtn, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_flex_flow(ui_wifiBtn, LV_FLEX_FLOW_ROW);
  lv_obj_set_flex_align(ui_wifiBtn, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER,
                        LV_FLEX_ALIGN_CENTER);
  lv_obj_set_style_pad_column(ui_wifiBtn, 10, LV_PART_MAIN | LV_STATE_DEFAULT);

  ui_wifiBtnLabel = lv_label_create(ui_wifiBtn);
  lv_obj_set_style_text_font(ui_wifiBtnLabel, &ui_font_Qualy24,
                             LV_PART_MAIN | LV_STATE_DEFAULT);

  // Configurar estado del botón WiFi según credenciales y estado
  if (!hw_has_wifi_credentials()) {
    // Sin credenciales → Botón DESHABILITADO
    lv_label_set_text(ui_wifiBtnLabel, "WiFi: SIN CONFIG");
    lv_obj_set_style_bg_color(ui_wifiBtn, UI_COLOR_BTN_DISABLED,
                              LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui_wifiBtnLabel, UI_COLOR_TEXT_INFO,
                                LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_state(ui_wifiBtn, LV_STATE_DISABLED);
    lv_obj_set_style_bg_color(ui_wifiBtn, UI_COLOR_BTN_DISABLED,
                              LV_PART_MAIN | LV_STATE_DISABLED);
    lv_obj_set_style_opa(ui_wifiBtn, 180, LV_PART_MAIN | LV_STATE_DISABLED);
  } else if (is_wifi_enabled) {
    lv_label_set_text(ui_wifiBtnLabel, "WiFi: ACTIVO");
    lv_obj_set_style_bg_color(ui_wifiBtn, lv_color_hex(0x2E7D32),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui_wifiBtnLabel, UI_COLOR_TEXT_ACTIVE,
                                LV_PART_MAIN | LV_STATE_DEFAULT);
  } else {
    lv_label_set_text(ui_wifiBtnLabel, "WiFi: INACTIVO");
    lv_obj_set_style_bg_color(ui_wifiBtn, lv_color_hex(0xC62828),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui_wifiBtnLabel, UI_COLOR_TEXT_ACTIVE,
                                LV_PART_MAIN | LV_STATE_DEFAULT);
  }
  lv_obj_add_event_cb(ui_wifiBtn, wifi_btn_cb, LV_EVENT_CLICKED, NULL);

  // ---- Gran Botón Reiniciar (click corto = reiniciar, long-press = factory reset) ----
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
  
  // Detección de press/release para distinguir click corto vs long-press (3s → factory reset)
  lv_obj_add_event_cb(ui_restartBtn, restart_pressed_cb, LV_EVENT_PRESSED, NULL);
  lv_obj_add_event_cb(ui_restartBtn, restart_released_cb, LV_EVENT_RELEASED, NULL);

  lv_obj_add_event_cb(ui_config, ui_event_config, LV_EVENT_ALL, NULL);

  // Indicador de Swipe (▲) - en la configuracion debe ir ABAJO
  ui_swipe_hint_create(ui_config, false);
}

void ui_config_screen_destroy(void) {
  // Limpiar timer de long-press si existe
  if (long_press_timer) {
    lv_timer_del(long_press_timer);
    long_press_timer = NULL;
  }
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
