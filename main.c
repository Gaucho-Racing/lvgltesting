#include <stdint.h>
#include <SDL2/SDL.h>

#include "lvgl/lvgl.h"

const size_t SWIDTH = 800;
const size_t SHEIGHT = 480;

const size_t WIDTH = 600;
const size_t HEIGHT = 360;

const size_t COLUMNS = 16;
const size_t ROWS = 10;

lv_obj_t * background[160];

char debugMessage[64];

static void draw_event_cb(lv_event_t * e)
{
    lv_draw_task_t * draw_task = lv_event_get_draw_task(e);
    lv_draw_dsc_base_t * base_dsc = (lv_draw_dsc_base_t *)lv_draw_task_get_draw_dsc(draw_task);

    if(base_dsc->part != LV_PART_ITEMS) {
        return;
    }

    lv_draw_fill_dsc_t * fill_dsc = lv_draw_task_get_fill_dsc(draw_task);
    if(fill_dsc) {
        lv_obj_t * chart = lv_event_get_target_obj(e);
        int32_t * y_array = lv_chart_get_y_array(chart, lv_chart_get_series_next(chart, NULL));
        int32_t v = y_array[base_dsc->id2];

        uint8_t ratio = (uint8_t)(v * 255 / 100);
        fill_dsc->color = lv_color_mix(lv_palette_main(LV_PALETTE_GREEN), lv_palette_main(LV_PALETTE_RED), ratio);
    }
}

typedef struct {
    lv_obj_t * c;
    lv_chart_series_t * ser;
} Chart;

/**
 * Recolor the bars of a chart based on their value
 */
Chart lv_example_chart_4(void)
{
    /*Create a chart1*/
    lv_obj_t * chart = lv_chart_create(lv_screen_active());
    lv_chart_set_type(chart, LV_CHART_TYPE_BAR);
    lv_chart_set_point_count(chart, 24);
    lv_obj_set_style_pad_column(chart, 2, 0);
    lv_obj_set_size(chart, 260, 160);
    lv_obj_center(chart);

    lv_chart_series_t * ser = lv_chart_add_series(chart, lv_color_hex(0xff0000), LV_CHART_AXIS_PRIMARY_Y);
    lv_obj_add_event_cb(chart, draw_event_cb, LV_EVENT_DRAW_TASK_ADDED, NULL);
    lv_obj_add_flag(chart, LV_OBJ_FLAG_SEND_DRAW_TASK_EVENTS);

    uint32_t i;
    for(i = 0; i < 24; i++) {
        lv_chart_set_next_value(chart, ser, (int32_t)lv_rand(10, 90));
    }

    Chart c = {.c = chart, .ser = ser};

    return c;
}


void singleElement() {
    lv_obj_t * p_bg;

    for (size_t i = 0; i < ROWS * COLUMNS; i++) {
        p_bg = lv_obj_create(lv_screen_active());
        background[i] = p_bg;
        lv_obj_set_size(p_bg, 30, 30);

        lv_obj_set_pos(p_bg, 100 + (i%COLUMNS)*(WIDTH / COLUMNS), 60 + (i / COLUMNS)*(HEIGHT / ROWS));
        lv_obj_set_style_bg_color(p_bg, lv_color_hex(0x00ff00), LV_PART_MAIN);
    }

    lv_obj_set_style_bg_color(background[30], lv_color_hex(0xff0000), LV_PART_MAIN);
}

