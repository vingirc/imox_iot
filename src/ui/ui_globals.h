/**
 * @file ui_globals.h
 * @brief Variables globales y configuración centralizada de la UI.
 *
 * Este archivo permite ajustar fácilmente la duración de animaciones,
 * fuentes por tipo de vista, colores compartidos y otros parámetros
 * sin tener que buscar en cada archivo de pantalla individualmente.
 */

#ifndef UI_GLOBALS_H
#define UI_GLOBALS_H

/* Incluido desde ui.h — no incluir ui.h aquí para evitar dependencia circular */

/* ============================================================
 *  ANIMACIONES
 * ============================================================ */

/** Duración en ms de la transición al hacer swipe entre pantallas */
#define UI_ANIM_SWIPE_DURATION      200

/** Delay en ms antes de iniciar la animación de cambio de pantalla */
#define UI_ANIM_SWIPE_DELAY         0

/** Tipo de animación para swipe horizontal (izquierda / derecha) */
#define UI_ANIM_SWIPE_LEFT          LV_SCR_LOAD_ANIM_MOVE_LEFT
#define UI_ANIM_SWIPE_RIGHT         LV_SCR_LOAD_ANIM_MOVE_RIGHT

/** Tipo de animación para swipe vertical (arriba / abajo) */
#define UI_ANIM_SWIPE_UP            LV_SCR_LOAD_ANIM_MOVE_TOP
#define UI_ANIM_SWIPE_DOWN          LV_SCR_LOAD_ANIM_MOVE_BOTTOM

/** Animación de fade usada en la pantalla de diagnóstico */
#define UI_ANIM_FADE                LV_SCR_LOAD_ANIM_FADE_ON

/* ============================================================
 *  FUENTES – agrupadas por tipo de vista
 * ============================================================ */

/*--- Vistas 1 y 2: Voltaje / Corriente (lectura principal) ---*/

/** Parte entera del valor principal (ej. "120") — fuente grande */
#define UI_FONT_HERO_INTEGER        (&ui_font_Qualy150)

/** Parte decimal del valor principal (ej. ".5") y etiqueta de unidad */
#define UI_FONT_HERO_DECIMAL        (&ui_font_Qualy48)

/** Etiqueta de unidad (ej. "V", "A") — mismo tamaño que decimales */
#define UI_FONT_UNIT_LABEL          (&ui_font_Qualy48)

/** Texto por defecto de la pantalla / secundarios */
#define UI_FONT_SCREEN_DEFAULT      (&ui_font_Qualy24)

/*--- Vista 3: Dashboard (4 cuadrantes) ---*/

/** Valor numérico del dashboard (más pequeño que el hero) */
#define UI_FONT_DASH_VALUE          (&ui_font_Qualy82)

/** Etiqueta de unidad en el dashboard */
#define UI_FONT_DASH_UNIT           (&ui_font_Qualy48)

/*--- Vistas 4 y 5: Gráficas (statsWatts / voltageStats) ---*/

/** Título de la gráfica (ej. "Consumo semanal") */
#define UI_FONT_CHART_TITLE         (&ui_font_Qualy24)

/** Valor junto a la gráfica */
#define UI_FONT_CHART_VALUE         (&ui_font_Qualy24)

/** Unidad junto al valor de la gráfica */
#define UI_FONT_CHART_UNIT          (&ui_font_Qualy24)

/*--- Vista 6: Diagnóstico ---*/

/** Título de sección (ej. "RED", "CLOUD", "HARDWARE") */
#define UI_FONT_DIAG_SECTION        (&ui_font_Qualy24)

/** Etiquetas y valores de elementos de diagnóstico */
#define UI_FONT_DIAG_ELEMENT        (&ui_font_Qualy14)

/*--- Vista Modo Diario 24hrs ---*/

/** Título principal y etiquetas de eje */
#define UI_FONT_DAILY_TITLE         (&ui_font_Qualy24)

/** Texto micro (instrucciones, info secundaria) */
#define UI_FONT_DAILY_MICRO         (&ui_font_Qualy14)

/* ============================================================
 *  PALETA DE COLORES – Tonos grises / blancos del cliente
 * ============================================================ */

/** Fondo principal de todas las pantallas */
#define UI_COLOR_BG                 lv_color_hex(0x000000)

/** Texto secundario por defecto (contenedores padres) */
#define UI_COLOR_TEXT_SECONDARY      lv_color_hex(0x606060)

/** Texto informativo (valores secundarios: Hz, W, PF) */
#define UI_COLOR_TEXT_INFO           lv_color_hex(0x808080)

/** Texto de etiquetas (unidades, títulos de sección) */
#define UI_COLOR_TEXT_LABEL          lv_color_hex(0xB0B0B0)

/** Texto activo / blanco puro (encabezados de diagnóstico, navDot activo) */
#define UI_COLOR_TEXT_ACTIVE         lv_color_hex(0xFFFFFF)

/** Color de acento para gráficas y barras de progreso */
#define UI_COLOR_ACCENT             lv_color_hex(0xB388FF)

/** Borde/outline/fondo por defecto (negro, se usa como 'sin borde visual') */
#define UI_COLOR_BORDER             lv_color_hex(0x000000)

/* ============================================================
 *  OPACIDADES (por si se quieren ajustar globalmente)
 * ============================================================ */

#define UI_OPA_FULL                 255
#define UI_OPA_NONE                 0

/* ============================================================
 *  CHART (configuración de gráficas compartida)
 * ============================================================ */

/** Número de puntos en las gráficas de barras */
#define UI_CHART_POINT_COUNT        7

/** Color de fondo de las gráficas */
#define UI_CHART_BG_COLOR           lv_color_hex(0x000000)

/** Color de líneas de cuadrícula */
#define UI_CHART_GRID_COLOR         lv_color_hex(0x0A0A0A)

/** Color de las barras de la serie */
#define UI_CHART_SERIES_COLOR       lv_color_hex(0xB388FF)

#endif /* UI_GLOBALS_H */
