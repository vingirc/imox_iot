#include "lvgl/lvgl.h"
#include "lv_drivers/sdl/sdl.h"
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>

#include "ui/ui.h"

int main(void)
{
    lv_init();
    sdl_init();

    static lv_disp_draw_buf_t disp_buf;
    static lv_color_t buf[SDL_HOR_RES * SDL_VER_RES / 10];
    lv_disp_draw_buf_init(&disp_buf, buf, NULL, SDL_HOR_RES * SDL_VER_RES / 10);

    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.draw_buf = &disp_buf;
    
    /* Regresamos al driver nativo de la PC */
    disp_drv.flush_cb = sdl_display_flush; 
    
    disp_drv.hor_res = SDL_HOR_RES;
    disp_drv.ver_res = SDL_VER_RES;
    lv_disp_drv_register(&disp_drv);

    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = sdl_mouse_read;
    lv_indev_drv_register(&indev_drv);

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