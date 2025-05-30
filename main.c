#include <stdint.h>
#include <SDL2/SDL.h>

#include "lvgl/lvgl.h"
#include "main.h"

volatile IncomingData incomingData = {0};
volatile int isDataChanged = 0;

volatile LvglObjects lvglObjects = {0};

const size_t SCREEN_WIDTH_PX = 800;
const size_t SCREEN_HEIGHT_PX = 480;

LV_DRAW_BUF_DEFINE_STATIC(drawBuffer, GRID_WIDTH_PX, GRID_HEIGHT_PX, LV_COLOR_FORMAT_RGB565);

void initDebugMsg() {
    lvglObjects.debugText.panel = lv_obj_create(lv_screen_active());
    lv_obj_set_size(lvglObjects.debugText.panel, 800, 70);
    lv_obj_center(lvglObjects.debugText.panel);
    lv_obj_set_style_bg_color(lvglObjects.debugText.panel, lv_color_hex(0x7920FF), LV_PART_MAIN);
    lv_obj_add_flag(lvglObjects.debugText.panel, LV_OBJ_FLAG_HIDDEN);

    lvglObjects.debugText.text = lv_label_create(lvglObjects.debugText.panel);
    lv_label_set_text(lvglObjects.debugText.text, "");
    lv_obj_center(lvglObjects.debugText.text);
}

void initCellTemps() {
    LV_DRAW_BUF_INIT_STATIC(drawBuffer);

    lv_obj_t * canvas = lv_canvas_create(lv_screen_active());
    lv_canvas_set_draw_buf(canvas, &drawBuffer);

    lv_canvas_fill_bg(canvas, lv_color_hex(0x0000ff), LV_OPA_COVER);
    lv_obj_center(canvas);

    lvglObjects.gridCanvas = canvas;
}

void initLVGL() {
    lv_obj_set_style_bg_color(lv_screen_active(), lv_color_hex(0x00ff00), LV_PART_MAIN);
    lv_obj_set_style_text_color(lv_screen_active(), lv_color_hex(0xffffff), LV_PART_MAIN);

    initCellTemps();
    initDebugMsg();
}

void refreshScreen(IncomingData data) {
    lv_obj_set_style_bg_color(lv_screen_active(), lv_color_hex(0x00ff00), LV_PART_MAIN);
    if (data.debugMessage[0] != '\0') {
        lv_label_set_text(lvglObjects.debugText.text, data.debugMessage);
        lv_obj_clear_flag(lvglObjects.debugText.panel, LV_OBJ_FLAG_HIDDEN);
    } else {
        lv_obj_add_flag(lvglObjects.debugText.panel, LV_OBJ_FLAG_HIDDEN);
    }

    lv_canvas_fill_bg(lvglObjects.gridCanvas, lv_color_hex(0x0000ff), LV_OPA_COVER);

    lv_layer_t layer;
    lv_canvas_init_layer(lvglObjects.gridCanvas, &layer);

    lv_draw_rect_dsc_t rectDesc;
    lv_draw_rect_dsc_init(&rectDesc);
    rectDesc.bg_color = lv_color_hex(0x00ff00);
    rectDesc.border_color = lv_color_hex(GR_COLOR_PURPLE);
    rectDesc.border_width = 3;
    rectDesc.radius = 5;

    lv_area_t coords = {0, 0, 50, 40};

    lv_draw_rect(&layer, &rectDesc, &coords);
    coords = (lv_area_t){50, 40, 70, 90};
    lv_draw_rect(&layer, &rectDesc, &coords);

    lv_canvas_finish_layer(lvglObjects.gridCanvas, &layer);
}

int main() {
    lv_init();

    lv_display_t* disp = lv_sdl_window_create(SCREEN_WIDTH_PX, SCREEN_HEIGHT_PX);
    lv_obj_t* scr = lv_screen_active();

    initLVGL();

    while (1) {
        lv_tick_inc(1000);
        lv_task_handler();
        refreshScreen(incomingData);
        SDL_Delay(1000);
    }
}