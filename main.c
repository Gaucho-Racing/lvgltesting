#include <stdint.h>
#include <SDL2/SDL.h>
#include "lvgl/lvgl.h"

int main() {
    lv_init();

    lv_sdl_window_create(800, 480);



    // setup code here
    lv_obj_t * label = lv_label_create(lv_screen_active());
    lv_label_set_text(label, "Hello world");
    lv_obj_set_style_text_color(lv_screen_active(), lv_color_hex(0xffffff), LV_PART_MAIN);
    lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
    uint32_t idle_time;
    while(1) {
        // looped code here
        idle_time = lv_timer_handler();
        SDL_Delay(idle_time);
    }
}
