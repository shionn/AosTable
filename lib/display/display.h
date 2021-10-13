#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include <Arduino.h>
#include <data.h>

#include <ssd1309.h>

#define BOX_W 24
#define BOX_H 14

#define MODE_MAIN 0
#define MODE_SCORE 1
#define MODE_SELECT_MAP 2
#define MODE_SELECT_COLOR 3
#define MODE_SELECT_BG 4
#define MODE_SELECT_STRIP_ANIM 5

#define MODE_JOUEUR_A_H 6
#define MODE_JOUEUR_A_S 7
#define MODE_JOUEUR_A_V 8
#define MODE_JOUEUR_B_H 9
#define MODE_JOUEUR_B_S 10
#define MODE_JOUEUR_B_V 11

#define MODE_GROUND_H 12
#define MODE_GROUND_S 13
#define MODE_GROUND_V 14
#define MODE_BORDER_H 15
#define MODE_BORDER_S 16
#define MODE_BORDER_V 17

#define MODE_SELECT_GROUND_ANIM 18
#define MODE_SELECT_BORDER_ANIM 19

class Display {
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
  void drawMode();
  String getAnimName(uint8_t anim);
};

#endif