// This file was modified to optimize elements, add a title, enable scrolling,
// and use global styling variables.
// LVGL version: 8.3.11

#include "../ui.h"

lv_obj_t * ui_diagnostic = NULL;
lv_obj_t * ui_diagTitle = NULL;
lv_obj_t * ui_contentPanel9 = NULL;
lv_obj_t * ui_redPanel = NULL;
lv_obj_t * ui_redLabel = NULL;
lv_obj_t * ui_ipPanel = NULL;
lv_obj_t * ui_elementLabel = NULL;
lv_obj_t * ui_elementVal = NULL;
lv_obj_t * ui_rssiPanel = NULL;
lv_obj_t * ui_elementLabel1 = NULL;
lv_obj_t * ui_elementVal1 = NULL;
lv_obj_t * ui_rssiBar = NULL;
lv_obj_t * ui_uptimePanel = NULL;
lv_obj_t * ui_elementLabel2 = NULL;
lv_obj_t * ui_elementVal3 = NULL;
lv_obj_t * ui_cloudPanel = NULL;
lv_obj_t * ui_cloudLabel = NULL;
lv_obj_t * ui_mqttPanel = NULL;
lv_obj_t * ui_elementLabel3 = NULL;
lv_obj_t * ui_elementVal4 = NULL;
lv_obj_t * ui_syncPanel = NULL;
lv_obj_t * ui_elementLabel5 = NULL;
lv_obj_t * ui_elementVal7 = NULL;
lv_obj_t * ui_hardPanel = NULL;
lv_obj_t * ui_hardLabel = NULL;
lv_obj_t * ui_macPanel = NULL;
lv_obj_t * ui_elementLabel4 = NULL;
lv_obj_t * ui_elementVal5 = NULL;
lv_obj_t * ui_pzemPanel = NULL;
lv_obj_t * ui_elementLabel6 = NULL;
lv_obj_t * ui_elementVal6 = NULL;
lv_obj_t * ui_heapPanel = NULL;
lv_obj_t * ui_elementLabel7 = NULL;
lv_obj_t * ui_elementVal8 = NULL;
lv_obj_t * ui_navPanel7 = NULL;

// event funtions
void ui_event_diagnostic(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if(event_code == LV_EVENT_GESTURE &&  lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_RIGHT) {
        lv_indev_wait_release(lv_indev_get_act());
        if (is_wifi_enabled) {
            _ui_screen_change(&ui_voltageStats, UI_ANIM_SWIPE_RIGHT, UI_ANIM_SWIPE_DURATION, UI_ANIM_SWIPE_DELAY, &ui_voltageStats_screen_init);
        } else {
            _ui_screen_change(&ui_dashboard, UI_ANIM_SWIPE_RIGHT, UI_ANIM_SWIPE_DURATION, UI_ANIM_SWIPE_DELAY, &ui_dashboard_screen_init);
        }
    }
    if(event_code == LV_EVENT_GESTURE &&  lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_LEFT) {
        lv_indev_wait_release(lv_indev_get_act());
        _ui_screen_change(&ui_voltaje, UI_ANIM_SWIPE_LEFT, UI_ANIM_SWIPE_DURATION, UI_ANIM_SWIPE_DELAY, &ui_voltaje_screen_init);
    }

}

