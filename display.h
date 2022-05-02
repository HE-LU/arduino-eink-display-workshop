// Display source: https://github.com/ZinggJM/GxEPD2

#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include <GxEPD2_3C.h>
#include <GxEPD2_BW.h>
#include <Fonts/FreeSerif9pt7b.h> // fonts: https://github.com/adafruit/Adafruit-GFX-Library/tree/master/Fonts
#include <Fonts/FreeSerif12pt7b.h>

#include "logs.h"
#include "data.h"

#define GxEPD2_DISPLAY_CLASS GxEPD2_3C // three color display
#define GxEPD2_DRIVER_CLASS GxEPD2_290c // GDEW029Z10 128x296, UC8151 (IL0373)

#define GxEPD2_BW_IS_GxEPD2_BW true
#define GxEPD2_3C_IS_GxEPD2_3C true
#define GxEPD2_7C_IS_GxEPD2_7C true
#define GxEPD2_1248_IS_GxEPD2_1248 true
#define IS_GxEPD(c, x) (c##x)
#define IS_GxEPD2_BW(x) IS_GxEPD(GxEPD2_BW_IS_, x)
#define IS_GxEPD2_3C(x) IS_GxEPD(GxEPD2_3C_IS_, x)
#define IS_GxEPD2_7C(x) IS_GxEPD(GxEPD2_7C_IS_, x)
#define IS_GxEPD2_1248(x) IS_GxEPD(GxEPD2_1248_IS_, x)

#define MAX_DISPLAY_BUFFER_SIZE (81920ul - 34000ul - 5000ul) // ~34000 base use, change 5000 to your application use
#define MAX_HEIGHT(EPD) (EPD::HEIGHT <= (MAX_DISPLAY_BUFFER_SIZE / 2) / (EPD::WIDTH / 8) ? EPD::HEIGHT : (MAX_DISPLAY_BUFFER_SIZE / 2) / (EPD::WIDTH / 8))

// adapt the constructor parameters to your wiring
static GxEPD2_DISPLAY_CLASS<GxEPD2_DRIVER_CLASS, MAX_HEIGHT(GxEPD2_DRIVER_CLASS)> display(GxEPD2_DRIVER_CLASS(/*CS=D8*/ SS, /*DC=D3*/ 0, /*RST=D4*/ 2, /*BUSY=D2*/ 4));

void displayNoWiFiConnection();
void displayData(DataHolder data);
char* alignText(char* text, int length, bool toLeft);

#endif
