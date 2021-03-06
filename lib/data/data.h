
#ifndef __DATA_H__
#define __DATA_H__

#include <Adafruit_NeoPixel.h>
#include <Arduino.h>
#include <color.h>

#define BORDER_STRIP_LEN 160
#define GROUND_STRIP_LEN 231

#define STRIP_MODE_PULSE 0
#define STRIP_MODE_CHENILL 1
#define STRIP_MODE_RAIN 2

PROGMEM const uint8_t DATA_SCENARIO[] = {
    0b01010101, 0b00000000, 0b00000000, 0b10101010, //
    0b01010000, 0b01000000, 0b00000010, 0b00001010, //
    0b00000101, 0b00000001, 0b10000000, 0b10100000, //
    0b01010100, 0b01010010, 0b01001010, 0b00101010, //
    0b00010101, 0b10000101, 0b10100001, 0b10101000, //
    0b01010101, 0b01010101, 0b10101010, 0b10101010, //
    0b01010000, 0b01010000, 0b00001010, 0b00001010, //
    0b00000101, 0b00000101, 0b10100000, 0b10100000, //
    0b01011010, 0b01011010, 0b01011010, 0b01011010, //
    0b01010101, 0b01010101, 0b01010110, 0b01011010, //
    0b01010101, 0b01010101, 0b10010101, 0b10100101, //
    0b10100101, 0b10010101, 0b01010101, 0b01010101, //
    0b01011010, 0b01010110, 0b01010101, 0b01010101, //
    0b00010100, 0b00010100, 0b10101010, 0b10101010, //
    0b10101010, 0b10101010, 0b00010100, 0b00010100, //
    0b00000000, 0b10010110, 0b10010110, 0b10101010, //
    0b10101010, 0b10010110, 0b10010110, 0b00000000, //
    0b10101010, 0b10010110, 0b10010110, 0b10101010, //
    0b10101010, 0b10101010, 0b01000001, 0b01000001, //
    0b01000001, 0b01000001, 0b10101010, 0b10101010, //
};

class HSV {
public:
  uint16_t h, s, v;
  HSV(uint16_t h, uint8_t s, uint8_t v);
  uint32_t hsv(Adafruit_NeoPixel* strip);
};

class Data {
private:
  // 0b00110000 : strip ground
  // 0b11000000 : strip border
  uint8_t mode = 0b00000000;

public:
  uint8_t scenario = 3;
  HSV playerA = HSV(0, 255, 32);
  HSV playerB = HSV(170 << 8, 255, 32);
  HSV ground = HSV(0, 255, 0);
  HSV border = HSV(0, 0, 32);

public:
  uint8_t groundMode();
  void groundMode(uint8_t ground);
  uint8_t borderMode();
  void borderMode(uint8_t border);
  uint32_t bothPlayerHsv(Adafruit_NeoPixel* strip);
};

#endif