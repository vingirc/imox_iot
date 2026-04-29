/**
 * @file ui_overlay.c
 * @brief Implementación de modales informativos globales.
 *
 * Se usan lv_layer_top() como padre para que el overlay se dibuje
 * sobre cualquier pantalla activa sin importar cuál sea.
 *
 * Estilo visual consistente con los modales de ui_config.c:
 *   - Overlay semi-transparente oscuro
 *   - Card centrada con esquinas redondeadas
 *   - Spinner animado + título + texto de progreso
 */

#include "ui_overlay.h"
#include "ui.h"

// ================================================================
// ESTADO INTERNO
// ================================================================

// --- Vinculación BLE ---
static lv_obj_t *linking_overlay = NULL;
static lv_obj_t *linking_status_label = NULL;

// --- Actualización OTA ---
static lv_obj_t *ota_overlay = NULL;
static lv_obj_t *ota_status_label = NULL;

// ================================================================
// HELPERS (Internos)
// ================================================================

/**
 * @brief Crea un overlay de pantalla completa sobre lv_layer_top().
 */
static lv_obj_t *create_global_overlay(lv_color_t bg_color, lv_opa_t bg_opa) {
    lv_obj_t *overlay = lv_obj_create(lv_layer_top());
    lv_obj_set_width(overlay, lv_pct(100));
    lv_obj_set_height(overlay, lv_pct(100));
    lv_obj_clear_flag(overlay, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(overlay, bg_color, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(overlay, bg_opa, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(overlay, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(overlay, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    // Interceptar toques para bloquear interacción con la pantalla de atrás
    lv_obj_add_flag(overlay, LV_OBJ_FLAG_CLICKABLE);
    return overlay;
}

/**
 * @brief Crea la card centrada estándar dentro del overlay.
 */
static lv_obj_t *create_overlay_card(lv_obj_t *parent, lv_color_t border_color) {
    lv_obj_t *card = lv_obj_create(parent);
    lv_obj_set_width(card, 300);
    lv_obj_set_height(card, LV_SIZE_CONTENT);
    lv_obj_set_align(card, LV_ALIGN_CENTER);
    lv_obj_clear_flag(card, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_flex_flow(card, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(card, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER,
                          LV_FLEX_ALIGN_CENTER);

    lv_obj_set_style_bg_color(card, UI_COLOR_CARD_BG,
                              LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(card, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(card, border_color,
                                  LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(card, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(card, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_all(card, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_row(card, 14, LV_PART_MAIN | LV_STATE_DEFAULT);

    return card;
}

/**
 * @brief Crea un spinner animado centrado.
 * @param arc_color Color del arco animado.
 */
static lv_obj_t *create_spinner(lv_obj_t *parent, lv_color_t arc_color) {
    lv_obj_t *spinner = lv_spinner_create(parent, 1000, 60);
    lv_obj_set_size(spinner, 50, 50);
    lv_obj_set_style_arc_width(spinner, 5, LV_PART_MAIN);
    lv_obj_set_style_arc_color(spinner, UI_COLOR_SEPARATOR, LV_PART_MAIN);
    lv_obj_set_style_arc_width(spinner, 5, LV_PART_INDICATOR);
    lv_obj_set_style_arc_color(spinner, arc_color, LV_PART_INDICATOR);
    return spinner;
}

// ================================================================
// MODAL DE VINCULACIÓN BLE
// ================================================================

void ui_overlay_show_linking(void) {
    if (linking_overlay) return; // Ya visible

    // Overlay con tono azulado suave
    linking_overlay = create_global_overlay(lv_color_hex(0x001030), 220);

    // Card
    lv_obj_t *card = create_overlay_card(linking_overlay, lv_color_hex(0x4488FF));

    // Spinner azul
    create_spinner(card, lv_color_hex(0x4488FF));

    // Título
    lv_obj_t *title = lv_label_create(card);
    lv_label_set_text(title, "Vinculando...");
    lv_obj_set_style_text_color(title, lv_color_hex(0x4488FF),
                                LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(title, &ui_font_Qualy24,
                               LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(title, LV_TEXT_ALIGN_CENTER,
                                LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_width(title, lv_pct(100));

    // Texto de estado (actualizable)
    linking_status_label = lv_label_create(card);
    lv_label_set_text(linking_status_label, "Dispositivo conectado");
    lv_obj_set_style_text_color(linking_status_label, UI_COLOR_TEXT_LABEL,
                                LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(linking_status_label, &ui_font_Qualy14,
                               LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_long_mode(linking_status_label, LV_LABEL_LONG_WRAP);
    lv_obj_set_style_text_align(linking_status_label, LV_TEXT_ALIGN_CENTER,
                                LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_width(linking_status_label, lv_pct(100));
}

void ui_overlay_update_linking(const char *msg) {
    if (linking_status_label && msg) {
        lv_label_set_text(linking_status_label, msg);
    }
}

void ui_overlay_hide_linking(void) {
    if (linking_overlay) {
        lv_obj_del(linking_overlay);
        linking_overlay = NULL;
        linking_status_label = NULL;
    }
}

// ================================================================
// MODAL DE ACTUALIZACIÓN OTA
// ================================================================

void ui_overlay_show_ota(const char *version) {
    if (ota_overlay) return; // Ya visible

    // Overlay con tono violeta/acento suave
    ota_overlay = create_global_overlay(lv_color_hex(0x1A0030), 220);

    // Card
    lv_obj_t *card = create_overlay_card(ota_overlay, UI_COLOR_ACCENT);

    // Spinner violeta (color acento del tema)
    create_spinner(card, UI_COLOR_ACCENT);

    // Título con la versión
    lv_obj_t *title = lv_label_create(card);
    static char title_buf[48];
    if (version && strlen(version) > 0) {
        lv_snprintf(title_buf, sizeof(title_buf), "Actualizando\na v%s", version);
    } else {
        lv_snprintf(title_buf, sizeof(title_buf), "Actualizando...");
    }
    lv_label_set_text(title, title_buf);
    lv_obj_set_style_text_color(title, UI_COLOR_ACCENT,
                                LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(title, &ui_font_Qualy24,
                               LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(title, LV_TEXT_ALIGN_CENTER,
                                LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_width(title, lv_pct(100));

    // Subtítulo de advertencia
    lv_obj_t *warn = lv_label_create(card);
    lv_label_set_text(warn, "No apague el\ndispositivo");
    lv_obj_set_style_text_color(warn, UI_COLOR_TEXT_INFO,
                                LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(warn, &ui_font_Qualy14,
                               LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_long_mode(warn, LV_LABEL_LONG_WRAP);
    lv_obj_set_style_text_align(warn, LV_TEXT_ALIGN_CENTER,
                                LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_width(warn, lv_pct(100));

    // Texto de estado (actualizable)
    ota_status_label = lv_label_create(card);
    lv_label_set_text(ota_status_label, "Iniciando...");
    lv_obj_set_style_text_color(ota_status_label, UI_COLOR_TEXT_LABEL,
                                LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ota_status_label, &ui_font_Qualy14,
                               LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_long_mode(ota_status_label, LV_LABEL_LONG_WRAP);
    lv_obj_set_style_text_align(ota_status_label, LV_TEXT_ALIGN_CENTER,
                                LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_width(ota_status_label, lv_pct(100));
}

void ui_overlay_update_ota(const char *step) {
    if (ota_status_label && step) {
        lv_label_set_text(ota_status_label, step);
    }
}

void ui_overlay_hide_ota(void) {
    if (ota_overlay) {
        lv_obj_del(ota_overlay);
        ota_overlay = NULL;
        ota_status_label = NULL;
    }
}
