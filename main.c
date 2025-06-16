#include <stdint.h>
#include <SDL2/SDL.h>
#include "lvgl/lvgl.h"

#define GR_NAVY 0x195297
#define GR_PINK 0xEF0DA1
#define GR_PRPL 0x7920FF
#define GR_GRAY 0x9AA3B0
#define TOP_HEIGHT 200
#define GRID_ROWS 2
#define GRID_COLUMNS 4
#define CELL_WIDTH_PX 20
#define CELL_HEIGHT_PX 20
#define GRID_WIDTH_PX 180
#define GRID_HEIGHT_PX 180

typedef struct {
    lv_obj_t * panel;
    lv_obj_t * text;
} DebugMsg;

static lv_style_t screenStyle;
static lv_style_t flexRowStyle;
static lv_style_t flexColumnStyle;

const size_t SCREEN_WIDTH_PX = 800;
const size_t SCREEN_HEIGHT_PX = 480;

lv_obj_t * speed = NULL;
lv_obj_t * state = NULL;  
lv_obj_t * voltage = NULL;
lv_obj_t * SoC = NULL;
lv_obj_t * power = NULL;   

lv_obj_t * cell = NULL;
lv_obj_t * motor = NULL;
lv_obj_t * inverter = NULL;
lv_obj_t * brake = NULL;

lv_obj_t * current = NULL;
lv_obj_t * torqueMapping = NULL;
lv_obj_t * regen = NULL;

lv_obj_t * wheelDispCanvas = NULL;
DebugMsg debugMsg;

LV_DRAW_BUF_DEFINE_STATIC(wheelDispBuf, GRID_WIDTH_PX, GRID_HEIGHT_PX, LV_COLOR_FORMAT_RGB565);

// extern DashInfo globalStatus;

void styleSetup(void);
void displaySetup(void);
void topSetup(lv_obj_t * parent_obj);
void bottomSetup(lv_obj_t * parent_obj);
void initDebugMsg(lv_obj_t * parent_obj);
// static void ecu_update_timer_cb(lv_timer_t * timer);
void createGrid(lv_obj_t * parent_obj);

void styleSetup(void) {
    lv_style_init(&screenStyle);
    lv_style_set_layout(&screenStyle, LV_LAYOUT_FLEX);
    lv_style_set_flex_flow(&screenStyle, LV_FLEX_FLOW_COLUMN);

    lv_style_init(&flexRowStyle);
    lv_style_set_width(&flexRowStyle, lv_pct(100)); // Make rows take full width
    lv_style_set_height(&flexRowStyle, LV_SIZE_CONTENT); // Row height based on content
    lv_style_set_flex_flow(&flexRowStyle, LV_FLEX_FLOW_ROW);
    lv_style_set_layout(&flexRowStyle, LV_LAYOUT_FLEX);
    lv_style_set_border_width(&flexRowStyle, 0);
    lv_style_set_flex_grow(&flexRowStyle, 1); // Specifically in context of columnn

    lv_style_init(&flexColumnStyle);
    lv_style_set_flex_flow(&flexColumnStyle, LV_FLEX_FLOW_COLUMN);
    lv_style_set_layout(&flexColumnStyle, LV_LAYOUT_FLEX);
    lv_style_set_border_width(&flexColumnStyle, 0);
}

void displaySetup(void) {
    styleSetup();


    LV_IMAGE_DECLARE(dashbg);
    lv_obj_t * bg = lv_image_create(lv_screen_active());
    lv_image_set_src(bg, &dashbg);
    lv_obj_set_width(bg, SCREEN_WIDTH_PX);
    lv_obj_set_height(bg, SCREEN_HEIGHT_PX);
    lv_obj_add_style(bg, &screenStyle, 0);


    topSetup(bg);
    bottomSetup(bg);
    initDebugMsg(bg);
}


