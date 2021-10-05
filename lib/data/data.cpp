#include <data.h>

HSV::HSV(uint16_t h, uint8_t s, uint8_t v) {
  this->h = h;
  this->s = s;
  this->v = v;
};

uint32_t HSV::hsv(Adafruit_NeoPixel *strip) { return strip->ColorHSV(h, s, v); }
