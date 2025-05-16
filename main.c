#include <stdint.h>
#include <SDL2/SDL.h>
#include "lvgl/lvgl.h"
#include "pos1.c"
#include "pos2.c"
#include "pos3.c"
#include "pos4.c"
#include "pos5.c"
#include "pos6.c"
#include "pos7.c"
#include "pos8.c"

#define GR_NAVY 0x195297
#define GR_PINK 0xEF0DA1
#define GR_PRPL 0x7920FF
#define GR_GRAY 0x9AA3B0

// --- Global or static variables needed in the timer callback ---
lv_obj_t * speed;
static uint16_t speedData = 1; // Initial speed data
static char speedBuffer[32];   // Buffer for the speed string

// --- Timer Callback Function ---
static void speed_update_timer_cb(lv_timer_t * timer) {
    speedData++;
    if (speedData > 100) {
        speedData = 1;
    }

    // Format the string
    snprintf(speedBuffer, sizeof(speedBuffer), "Speed: %d mph", speedData);
    if (speed) {
        lv_label_set_text(speed, speedBuffer);
        // Add this line for diagnostics:
        lv_obj_invalidate(lv_screen_active()); // Invalidate the whole screen
    }
}

int main() {

    /**
     * @brief Notes about LVGL
     * 
     * main_place - how to distribute items of a flex container on its main axis (ex: how to vertically organize items for a flex column)
     * track_place - how to distribute items of a flex container on its cross (perpendicular) axis
     * cross_place - how to distribute items in its self-contained perpendicular axis (if they have different heights/widths for example)
     */

    // Images

    LV_IMAGE_DECLARE(pos1);
    LV_IMAGE_DECLARE(pos2);
    LV_IMAGE_DECLARE(pos3);

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
        lv_style_set_flex_flow(&screenStyle, LV_FLEX_FLOW_ROW);
        lv_style_set_flex_main_place(&screenStyle, LV_FLEX_ALIGN_CENTER);
        lv_style_set_flex_cross_place(&screenStyle, LV_FLEX_ALIGN_CENTER);
        lv_style_set_flex_track_place(&screenStyle, LV_FLEX_ALIGN_CENTER);

    static lv_style_t flexColStyle;
        lv_style_init(&flexColStyle);
        lv_style_set_layout(&flexColStyle, LV_LAYOUT_FLEX);
        lv_style_set_flex_flow(&flexColStyle, LV_FLEX_FLOW_COLUMN);
        lv_style_set_flex_main_place(&flexColStyle, LV_FLEX_ALIGN_CENTER);
        lv_style_set_flex_cross_place(&flexColStyle, LV_FLEX_ALIGN_CENTER);
        lv_style_set_flex_track_place(&flexColStyle, LV_FLEX_ALIGN_CENTER);
        lv_style_set_pad_top(&flexColStyle, 50);
        lv_style_set_pad_bottom(&flexColStyle, 50);
        lv_style_set_pad_left(&flexColStyle, 50);
        lv_style_set_pad_right(&flexColStyle, 50);


    // --- SCREEN SETUP ---
    lv_obj_t * screen = lv_screen_active();
    lv_obj_add_style(screen, &screenStyle, 0);
    lv_obj_set_style_bg_color(screen, lv_color_hex(GR_NAVY), LV_PART_MAIN);

    lv_obj_set_style_border_width(screen, 2, LV_PART_MAIN);
    lv_obj_set_style_border_color(screen, lv_color_hex(0xFF0000), LV_PART_MAIN);  // Red border
    lv_obj_set_style_border_side(screen, LV_BORDER_SIDE_FULL, LV_PART_MAIN);


    lv_obj_t * flexCol = lv_obj_create(screen);
    lv_obj_add_style(flexCol, &flexColStyle, 0);
    lv_obj_set_style_bg_color(flexCol, lv_color_hex(0xffffff), LV_PART_MAIN);

    lv_obj_t * label1 = lv_label_create(flexCol);
    lv_label_set_text(label1, "Gaucho");
    lv_obj_set_style_border_width(label1, 1, LV_PART_MAIN);
    lv_obj_set_style_border_color(label1, lv_color_hex(0x00FF00), LV_PART_MAIN);  // Red border
    lv_obj_set_style_border_side(label1, LV_BORDER_SIDE_FULL, LV_PART_MAIN);

    // lv_obj_t * label2 = lv_label_create(flexCol);
    // lv_label_set_text(label2, "Racing");
    // lv_obj_set_style_border_width(label2, 1, LV_PART_MAIN);
    // lv_obj_set_style_border_color(label2, lv_color_hex(0x0000FF), LV_PART_MAIN);  // Red border
    // lv_obj_set_style_border_side(label2, LV_BORDER_SIDE_FULL, LV_PART_MAIN);




    
                    
    // --- LVGL Main Loop --- 
    uint32_t idle_time;

    lv_timer_create(speed_update_timer_cb, 1000, NULL);

    while(1) {
        lv_task_handler();
        lv_delay_ms(5);
    }
}
