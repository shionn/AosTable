#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include <Arduino.h>
#include <ssd1309.h>
#include <data.h>

#define BOX_W 24
#define BOX_H 14

#define MODE_MAIN 0
#define MODE_SCORE 1
#define MODE_SELECT_MAP 2
#define MODE_SELECT_COLOR 3
#define MODE_SELECT_BG 4

class Display
{
private:
    Ssd1309 lcd = Ssd1309(10, 9, 8);
    Data* data;
    uint8_t mode = MODE_MAIN;
    uint8_t cursor = 0;
    uint16_t analog = 0;
public:
    Display(Data* data);
    void init();
    void print();
    void update();
private:
    void drawBorder();
    void drawGrid();
};

#endif