// build funtions
void ui_diagnostic_screen_init(void)
{
    ui_diagnostic = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_diagnostic, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(ui_diagnostic, UI_COLOR_BG, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_diagnostic, UI_OPA_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);

    // --- Título de la pantalla ---
    ui_diagTitle = lv_label_create(ui_diagnostic);
    lv_obj_set_width(ui_diagTitle, lv_pct(100)); // Ancho completo para que actúe como banner
    lv_obj_set_height(ui_diagTitle, LV_SIZE_CONTENT);
    lv_obj_align(ui_diagTitle, LV_ALIGN_TOP_MID, 0, 0);
    lv_label_set_text(ui_diagTitle, "DIAGNOSTICO");
    lv_obj_set_style_text_align(ui_diagTitle, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui_diagTitle, UI_COLOR_TEXT_ACTIVE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_diagTitle, UI_FONT_DIAG_SECTION, LV_PART_MAIN | LV_STATE_DEFAULT); 
    lv_obj_set_style_bg_color(ui_diagTitle, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_diagTitle, UI_OPA_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_diagTitle, 15, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_diagTitle, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    
    // --- Contenedor Principal con Scroll ---
    ui_contentPanel9 = lv_obj_create(ui_diagnostic);
    lv_obj_set_height(ui_contentPanel9, lv_pct(70)); 
    lv_obj_set_width(ui_contentPanel9, lv_pct(100));
    lv_obj_align(ui_contentPanel9, LV_ALIGN_CENTER, 0, 0); 
    
    // Configuración Flexbox: Columna única infinita para habilitar el scroll
    lv_obj_set_flex_flow(ui_contentPanel9, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(ui_contentPanel9, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_set_style_pad_row(ui_contentPanel9, 15, LV_PART_MAIN | LV_STATE_DEFAULT); // Espacio entre secciones
    
    // Configuración Scroll
    lv_obj_add_flag(ui_contentPanel9, LV_OBJ_FLAG_SCROLLABLE); 
    lv_obj_set_scroll_dir(ui_contentPanel9, LV_DIR_VER);       
    lv_obj_set_scrollbar_mode(ui_contentPanel9, LV_SCROLLBAR_MODE_ON); 
    
    // Estilo visual del scrollbar
    lv_obj_set_style_bg_color(ui_contentPanel9, lv_color_hex(0x808080), LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_contentPanel9, 150, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_set_style_width(ui_contentPanel9, 5, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_contentPanel9, 2, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    
    // Quitar fondos y bordes molestos al contenedor
    lv_obj_set_style_bg_opa(ui_contentPanel9, UI_OPA_NONE, LV_PART_MAIN | LV_STATE_DEFAULT); 
    lv_obj_set_style_border_width(ui_contentPanel9, 0, LV_PART_MAIN | LV_STATE_DEFAULT); 

    // ================= SECCIÓN RED =================
    ui_redPanel = lv_obj_create(ui_contentPanel9);
    lv_obj_set_width(ui_redPanel, lv_pct(90));
    lv_obj_set_height(ui_redPanel, LV_SIZE_CONTENT);
    lv_obj_set_flex_flow(ui_redPanel, LV_FLEX_FLOW_COLUMN);
    lv_obj_clear_flag(ui_redPanel, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_opa(ui_redPanel, UI_OPA_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_redPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_redLabel = lv_label_create(ui_redPanel);
    lv_label_set_text(ui_redLabel, "RED");
    lv_obj_set_style_text_color(ui_redLabel, UI_COLOR_TEXT_ACTIVE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_redLabel, UI_FONT_DIAG_SECTION, LV_PART_MAIN | LV_STATE_DEFAULT);

    // IP Panel
    ui_ipPanel = lv_obj_create(ui_redPanel);
    lv_obj_set_width(ui_ipPanel, lv_pct(100));
    lv_obj_set_height(ui_ipPanel, LV_SIZE_CONTENT);
    lv_obj_set_flex_flow(ui_ipPanel, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(ui_ipPanel, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_clear_flag(ui_ipPanel, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_opa(ui_ipPanel, UI_OPA_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_ipPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_elementLabel = lv_label_create(ui_ipPanel);
    lv_label_set_text(ui_elementLabel, "IP Local:"); 
    lv_obj_set_style_text_color(ui_elementLabel, UI_COLOR_TEXT_LABEL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_elementLabel, UI_FONT_DIAG_ELEMENT, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_elementVal = lv_label_create(ui_ipPanel);
    lv_label_set_text(ui_elementVal, "---.---.-.-");
    lv_obj_set_style_text_color(ui_elementVal, UI_COLOR_TEXT_LABEL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_elementVal, UI_FONT_DIAG_ELEMENT, LV_PART_MAIN | LV_STATE_DEFAULT);

    // RSSI Panel
    ui_rssiPanel = lv_obj_create(ui_redPanel);
    lv_obj_set_width(ui_rssiPanel, lv_pct(100));
    lv_obj_set_height(ui_rssiPanel, LV_SIZE_CONTENT);
    lv_obj_set_flex_flow(ui_rssiPanel, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(ui_rssiPanel, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_clear_flag(ui_rssiPanel, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_opa(ui_rssiPanel, UI_OPA_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_rssiPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_elementLabel1 = lv_label_create(ui_rssiPanel);
    lv_label_set_text(ui_elementLabel1, "RSSI:");
    lv_obj_set_style_text_color(ui_elementLabel1, UI_COLOR_TEXT_LABEL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_elementLabel1, UI_FONT_DIAG_ELEMENT, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_elementVal1 = lv_label_create(ui_rssiPanel);
    lv_label_set_text(ui_elementVal1, "-- dBm"); 
    lv_obj_set_style_text_color(ui_elementVal1, UI_COLOR_TEXT_LABEL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_elementVal1, UI_FONT_DIAG_ELEMENT, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_rssiBar = lv_bar_create(ui_rssiPanel);
    lv_obj_set_width(ui_rssiBar, 100);
    lv_obj_set_height(ui_rssiBar, 15);
    lv_bar_set_range(ui_rssiBar, 0, 100);
    lv_bar_set_value(ui_rssiBar, 0, LV_ANIM_OFF);
    
    // Monochromatic style for the bar
    lv_obj_set_style_bg_color(ui_rssiBar, UI_COLOR_SLIDER_TRACK, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_rssiBar, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui_rssiBar, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(ui_rssiBar, UI_COLOR_TEXT_ACTIVE, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_rssiBar, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui_rssiBar, 5, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    // Uptime Panel
    ui_uptimePanel = lv_obj_create(ui_redPanel);
    lv_obj_set_width(ui_uptimePanel, lv_pct(100));
    lv_obj_set_height(ui_uptimePanel, LV_SIZE_CONTENT);
    lv_obj_set_flex_flow(ui_uptimePanel, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(ui_uptimePanel, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_clear_flag(ui_uptimePanel, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_opa(ui_uptimePanel, UI_OPA_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_uptimePanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_elementLabel2 = lv_label_create(ui_uptimePanel);
    lv_label_set_text(ui_elementLabel2, "Uptime:");
    lv_obj_set_style_text_color(ui_elementLabel2, UI_COLOR_TEXT_LABEL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_elementLabel2, UI_FONT_DIAG_ELEMENT, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_elementVal3 = lv_label_create(ui_uptimePanel);
    lv_label_set_text(ui_elementVal3, "---------");
    lv_obj_set_style_text_color(ui_elementVal3, UI_COLOR_TEXT_LABEL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_elementVal3, UI_FONT_DIAG_ELEMENT, LV_PART_MAIN | LV_STATE_DEFAULT);


    // ================= SECCIÓN CLOUD =================
    ui_cloudPanel = lv_obj_create(ui_contentPanel9);
    lv_obj_set_width(ui_cloudPanel, lv_pct(90));
    lv_obj_set_height(ui_cloudPanel, LV_SIZE_CONTENT);
    lv_obj_set_flex_flow(ui_cloudPanel, LV_FLEX_FLOW_COLUMN);
    lv_obj_clear_flag(ui_cloudPanel, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_opa(ui_cloudPanel, UI_OPA_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_cloudPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_cloudLabel = lv_label_create(ui_cloudPanel);
    lv_label_set_text(ui_cloudLabel, "CLOUD");
    lv_obj_set_style_text_color(ui_cloudLabel, UI_COLOR_TEXT_ACTIVE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_cloudLabel, UI_FONT_DIAG_SECTION, LV_PART_MAIN | LV_STATE_DEFAULT);

    // MQTT Panel
    ui_mqttPanel = lv_obj_create(ui_cloudPanel);
    lv_obj_set_width(ui_mqttPanel, lv_pct(100));
    lv_obj_set_height(ui_mqttPanel, LV_SIZE_CONTENT);
    lv_obj_set_flex_flow(ui_mqttPanel, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(ui_mqttPanel, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_clear_flag(ui_mqttPanel, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_opa(ui_mqttPanel, UI_OPA_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_mqttPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_elementLabel3 = lv_label_create(ui_mqttPanel);
    lv_label_set_text(ui_elementLabel3, "MQTT Broker:");
    lv_obj_set_style_text_color(ui_elementLabel3, UI_COLOR_TEXT_LABEL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_elementLabel3, UI_FONT_DIAG_ELEMENT, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_elementVal4 = lv_label_create(ui_mqttPanel);
    lv_label_set_text(ui_elementVal4, "-----");
    lv_obj_set_style_text_color(ui_elementVal4, UI_COLOR_TEXT_LABEL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_elementVal4, UI_FONT_DIAG_ELEMENT, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Sync Panel
    ui_syncPanel = lv_obj_create(ui_cloudPanel);
    lv_obj_set_width(ui_syncPanel, lv_pct(100));
    lv_obj_set_height(ui_syncPanel, LV_SIZE_CONTENT);
    lv_obj_set_flex_flow(ui_syncPanel, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(ui_syncPanel, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_clear_flag(ui_syncPanel, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_opa(ui_syncPanel, UI_OPA_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_syncPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_elementLabel5 = lv_label_create(ui_syncPanel);
    lv_label_set_text(ui_elementLabel5, "Last Sync:");
    lv_obj_set_style_text_color(ui_elementLabel5, UI_COLOR_TEXT_LABEL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_elementLabel5, UI_FONT_DIAG_ELEMENT, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_elementVal7 = lv_label_create(ui_syncPanel);
    lv_label_set_text(ui_elementVal7, "---------");
    lv_obj_set_style_text_color(ui_elementVal7, UI_COLOR_TEXT_LABEL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_elementVal7, UI_FONT_DIAG_ELEMENT, LV_PART_MAIN | LV_STATE_DEFAULT);


    // ================= SECCIÓN HARDWARE =================
    ui_hardPanel = lv_obj_create(ui_contentPanel9);
    lv_obj_set_width(ui_hardPanel, lv_pct(90));
    lv_obj_set_height(ui_hardPanel, LV_SIZE_CONTENT);
    lv_obj_set_flex_flow(ui_hardPanel, LV_FLEX_FLOW_COLUMN);
    lv_obj_clear_flag(ui_hardPanel, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_opa(ui_hardPanel, UI_OPA_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_hardPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_hardPanel, 20, LV_PART_MAIN | LV_STATE_DEFAULT); // Espacio extra al final del scroll

    ui_hardLabel = lv_label_create(ui_hardPanel);
    lv_label_set_text(ui_hardLabel, "HARDWARE");
    lv_obj_set_style_text_color(ui_hardLabel, UI_COLOR_TEXT_ACTIVE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_hardLabel, UI_FONT_DIAG_SECTION, LV_PART_MAIN | LV_STATE_DEFAULT);

    // MAC Panel
    ui_macPanel = lv_obj_create(ui_hardPanel);
    lv_obj_set_width(ui_macPanel, lv_pct(100));
    lv_obj_set_height(ui_macPanel, LV_SIZE_CONTENT);
    lv_obj_set_flex_flow(ui_macPanel, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(ui_macPanel, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_clear_flag(ui_macPanel, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_opa(ui_macPanel, UI_OPA_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_macPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_elementLabel4 = lv_label_create(ui_macPanel);
    lv_label_set_text(ui_elementLabel4, "MAC:");
    lv_obj_set_style_text_color(ui_elementLabel4, UI_COLOR_TEXT_LABEL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_elementLabel4, UI_FONT_DIAG_ELEMENT, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_elementVal5 = lv_label_create(ui_macPanel);
    lv_label_set_text(ui_elementVal5, "-----------");
    lv_obj_set_style_text_color(ui_elementVal5, UI_COLOR_TEXT_LABEL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_elementVal5, UI_FONT_DIAG_ELEMENT, LV_PART_MAIN | LV_STATE_DEFAULT);

    // PZEM Panel
    ui_pzemPanel = lv_obj_create(ui_hardPanel);
    lv_obj_set_width(ui_pzemPanel, lv_pct(100));
    lv_obj_set_height(ui_pzemPanel, LV_SIZE_CONTENT);
    lv_obj_set_flex_flow(ui_pzemPanel, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(ui_pzemPanel, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_clear_flag(ui_pzemPanel, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_opa(ui_pzemPanel, UI_OPA_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_pzemPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_elementLabel6 = lv_label_create(ui_pzemPanel);
    lv_label_set_text(ui_elementLabel6, "PZEM:");
    lv_obj_set_style_text_color(ui_elementLabel6, UI_COLOR_TEXT_LABEL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_elementLabel6, UI_FONT_DIAG_ELEMENT, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_elementVal6 = lv_label_create(ui_pzemPanel);
    lv_label_set_text(ui_elementVal6, "-----------");
    lv_obj_set_style_text_color(ui_elementVal6, UI_COLOR_TEXT_LABEL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_elementVal6, UI_FONT_DIAG_ELEMENT, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Heap Panel
    ui_heapPanel = lv_obj_create(ui_hardPanel);
    lv_obj_set_width(ui_heapPanel, lv_pct(100));
    lv_obj_set_height(ui_heapPanel, LV_SIZE_CONTENT);
    lv_obj_set_flex_flow(ui_heapPanel, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(ui_heapPanel, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_clear_flag(ui_heapPanel, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_opa(ui_heapPanel, UI_OPA_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_heapPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_elementLabel7 = lv_label_create(ui_heapPanel);
    lv_label_set_text(ui_elementLabel7, "Heap:");
    lv_obj_set_style_text_color(ui_elementLabel7, UI_COLOR_TEXT_LABEL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_elementLabel7, UI_FONT_DIAG_ELEMENT, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_elementVal8 = lv_label_create(ui_heapPanel);
    lv_label_set_text(ui_elementVal8, "------/-----");
    lv_obj_set_style_text_color(ui_elementVal8, UI_COLOR_TEXT_LABEL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_elementVal8, UI_FONT_DIAG_ELEMENT, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Componente Navegación Inferior
    ui_navPanel7 = ui_navPanel_create(ui_diagnostic);
    lv_obj_align(ui_navPanel7, LV_ALIGN_BOTTOM_MID, 0, 0); 
    lv_obj_set_style_bg_color(ui_comp_get_child(ui_navPanel7, UI_COMP_NAVPANEL_CIRCLE6), UI_COLOR_TEXT_ACTIVE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_comp_get_child(ui_navPanel7, UI_COMP_NAVPANEL_CIRCLE6), 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(ui_diagnostic, ui_event_diagnostic, LV_EVENT_ALL, NULL);

    // Asegurar que el título siempre esté por encima del contenido que se desplaza
    lv_obj_move_foreground(ui_diagTitle);
}

void ui_diagnostic_screen_destroy(void)
{
    if(ui_diagnostic) lv_obj_del(ui_diagnostic);

    // NULL screen variables
    ui_diagnostic = NULL;
    ui_diagTitle = NULL;
    ui_contentPanel9 = NULL;
    ui_redPanel = NULL;
    ui_redLabel = NULL;
    ui_ipPanel = NULL;
    ui_elementLabel = NULL;
    ui_elementVal = NULL;
    ui_rssiPanel = NULL;
    ui_elementLabel1 = NULL;
    ui_elementVal1 = NULL;
    ui_rssiBar = NULL;
    ui_uptimePanel = NULL;
    ui_elementLabel2 = NULL;
    ui_elementVal3 = NULL;
    ui_cloudPanel = NULL;
    ui_cloudLabel = NULL;
    ui_mqttPanel = NULL;
    ui_elementLabel3 = NULL;
    ui_elementVal4 = NULL;
    ui_syncPanel = NULL;
    ui_elementLabel5 = NULL;
    ui_elementVal7 = NULL;
    ui_hardPanel = NULL;
    ui_hardLabel = NULL;
    ui_macPanel = NULL;
    ui_elementLabel4 = NULL;
    ui_elementVal5 = NULL;
    ui_pzemPanel = NULL;
    ui_elementLabel6 = NULL;
    ui_elementVal6 = NULL;
    ui_heapPanel = NULL;
    ui_elementLabel7 = NULL;
    ui_elementVal8 = NULL;
    ui_navPanel7 = NULL;
}