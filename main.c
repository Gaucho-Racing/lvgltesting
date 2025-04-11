#include <stdint.h>
#include <SDL2/SDL.h>
#include "lvgl/lvgl.h"

static void event_cb(lv_event_t * e)
{
    LV_LOG_USER("Clicked");

    static uint32_t cnt = 1;
    lv_obj_t * btn = lv_event_get_target(e);
    lv_obj_t * label = lv_obj_get_child(btn, 0);
    lv_label_set_text_fmt(label, "%"LV_PRIu32, cnt);
    cnt++;
}

/**
 * Add click event to a button
 */
void lv_example_event_1(void)
{
    lv_obj_t * btn = lv_button_create(lv_screen_active());
    lv_obj_set_size(btn, 100, 50);
    lv_obj_center(btn);
    lv_obj_add_event_cb(btn, event_cb, LV_EVENT_CLICKED, NULL);

    lv_obj_t * label = lv_label_create(btn);
    lv_label_set_text(label, "Click me!");
    lv_obj_center(label);
}

int main() {

    static char data[10] = "1000";
    char old_data[10] = "1000";

    const char* new_data = "100000 mph";

    lv_init();

    lv_disp_t * disp = lv_sdl_window_create(800, 480);
    if (disp == NULL) {
        fprintf(stderr, "Failed to create SDL window\n");
        return 1;
    }

    // --- WIDGET STYLES ---
    static lv_style_t screenStyle;
        lv_style_init(&screenStyle);
        lv_style_set_layout(&screenStyle, LV_LAYOUT_FLEX);
        lv_style_set_flex_flow(&screenStyle, LV_FLEX_FLOW_COLUMN);
  
    static lv_style_t flexRowStyle;
    
        lv_style_init(&flexRowStyle);
        lv_style_set_width(&flexRowStyle, lv_pct(100)); // Make rows take full width
        lv_style_set_height(&flexRowStyle, LV_SIZE_CONTENT); // Row height based on content
        lv_style_set_flex_flow(&flexRowStyle, LV_FLEX_FLOW_ROW);
        lv_style_set_layout(&flexRowStyle, LV_LAYOUT_FLEX);
        lv_style_set_border_width(&flexRowStyle, 2);
        lv_style_set_flex_grow(&flexRowStyle, 1); // Specifically in context of columnn

    // --- SCREEN SETUP ---
    lv_obj_t * screen = lv_screen_active();
    lv_obj_add_style(screen, &screenStyle, 0);
    lv_obj_set_style_bg_color(screen, lv_color_hex(0x000000), LV_PART_MAIN);

    // Code for top flex row 
    lv_obj_t * flexRowTop = lv_obj_create(screen);
    lv_obj_add_style(flexRowTop, &flexRowStyle, 0);
    lv_obj_set_flex_align(flexRowTop, LV_FLEX_ALIGN_SPACE_AROUND, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_SPACE_AROUND);

        lv_obj_t * boxTop1 = lv_obj_create(flexRowTop);
        lv_obj_set_size(boxTop1, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
        lv_obj_set_style_bg_color(boxTop1, lv_color_hex(0xb6d4be), 0);
        lv_obj_set_style_pad_all(boxTop1, 20, 0); // Add some padding inside the box
        lv_obj_t * speed = lv_label_create(boxTop1);
        lv_label_set_text(speed, "Speed: x mph");

    // Code for bottom flex row 
    lv_obj_t * flexRowBottom = lv_obj_create(screen);
    lv_obj_add_style(flexRowBottom, &flexRowStyle, 0);
    lv_obj_set_flex_align(flexRowBottom, LV_FLEX_ALIGN_SPACE_AROUND, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_SPACE_AROUND);

        lv_obj_t * boxBottom1 = lv_obj_create(flexRowBottom);
        lv_obj_set_size(boxBottom1, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
        lv_obj_set_style_bg_color(boxBottom1, lv_color_hex(0xb6d4be), 0);
        lv_obj_set_style_pad_all(boxBottom1, 20, 0); // Add some padding inside the box
        lv_obj_t * state = lv_label_create(boxBottom1);
        lv_label_set_text(state, "State: ");

    
    // --- LVGL Main Loop --- 
    uint32_t idle_time;
    int i = 0;

    while(1) {

        if (i == 1000) {
            lv_memcpy(data, new_data, 10);
            lv_label_set_text_static(speed, data);
        } 
        i++;
        // looped code here
        
        lv_task_handler();
        lv_delay_ms(5);
        // idle_time = lv_timer_handler();
        // SDL_Delay(idle_time);
    }
}
