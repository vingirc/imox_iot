#include "lvgl/lvgl.h"
#include "lv_drivers/sdl/sdl.h"
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>

#include "ui/ui.h"

/* Interceptor inteligente para corregir los colores en la PC */
void my_flush_cb(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p) {
    int32_t w = (area->x2 - area->x1 + 1);
    int32_t h = (area->y2 - area->y1 + 1);
    uint32_t total = w * h;
    
    /* Deshacemos el SWAP de 16 bits forzado por SquareLine para que se vea bien en Windows */
    for(uint32_t i = 0; i < total; i++) {
        uint16_t c = color_p[i].full;
        color_p[i].full = (c >> 8) | (c << 8);
    }
    
    sdl_display_flush(disp_drv, area, color_p);
}

int main(void)
{
    lv_init();
    sdl_init();

    /* Crear el buffer usando las dimensiones inyectadas por CMake */
    static lv_disp_draw_buf_t disp_buf;
    static lv_color_t buf[SDL_HOR_RES * SDL_VER_RES / 10];
    lv_disp_draw_buf_init(&disp_buf, buf, NULL, SDL_HOR_RES * SDL_VER_RES / 10);

    /* Registrar la pantalla */
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.draw_buf = &disp_buf;
    disp_drv.flush_cb = my_flush_cb; 
    disp_drv.hor_res = SDL_HOR_RES;
    disp_drv.ver_res = SDL_VER_RES;
    lv_disp_drv_register(&disp_drv);

    /* Registrar el raton */
    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = sdl_mouse_read;
    lv_indev_drv_register(&indev_drv);

    /* --- INICIALIZAR IMOX UI --- */
    ui_init();

    while(1) {
        lv_timer_handler();
        usleep(5000);
    }

    return 0;
}

uint32_t custom_tick_get(void)
{
    static uint64_t start_ms = 0;
    if(start_ms == 0) {
        struct timeval tv_start;
        gettimeofday(&tv_start, NULL);
        start_ms = (tv_start.tv_sec * 1000000 + tv_start.tv_usec) / 1000;
    }

    struct timeval tv_now;
    gettimeofday(&tv_now, NULL);
    uint64_t now_ms;
    now_ms = (tv_now.tv_sec * 1000000 + tv_now.tv_usec) / 1000;

    return (uint32_t)(now_ms - start_ms);
}