SET(SOURCES components/ui_comp_navpanel.c
    components/ui_comp.c
    screens/ui_voltaje.c
    screens/ui_corriente.c
    screens/ui_dashboard.c
    screens/ui_Modo_Diario_24hrs.c
    screens/ui_statsWatts.c
    screens/ui_voltageStats.c
    screens/ui_diagnostic.c
    ui_theme_manager.c
    ui_themes.c
    ui.c
    components/ui_comp_hook.c
    ui_helpers.c
    fonts/ui_font_diagElem.c
    fonts/ui_font_diagTitle.c
    fonts/ui_font_LecturaS.c
    fonts/ui_font_LecturaS48.c
    fonts/ui_font_Micro_text.c
    fonts/ui_font_Secondary_info.c
    fonts/ui_font_Unidades.c
    fonts/ui_font_Valores.c)

add_library(ui ${SOURCES})
