#include <stdint.h>
#include <SDL2/SDL.h>
#include "lvgl/lvgl.h"

int main() {
    lv_init();

    lv_sdl_window_create(800, 480);

    // styles
    static lv_style_t screenStyle;
    lv_style_init(&screenStyle);

    static lv_style_t flexRowStyle;
    lv_style_init(&flexRowStyle);
    lv_style_set_width(&flexRowStyle, 500);
    lv_style_set_flex_flow(&flexRowStyle, LV_FLEX_FLOW_ROW);
    lv_style_set_layout(&flexRowStyle, LV_LAYOUT_FLEX);
    lv_style_set_flex_grow(&flexRowStyle, 1); // Specifically in context of columnn

    // setup code here
    lv_obj_set_style_bg_color(lv_screen_active(), lv_color_hex(0x39FF14), LV_PART_MAIN);
    lv_obj_set_layout(lv_screen_active(), LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(lv_screen_active(), LV_FLEX_FLOW_COLUMN);
    lv_obj_set_style_text_color(lv_screen_active(), lv_color_hex(0x000000), LV_PART_MAIN);

    lv_obj_t * flexRow1 = lv_obj_create(lv_screen_active());
    lv_obj_add_style(flexRow1, &flexRowStyle, 0);
    lv_obj_set_flex_align(flexRow1, LV_FLEX_ALIGN_SPACE_AROUND, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_SPACE_AROUND);

    lv_obj_t * flexRow2 = lv_obj_create(lv_screen_active());
    lv_obj_add_style(flexRow2, &flexRowStyle, 0);
    lv_obj_set_flex_align(flexRow2, LV_FLEX_ALIGN_SPACE_AROUND, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_SPACE_AROUND);

    lv_obj_t * label1 = lv_label_create(flexRow1);
    lv_label_set_text(label1, "Row 1 Test");
    lv_obj_set_flex_grow(label1, 1);
    lv_obj_t * speed = lv_label_create(flexRow1);
    lv_label_set_text(speed, "Speed aaaaaaaaaaaaaaaa ");
    lv_obj_set_flex_grow(speed, 1);
    

    lv_obj_t * label2 = lv_label_create(flexRow2);
    lv_label_set_text(label2, "Row 2 Test");
    lv_obj_set_flex_grow(label2, 1);

    uint32_t idle_time;
    while(1) {
        // looped code here
        idle_time = lv_timer_handler();
        SDL_Delay(idle_time);
    }
}
