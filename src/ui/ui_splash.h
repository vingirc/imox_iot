/**
 * @file ui_splash.h
 * @brief Pantalla de inicio (Splash Screen) con logo y modelo del dispositivo.
 * 
 * Replica la secuencia de arranque del proyecto legacy:
 * 1. Pantalla en negro → Fade-in lento del logo
 * 2. Logo visible ~4 segundos  
 * 3. Fade-out → Pantalla con nombre del modelo ("IMOX-XX")
 * 4. Fade-in del modelo → Visible ~4 segundos
 * 5. Fade-out → Carga la UI principal
 */

#ifndef UI_SPLASH_H
#define UI_SPLASH_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

/**
 * @brief Ejecuta la secuencia completa de splash (bloqueante).
 * 
 * Esta función debe llamarse DESPUÉS de beginLvglHelper() y ANTES de ui_init().
 * Controla el brillo del AMOLED directamente para las transiciones de fade.
 */
void ui_splash_run(void);

#ifdef __cplusplus
}
#endif

#endif // UI_SPLASH_H
