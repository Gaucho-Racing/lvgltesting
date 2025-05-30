#include <stdint.h>
#include "lvgl/lvgl.h"

#define GRID_COLUMNS 10
#define GRID_ROWS 10

#define GRID_WIDTH_PX 300
#define GRID_HEIGHT_PX 100

// See Brand Guidelines
#define GR_COLOR_PINK 0xEF0DA1
#define GR_COLOR_PURPLE 0x7920FF
#define GR_COLOR_NAVY 0x195297
#define GR_COLOR_GRAY 0x9AA3B0
#define GR_COLOR_WHITE 0xFFFFFF

typedef struct {
    struct {
        lv_obj_t * panel;
        lv_obj_t * text;
    } debugText;

    struct {
        lv_obj_t * graph;
        lv_chart_series_t * ser;
        size_t len;
    } chart;

    lv_obj_t * gridCanvas;
} LvglObjects;

extern volatile LvglObjects lvglObjects;


typedef struct {
    uint8_t cellVoltage;
    uint8_t cellTemperature;
} IncomingACUCellData; // Do not reorder

typedef struct {
    IncomingACUCellData cellData[160];
    char debugMessage[64];              // Treat as a string, if first bit '\0' then no message, clear in steering
    uint8_t ecuPingMap[3];      // Literal copy of ECU Status bits
} IncomingData;

extern volatile IncomingData incomingData;
extern volatile int isDataChanged;