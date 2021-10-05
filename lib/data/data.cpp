#include <data.h>

HSV::HSV(uint16_t h, uint8_t s, uint8_t v) {
  this->h = h;
  this->s = s;
  this->v = v;
};

uint32_t HSV::hsv(Adafruit_NeoPixel *strip) { return strip->ColorHSV(h, s, v); }

uint8_t Data::scenario() { return mode & 0b00001111; }
uint8_t Data::groundMode() { return mode & 0b00110000 >> 4; }
uint8_t Data::borderMode() { return mode & 0b11000000 >> 6; }
void Data::scenario(uint8_t scenario) { mode = (mode & 0b11110000) | scenario; }
void Data::groundMode(uint8_t ground) {
  mode = (mode & 0b11001111) | ground << 4;
}
void Data::borderMode(uint8_t border) {
  mode = (mode & 0b00111111) | border << 6;
}
