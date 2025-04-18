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

int main() {

    /**
     * @brief Notes about LVGL
     * 
     * lv_obj_set_flex_grow - this edits the way children of a flex container stretch along the main axis, NOT how its own children stretch
     * lv_obj_set_flex_flow - this edits the main axis of how its children are placed
     * 
     */

    // Images

    LV_IMAGE_DECLARE(pos1);
    LV_IMAGE_DECLARE(pos2);
    LV_IMAGE_DECLARE(pos3);

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

    static lv_style_t flexColumnStyle;

        lv_style_init(&flexColumnStyle);
        lv_style_set_flex_flow(&flexColumnStyle, LV_FLEX_FLOW_COLUMN);
        lv_style_set_layout(&flexColumnStyle, LV_LAYOUT_FLEX);

    // --- SCREEN SETUP ---
    lv_obj_t * screen = lv_screen_active();
    lv_obj_add_style(screen, &screenStyle, 0);
    lv_obj_set_style_bg_color(screen, lv_color_hex(0x000000), LV_PART_MAIN);

    // Code for top flex row 
    lv_obj_t * flexRowTop = lv_obj_create(screen);
    lv_obj_add_style(flexRowTop, &flexRowStyle, 0);
    lv_obj_set_flex_align(flexRowTop, LV_FLEX_ALIGN_SPACE_AROUND, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_SPACE_EVENLY);

        lv_obj_t * boxTop1 = lv_obj_create(flexRowTop);
        lv_obj_set_flex_flow(boxTop1, LV_FLEX_COLUMN);
        lv_obj_set_flex_grow(boxTop1, 2);
        lv_obj_set_size(boxTop1, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
        lv_obj_set_style_bg_color(boxTop1, lv_color_hex(0xb6d4be), 0);
        lv_obj_set_style_pad_all(boxTop1, 20, 0); 
        lv_obj_t * placeholder1 = lv_label_create(boxTop1);
        lv_label_set_text(placeholder1, "\n\nVoltage: x V\n\nSOC: x %\n\nTotal Power: x W\n\n");

        lv_obj_t * boxTop2 = lv_obj_create(flexRowTop);
        lv_obj_set_flex_flow(boxTop2, LV_FLEX_COLUMN);
        lv_obj_set_flex_grow(boxTop2, 4); // TODO: edit later for real screen
        lv_obj_set_content_height(boxTop2, lv_pct(100));
        lv_obj_set_size(boxTop2, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
        lv_obj_set_style_bg_color(boxTop2, lv_color_hex(0xb6d4be), 0);
        lv_obj_set_style_pad_all(boxTop2, 20, 0); 
        
            lv_obj_t * speed = lv_label_create(boxTop2);
            lv_label_set_text(speed, "\n\nSpeed: x mph\n");
            lv_obj_t * state = lv_label_create(boxTop2);
            lv_label_set_text(state, "\nState: \n\n");

        lv_obj_t * boxTop3 = lv_obj_create(flexRowTop);
        lv_obj_set_flex_flow(boxTop3, LV_FLEX_FLOW_ROW);
        lv_obj_set_flex_grow(boxTop3, 2);
        lv_obj_set_size(boxTop3, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
        lv_obj_set_style_bg_color(boxTop3, lv_color_hex(0xb6d4be), 0);
        lv_obj_set_style_pad_all(boxTop3, 20, 0); // Add some padding inside the box

            lv_obj_t * dialCol = lv_obj_create(boxTop3);
            lv_obj_set_flex_flow(dialCol, LV_FLEX_FLOW_COLUMN);
            lv_obj_set_flex_grow(dialCol, 1);

            lv_obj_t * dialValCol = lv_obj_create(boxTop3);
            lv_obj_set_flex_flow(dialValCol, LV_FLEX_FLOW_COLUMN);
            lv_obj_set_flex_grow(dialValCol, 1);

                lv_obj_t * dial1 = lv_image_create(dialCol);
                lv_image_set_src(dial1, &pos1);
                lv_image_set_scale(dial1, 128);
                lv_obj_t * dial2 = lv_image_create(dialCol);
                lv_image_set_src(dial2, &pos2);
                lv_image_set_scale(dial2, 128);
                lv_obj_t * dial3 = lv_image_create(dialCol);
                lv_image_set_src(dial3, &pos3);
                lv_image_set_scale(dial3, 128);

                lv_obj_t * placeholder3 = lv_label_create(dialValCol);
                lv_label_set_text(placeholder3, "\n\nC: x A\n\nTM: x\n\nRn: x\n\n");

    // Code for bottom flex row 
    lv_obj_t * flexRowBottom = lv_obj_create(screen);
    lv_obj_add_style(flexRowBottom, &flexRowStyle, 0);
    lv_obj_set_flex_align(flexRowBottom, LV_FLEX_ALIGN_SPACE_AROUND, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_SPACE_AROUND);

        lv_obj_t * boxBottom1 = lv_obj_create(flexRowBottom);
        lv_obj_set_flex_flow(boxBottom1, LV_FLEX_FLOW_ROW); // Separates top wheel and bottom wheels
        lv_obj_set_flex_grow(boxBottom1, 2);
        lv_obj_set_size(boxBottom1, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
        lv_obj_set_style_bg_color(boxBottom1, lv_color_hex(0xb6d4be), 0);
        lv_obj_set_style_pad_all(boxBottom1, 20, 0); // Add some padding inside the box

            lv_obj_t * boxBottom1Col1 = lv_obj_create(boxBottom1);
            lv_obj_set_flex_flow(boxBottom1Col1, LV_FLEX_FLOW_COLUMN); 

                lv_obj_t * tireFL = lv_obj_create(boxBottom1Col1);
                lv_obj_set_flex_flow(tireFL, LV_FLEX_FLOW_ROW); 

                    lv_obj_t * tireFLCol = lv_obj_create(tireFL);
                    lv_obj_set_flex_flow(tireFLCol, LV_FLEX_FLOW_COLUMN); 

                        lv_obj_t * tempImageFL = lv_obj_create(tireFLCol);
                        lv_obj_set_size(tempImageFL, 30, 30);
                        lv_obj_set_style_bg_color(tempImageFL, lv_color_hex(0xFF0000), 0);

                        lv_obj_t * powerImageFL = lv_obj_create(tireFLCol);
                        lv_obj_set_size(powerImageFL, 30, 30);
                        lv_obj_set_style_bg_color(powerImageFL, lv_color_hex(0xFF0000), 0);

                    lv_obj_t * tireFLImage = lv_obj_create(tireFL); // Convert to image later
                    lv_obj_set_size(tireFLImage, 30, 30);
                    lv_obj_set_style_bg_color(tireFLImage, lv_color_hex(0x000000), 0);

                lv_obj_t * tireFR = lv_obj_create(boxBottom1Col1);
                lv_obj_set_flex_flow(tireFR, LV_FLEX_FLOW_ROW); 

                    lv_obj_t * tireFRCol = lv_obj_create(tireFR);
                    lv_obj_set_flex_flow(tireFRCol, LV_FLEX_FLOW_COLUMN); 

                        lv_obj_t * tempImageFR = lv_obj_create(tireFRCol);
                        lv_obj_set_size(tempImageFR, 30, 30);
                        lv_obj_set_style_bg_color(tempImageFR, lv_color_hex(0xFF0000), 0);

                        lv_obj_t * powerImageFR = lv_obj_create(tireFRCol);
                        lv_obj_set_size(powerImageFR, 30, 30);
                        lv_obj_set_style_bg_color(powerImageFR, lv_color_hex(0xFF0000), 0);

                    lv_obj_t * tireFRImage = lv_obj_create(tireFR); // Convert to image later
                    lv_obj_set_size(tireFRImage, 30, 30);
                    lv_obj_set_style_bg_color(tireFRImage, lv_color_hex(0x000000), 0);

            lv_obj_t * boxBottom1Col2 = lv_obj_create(boxBottom1);
            lv_obj_set_flex_flow(boxBottom1Col2, LV_FLEX_FLOW_COLUMN); 

                lv_obj_t * tireRL = lv_obj_create(boxBottom1Col2);
                lv_obj_set_flex_flow(tireRL, LV_FLEX_FLOW_ROW);

                    lv_obj_t * tireRLCol = lv_obj_create(tireRL);
                    lv_obj_set_flex_flow(tireRLCol, LV_FLEX_FLOW_COLUMN);

                        lv_obj_t * tempImageRL = lv_obj_create(tireRLCol);
                        lv_obj_set_size(tempImageRL, 30, 30);
                        lv_obj_set_style_bg_color(tempImageRL, lv_color_hex(0xFF0000), 0);

                        lv_obj_t * powerImageRL = lv_obj_create(tireRLCol);
                        lv_obj_set_size(powerImageRL, 30, 30);
                        lv_obj_set_style_bg_color(powerImageRL, lv_color_hex(0xFF0000), 0);

                    lv_obj_t * tireRLImage = lv_obj_create(tireRL); // Convert to image later
                    lv_obj_set_size(tireRLImage, 30, 30);
                    lv_obj_set_style_bg_color(tireRLImage, lv_color_hex(0x000000), 0);


                lv_obj_t * tireRR = lv_obj_create(boxBottom1Col2);
                lv_obj_set_flex_flow(tireRR, LV_FLEX_FLOW_ROW);

                    lv_obj_t * tireRRCol = lv_obj_create(tireRR);
                    lv_obj_set_flex_flow(tireRRCol, LV_FLEX_FLOW_COLUMN); 

                        lv_obj_t * tempImageRR = lv_obj_create(tireRRCol);
                        lv_obj_set_size(tempImageRR, 30, 30);
                        lv_obj_set_style_bg_color(tempImageRR, lv_color_hex(0xFF0000), 0);

                        lv_obj_t * powerImageRR = lv_obj_create(tireRRCol);
                        lv_obj_set_size(powerImageRR, 30, 30);
                        lv_obj_set_style_bg_color(powerImageRR, lv_color_hex(0xFF0000), 0);

                    lv_obj_t * tireRRImage = lv_obj_create(tireRR); // Convert to image later
                    lv_obj_set_size(tireRRImage, 30, 30);
                    lv_obj_set_style_bg_color(tireRRImage, lv_color_hex(0x000000), 0);


        lv_obj_t * boxBottom2 = lv_obj_create(flexRowBottom);
        lv_obj_set_flex_flow(boxBottom2, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_flex_grow(boxBottom2, 3);
        lv_obj_set_size(boxBottom2, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
        lv_obj_set_style_bg_color(boxBottom2, lv_color_hex(0xb6d4be), 0);
        //lv_obj_set_style_pad_all(boxBottom2, 20, 0); // Add some padding inside the box

            // most important temperatures to display will probably be maxCellTemp, motorTemp, inverterTemp, brakeTemp
            
            // honestly we can probably get rid of this label later down the line; driver can tell temp from celsius/fahrenheit
            lv_obj_t * temperature_label = lv_label_create(boxBottom2);
            //lv_obj_set_flex_align(temperature_label, LV_FLEX_ALIGN_CENTER, 0, 0);
            lv_label_set_text(temperature_label, "Temperatures:");

            lv_obj_t * temperatures = lv_obj_create(boxBottom2);
            lv_obj_set_flex_flow(temperatures, LV_FLEX_FLOW_ROW);
            lv_obj_set_size(temperatures, LV_PCT(100), LV_SIZE_CONTENT);
            lv_obj_set_flex_align(temperatures, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

                    lv_obj_t * cellTemp = lv_label_create(temperatures);
                    lv_label_set_text(cellTemp, "Cell: ");

                    lv_obj_t * motorTemp = lv_label_create(temperatures);
                    lv_label_set_text(motorTemp, "Motor: ");

                    lv_obj_t * inverterTemp = lv_label_create(temperatures);
                    lv_label_set_text(inverterTemp, "Inverter: ");
                    
                    lv_obj_t * brakeTemp = lv_label_create(temperatures);
                    lv_label_set_text(brakeTemp, "Brakes: ");
    
    // --- LVGL Main Loop --- 
    uint32_t idle_time;

    while(1) {

        lv_task_handler();
        lv_delay_ms(5);
        // idle_time = lv_timer_handler();
        // SDL_Delay(idle_time);
    }
}