void topSetup(lv_obj_t * parent_obj) {
    lv_obj_t * flexRowTop = lv_obj_create(parent_obj);
    lv_obj_add_style(flexRowTop, &flexRowStyle, 0);
    lv_obj_set_flex_align(flexRowTop, LV_FLEX_ALIGN_SPACE_AROUND, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_SPACE_EVENLY);
    lv_obj_set_style_bg_opa(flexRowTop, 0, 0);

        lv_obj_t * boxTop1 = lv_obj_create(flexRowTop);
        lv_obj_set_flex_flow(boxTop1, LV_FLEX_COLUMN);
        lv_obj_set_flex_grow(boxTop1, 2);
        lv_obj_set_style_flex_cross_place(boxTop1, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_style_flex_main_place(boxTop1, LV_FLEX_ALIGN_SPACE_EVENLY, 0);
        lv_obj_set_size(boxTop1, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
        lv_obj_set_height(boxTop1, TOP_HEIGHT);
        lv_obj_set_style_bg_color(boxTop1, lv_color_black(), 0);
        lv_obj_set_style_bg_opa(boxTop1, 100, 0);
        lv_obj_set_style_pad_all(boxTop1, 20, 0);
        lv_obj_set_style_border_width(boxTop1, 0, 0);
        lv_obj_set_style_text_color(boxTop1, lv_color_white(), 0);

            voltage = lv_label_create(boxTop1);
            lv_label_set_text_static(voltage, "100 V");
            SoC = lv_label_create(boxTop1);
            lv_label_set_text_static(SoC, "SoC: 16%");
            power = lv_label_create(boxTop1);
            lv_label_set_text_static(power, "99 kW");

        lv_obj_t * boxTop2 = lv_obj_create(flexRowTop);
        lv_obj_set_flex_flow(boxTop2, LV_FLEX_COLUMN);
        lv_obj_set_flex_grow(boxTop2, 8); // TODO: edit later for real screen
        lv_obj_set_content_height(boxTop2, lv_pct(100));
        lv_obj_set_size(boxTop2, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
        lv_obj_set_height(boxTop2, TOP_HEIGHT);
        lv_obj_set_style_bg_color(boxTop2, lv_color_black(), 0);
        lv_obj_set_style_bg_opa(boxTop2, 100, 0);
        lv_obj_set_style_pad_all(boxTop2, 20, 0);
        lv_obj_set_flex_align(boxTop2, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
        lv_obj_set_style_text_color(boxTop2, lv_color_white(), 0);
        // lv_obj_set_style_flex_cross_place(boxTop2, LV_FLEX_ALIGN_CENTER, 0);
        // lv_obj_set_style_flex_main_place(boxTop2, LV_FLEX_ALIGN_SPACE_EVENLY, 0);

            // flexbox inside of flexbox doesn't seem to work? 
            // lv_obj_t * speedBox = lv_obj_create(boxTop2);
            //     lv_obj_set_flex_flow(speedBox, LV_FLEX_FLOW_ROW);
            //     speed = lv_label_create(speedBox);

            LV_FONT_DECLARE(speedometer_font)
            speed = lv_label_create(boxTop2);
            lv_obj_set_style_text_font(speed, &lv_font_montserrat_44, 0);   // TODO Can we go bigger?
            lv_label_set_text_static(speed, "100");
        
            state = lv_label_create(boxTop2);
            lv_obj_set_style_text_font(state, &lv_font_montserrat_28, 0);
            lv_label_set_text_static(state, "TS PMO");

        lv_obj_t * boxTop3 = lv_obj_create(flexRowTop);
        lv_obj_set_flex_flow(boxTop3, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_flex_grow(boxTop3, 2);
        lv_obj_set_style_flex_main_place(boxTop3, LV_FLEX_ALIGN_SPACE_EVENLY, 0);
        lv_obj_set_style_flex_cross_place(boxTop3, LV_FLEX_ALIGN_CENTER, 0);
        lv_obj_set_size(boxTop3, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
        lv_obj_set_height(boxTop3, TOP_HEIGHT);
        lv_obj_set_style_bg_color(boxTop3, lv_color_hex(GR_GRAY), 0);
        lv_obj_set_style_pad_all(boxTop3, 20, 0); // Add some padding inside the box

                current = lv_label_create(boxTop3);
                lv_obj_set_width(current, 100);
                lv_label_set_text_static(current, "0 A");
                torqueMapping = lv_label_create(boxTop3);
                lv_obj_set_width(torqueMapping, 100);
                lv_label_set_text_static(torqueMapping, "0 TorqueMap");
                regen = lv_label_create(boxTop3);
                lv_obj_set_width(regen, 100);
                lv_label_set_text_static(regen, "0 Regen");
}

void bottomSetup(lv_obj_t * parent_obj) {

    // Code for bottom flex row
    lv_obj_t * flexRowBottom = lv_obj_create(parent_obj);
    lv_obj_add_style(flexRowBottom, &flexRowStyle, 0);
    lv_obj_set_flex_align(flexRowBottom, LV_FLEX_ALIGN_SPACE_AROUND, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_SPACE_AROUND);
    lv_obj_set_style_bg_opa(flexRowBottom, 0, 0);
    //lv_obj_set_style_pad_all(flexRowBottom, 10, 0);

        lv_obj_t * boxBottom1 = lv_obj_create(flexRowBottom);
        lv_obj_set_size(boxBottom1, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
        lv_obj_set_height(boxBottom1, TOP_HEIGHT);
        lv_obj_set_width(boxBottom1, 200);
        lv_obj_set_style_bg_color(boxBottom1, lv_color_hex(GR_GRAY), 0);
        lv_obj_set_style_pad_all(boxBottom1, 20, 0); // Add some padding inside the box

            // lv_obj_update_layout(lv_screen_active());
            createGrid(boxBottom1);

        lv_obj_t * boxBottom2 = lv_obj_create(flexRowBottom);
        lv_obj_set_flex_flow(boxBottom2, LV_FLEX_FLOW_ROW); // --> no longer need flex column since we removed the "temperatures" label
        lv_obj_set_flex_grow(boxBottom2, 4);
        lv_obj_set_size(boxBottom2, LV_PCT(100), LV_SIZE_CONTENT);
        lv_obj_set_height(boxBottom2, TOP_HEIGHT);
        lv_obj_set_style_bg_color(boxBottom2, lv_color_hex(GR_GRAY), 0);
        lv_obj_set_flex_align(boxBottom2, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
        lv_obj_set_style_flex_cross_place(boxBottom2, LV_FLEX_ALIGN_START, 0);
        lv_obj_set_style_pad_all(boxBottom2, 20, 0); // Add some padding inside the box

                    // lv_obj_t * cellTempBox = lv_obj_create(boxBottom2);
                    // lv_obj_set_height(cellTempBox, 200);
                    // lv_obj_set_flex_flow(cellTempBox, LV_FLEX_FLOW_COLUMN);
                    // lv_obj_set_flex_align(cellTempBox, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
                    // lv_obj_set_scrollbar_mode(cellTempBox, LV_SCROLLBAR_MODE_OFF);    // gets rid of scrollbars when content within a flexbox extends past box borders
                    // lv_obj_set_size(cellTempBox, LV_SIZE_CONTENT, LV_SIZE_CONTENT);

                        cell = lv_label_create(boxBottom2);
                        lv_label_set_text_static(cell, "Cell:\n30 C");

                        motor = lv_label_create(boxBottom2);
                        lv_label_set_text_static(motor, "Motor:\n30 C");

                        inverter = lv_label_create(boxBottom2);
                        lv_label_set_text_static(inverter, "Inverter:\n30 C");

                        brake = lv_label_create(boxBottom2);
                        lv_label_set_text_static(brake, "Brakes:\n30 C\n30 C\n30 C\n30 C");

}

void initDebugMsg(lv_obj_t * parent_obj)
{
    debugMsg.panel = lv_obj_create(parent_obj);
    lv_obj_set_size(debugMsg.panel, 800, 70);
    lv_obj_center(debugMsg.panel);
    lv_obj_set_style_bg_color(debugMsg.panel, lv_color_hex(0x7920FF), LV_PART_MAIN);
    lv_obj_add_flag(debugMsg.panel, LV_OBJ_FLAG_HIDDEN);

    debugMsg.text = lv_label_create(debugMsg.panel);
    lv_obj_center(debugMsg.text);
    lv_label_set_text(debugMsg.text, "Allegedly");
    lv_obj_set_style_text_font(debugMsg.text, &lv_font_montserrat_44, 0);
}

void createGrid(lv_obj_t * parent) {
    LV_DRAW_BUF_INIT_STATIC(wheelDispBuf);

    wheelDispCanvas = lv_canvas_create(parent);
    lv_obj_set_size(wheelDispCanvas, GRID_WIDTH_PX, GRID_HEIGHT_PX);
    lv_canvas_set_draw_buf(wheelDispCanvas, &wheelDispBuf);

    lv_canvas_fill_bg(wheelDispCanvas, lv_color_hex(GR_GRAY), LV_OPA_COVER);
    lv_obj_center(wheelDispCanvas);
}
void updateWheelDisp() {
    lv_layer_t layer;
    lv_canvas_init_layer(wheelDispCanvas, &layer);

    lv_draw_arc_dsc_t dsc;
    lv_draw_arc_dsc_init(&dsc);
    dsc.width = 15;
    dsc.radius = 15;
    dsc.start_angle = 0;
    dsc.end_angle = 359;

    dsc.color = lv_color_hex(GR_PRPL); // TEMP TL
    dsc.center.x = 25;
    dsc.center.y = 25;
    lv_draw_arc(&layer, &dsc);
    dsc.center.x = 60;
    dsc.color = lv_color_hex(GR_PRPL); // VOLT TL
    lv_draw_arc(&layer, &dsc);

    dsc.color = lv_color_hex(GR_PRPL); // TEMP TR
    dsc.center.x = 180-60;
    dsc.center.y = 25;
    lv_draw_arc(&layer, &dsc);
    dsc.center.x = 180-25;
    dsc.color = lv_color_hex(GR_PRPL); // VOLT TR
    lv_draw_arc(&layer, &dsc);

    dsc.color = lv_color_hex(GR_PRPL); // TEMP BL
    dsc.center.x = 25;
    dsc.center.y = 180-25;
    lv_draw_arc(&layer, &dsc);
    dsc.center.x = 60;
    dsc.color = lv_color_hex(GR_PRPL); // VOLT BL
    lv_draw_arc(&layer, &dsc);

    dsc.color = lv_color_hex(GR_PRPL); // TEMP BR
    dsc.center.x = 180-60;
    dsc.center.y = 180-25;
    lv_draw_arc(&layer, &dsc);
    dsc.center.x = 180-25;
    dsc.color = lv_color_hex(GR_PRPL); // VOLT BR
    lv_draw_arc(&layer, &dsc);

    lv_canvas_finish_layer(wheelDispCanvas, &layer);
}

int main() {
    lv_init();

    lv_sdl_window_create(800, 480);

    displaySetup();



    updateWheelDisp();
    // setup code here

    uint32_t idle_time;
    while(1) {
        // looped code here
        idle_time = lv_timer_handler();
        SDL_Delay(idle_time);

        lv_obj_invalidate(lv_screen_active());
    }
}
