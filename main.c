#include <stdint.h>
#include <SDL2/SDL.h>

#include "lvgl/lvgl.h"

int main() {
    lv_init();

    lv_sdl_window_create(800, 480);

    // setup code here

    uint32_t idle_time;
    while(1) {
        // looped code here
        idle_time = lv_timer_handler();
        SDL_Delay(idle_time);
    }
}