void oneElement() {
    lv_obj_t * grid = lv_obj_create(lv_screen_active());
    lv_obj_set_size(grid, WIDTH, HEIGHT);
    lv_obj_center(grid);
    lv_obj_set_style_bg_color(grid, lv_color_hex(0x9AA3B0), LV_PART_MAIN);

    lv_obj_t * p_bg;

    const int32_t padding = lv_obj_get_style_pad_top(grid, LV_PART_MAIN);
    printf("%d", padding);
    for (size_t i = 0; i < ROWS * COLUMNS; i++) {
        p_bg = lv_obj_create(grid);
        background[i] = p_bg;
        lv_obj_set_size(p_bg, 30, 30);

        lv_obj_set_pos(p_bg, (i%COLUMNS)*((WIDTH - 2*padding) / COLUMNS), (i / COLUMNS)*((HEIGHT - 2*padding) / ROWS));
        lv_obj_set_style_bg_color(p_bg, lv_color_hex(0x00ff00), LV_PART_MAIN);
    }

    lv_obj_set_style_bg_color(background[30], lv_color_hex(0xff0000), LV_PART_MAIN);
}

void buildDebug() {
    lv_obj_t * panel = lv_obj_create(lv_screen_active());
    lv_obj_set_size(panel, 800, 70);
    lv_obj_center(panel);
    lv_obj_set_style_bg_color(panel, lv_color_hex(0x7920FF), LV_PART_MAIN);

    lv_obj_t * text = lv_label_create(panel);
    lv_label_set_text(text, debugMessage);
    lv_obj_center(text);
}

#define GRID_COLUMNS 10
#define GRID_ROWS 10

#define GRID_WIDTH_PX 600
#define GRID_HEIGHT_PX 360

void x() {
    LV_DRAW_BUF_DEFINE_STATIC(drawBuffer, GRID_WIDTH_PX, GRID_HEIGHT_PX, LV_COLOR_FORMAT_RGB565);
    LV_DRAW_BUF_INIT_STATIC(drawBuffer);

    lv_obj_t * canvas = lv_canvas_create(lv_screen_active());
    lv_canvas_set_draw_buf(canvas, &drawBuffer);

    lv_canvas_fill_bg(canvas, lv_color_hex3(0xccc), LV_OPA_COVER);
    lv_obj_center(canvas);

    lv_layer_t layer;
    lv_canvas_init_layer(canvas, &layer);

    lv_draw_rect_dsc_t rectDesc;
    lv_draw_rect_dsc_init(&rectDesc);
    rectDesc.bg_color = lv_color_hex(0x00ff00);
    rectDesc.border_color = lv_color_hex(0xff0000);
    rectDesc.border_width = 3;
    rectDesc.radius = 5;

    lv_area_t coords = {10, 10, 200, 200};

    lv_draw_rect(&layer, &rectDesc, &coords);

    lv_canvas_finish_layer(canvas, &layer);
}

int main() {
    lv_init();

    lv_display_t* disp = lv_sdl_window_create(SWIDTH, SHEIGHT);
    lv_obj_t* scr = lv_screen_active();
    strcpy(debugMessage, "This is a test! f");

    // setup code here
    lv_obj_set_style_bg_color(lv_screen_active(), lv_color_hex(0x195297), LV_PART_MAIN);

    Chart c = lv_example_chart_4();

    //oneElement();

    // lv_obj_t * label;
    // lv_obj_t * obj;
    // uint8_t i;
    // for(i = 0; i < 9; i++) {
    //     uint8_t col = i % 3;
    //     uint8_t row = i / 3;

    //     label = lv_label_create(grid);
    //     lv_obj_set_size(label, 30, 30);
    //     lv_label_set_text_fmt(label, "%d,%d", col, row);
    //     lv_obj_center(label);

    //     lv_obj_set_grid_cell(label, LV_GRID_ALIGN_STRETCH, col, 1,
    //         LV_GRID_ALIGN_STRETCH, row, 1);
    // }

    uint32_t idle_time;
    int x = 0;
    while(1) {
        // looped code here
        idle_time = lv_timer_handler();
        SDL_Delay(1000);

        lv_obj_set_style_bg_color(lv_screen_active(), lv_color_hex(0x195297), LV_PART_MAIN);

        if (x == 1 && debugMessage[0] != '\0') {
            buildDebug();
        }

        lv_chart_set_next_value(c.c, c.ser, 100 - x);
        x++;
    }
}
