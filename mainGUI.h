#pragma once
#include <stdint.h>
#include <SDL2/SDL.h>

#include "lvgl/lvgl.h"

typedef struct {
    lv_obj_t * c;
    lv_chart_series_t * ser;
} Chart;

Chart chart4();
void buildDebug(char * debugMessage);