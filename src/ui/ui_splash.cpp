/**
 * @file ui_splash.cpp
 * @brief Implementación de la pantalla de inicio con animaciones de brillo.
 * 
 * Secuencia replicada del proyecto legacy (WiFi_Manager_IMOX_v10):
 *   transicion_logo(120) → delay(4000) → transicion_out(120)
 *   → Mostrar modelo "IMOX-XX" → transicion_in(120) → delay(4000)  
 *   → transicion_out(120) → continuar al UI principal.
 *
 * Adaptado para hardware AMOLED usando amoled.setBrightness() 
 * en lugar de analogWrite().
 */

#include "ui_splash.h"
#include "ui.h"
#include "config.h"
#include <LilyGo_AMOLED.h>
#include <Arduino.h>

// ============================================================================
// Referencia al objeto AMOLED global (definido en main.cpp)
// ============================================================================
extern LilyGo_Class amoled;
extern uint8_t user_brightness;

// ============================================================================
// Imagen del logo exportada desde SquareLine Studio (ui_img_yex_240h_png.c)
// ============================================================================
extern const lv_img_dsc_t ui_img_yex_240h_png;

// ============================================================================
// Transiciones de brillo (adaptadas del proyecto legacy)
// ============================================================================

/**
 * @brief Fade-in lento para el logo (~1.4 segundos).
 * Equivalente a transicion_logo() del .ino original.
 */
static void splash_fade_in_logo(uint8_t target) {
    for (int i = 1; i <= target; i += 10) {
        amoled.setBrightness(i);
        delay(110); // 110ms por paso = cinematográfico
    }
}

/**
 * @brief Fade-in normal (~200ms).
 * Equivalente a transicion_in() del .ino original.
 */
static void splash_fade_in(uint8_t target) {
    for (int i = 30; i <= target; i += 10) {
        amoled.setBrightness(i);
        delay(20);
    }
    delay(50);
}

/**
 * @brief Fade-out (~200ms). Limpia pantalla al final.
 * Equivalente a transicion_out() del .ino original.
 */
static void splash_fade_out(uint8_t from) {
    for (int i = from; i >= 1; i -= 10) {
        amoled.setBrightness(i);
        delay(15);
    }
    amoled.setBrightness(0);
    delay(50);
}

// ============================================================================
// Secuencia principal de Splash
// ============================================================================
void ui_splash_run(void) {
    // --- PASO 0: Asegurar pantalla apagada ---
    amoled.setBrightness(0);

    // --- PASO 1: Crear pantalla de splash con color de fondo configurable ---
    lv_obj_t *splash_scr = lv_obj_create(NULL);
    lv_obj_clear_flag(splash_scr, LV_OBJ_FLAG_SCROLLABLE);

#if UI_SPLASH_BG_WHITE
    lv_obj_set_style_bg_color(splash_scr, lv_color_white(), LV_PART_MAIN);
#else
    lv_obj_set_style_bg_color(splash_scr, lv_color_black(), LV_PART_MAIN);
#endif
    lv_obj_set_style_bg_opa(splash_scr, LV_OPA_COVER, LV_PART_MAIN);

    // --- PASO 2: Agregar imagen del logo centrada ---
    lv_obj_t *logo_img = lv_img_create(splash_scr);
    lv_img_set_src(logo_img, &ui_img_yex_240h_png);
    lv_obj_set_width(logo_img, LV_SIZE_CONTENT);
    lv_obj_set_height(logo_img, LV_SIZE_CONTENT);
    lv_obj_set_align(logo_img, LV_ALIGN_CENTER);
    lv_obj_add_flag(logo_img, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(logo_img, LV_OBJ_FLAG_SCROLLABLE);

    // Cargar la pantalla de splash
    lv_disp_load_scr(splash_scr);
    lv_task_handler(); // Forzar renderizado

    // --- PASO 3: Logo visible con brillo fijo (sin animación de fade) ---
    // NOTA: Animación de fade comentada a petición del cliente (efecto "logo doble").
    //       Se conserva el código para uso futuro.
    // delay(500);
    // splash_fade_in_logo(120);  // Fade-in lento (~1.4s)
    // delay(UI_SPLASH_TIME_LOGO_MS); // Logo visible
    // splash_fade_out(120);      // Fade-out
    amoled.setBrightness(SPLASH_BRIGHTNESS);
    delay(UI_SPLASH_TIME_LOGO_MS);
    amoled.setBrightness(0);
    delay(50);

    // --- PASO 4: Pantalla de modelo "IMOX-XX" ---
    // Limpiar pantalla para texto del modelo
    lv_obj_clean(splash_scr);

    // Fondo negro para el texto del modelo (como en el original)
    lv_obj_set_style_bg_color(splash_scr, lv_color_black(), LV_PART_MAIN);

    // Crear labels para "IMOX-" (bold) y el sufijo (light)
    // Usamos LV_FONT_MONTSERRAT_40 como aproximación a Oswald_Medium45pt7b
    lv_obj_t *model_label = lv_label_create(splash_scr);
    lv_label_set_text(model_label, DEVICE_MODEL);
    lv_obj_set_style_text_color(model_label, lv_color_white(), LV_PART_MAIN);
    lv_obj_set_style_text_font(model_label, &ui_font_Qualy96, LV_PART_MAIN);
    lv_obj_set_align(model_label, LV_ALIGN_CENTER);

    lv_task_handler(); // Forzar renderizado

    // Fade-in del modelo
    // NOTA: Animación de fade comentada para consistencia con paso 3.
    // splash_fade_in(120);
    // delay(UI_SPLASH_TIME_MODEL_MS); // Modelo visible
    // splash_fade_out(120);     // Fade-out
    amoled.setBrightness(SPLASH_BRIGHTNESS);
    delay(UI_SPLASH_TIME_MODEL_MS);
    amoled.setBrightness(0);
    delay(50);

    // --- PASO 5: Limpieza ---
    // CRÍTICO: No podemos borrar la pantalla activa (splash_scr) porque LVGL hará crash.
    // Creamos una pantalla temporal vacía, la cargamos y así podemos borrar el splash de forma segura.
    lv_obj_t *temp_scr = lv_obj_create(NULL);
    lv_disp_load_scr(temp_scr);
    lv_obj_del(splash_scr);

    // Restaurar brillo del usuario para la UI principal
    amoled.setBrightness(user_brightness);

    Serial.println("Splash: Secuencia completada");
}
