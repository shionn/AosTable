#include <data.h>

HSV::HSV(uint16_t h, uint8_t s, uint8_t v) {
  this->h = h;
  this->s = s;
  this->v = v;
};

uint32_t HSV::hsv(Adafruit_NeoPixel *strip) { return strip->ColorHSV(h, s, v); }

uint32_t Data::bothPlayerHsv(Adafruit_NeoPixel *strip) {
  return mapColor(1, 0, 2, playerA.hsv(strip), playerB.hsv(strip));
}

uint8_t Data::groundMode() { return (mode & 0b00110000) >> 4; }
uint8_t Data::borderMode() { return (mode & 0b11000000) >> 6; }
void Data::groundMode(uint8_t ground) {
  mode = (mode & 0b11001111) | ground << 4;
}
void Data::borderMode(uint8_t border) {
  mode = (mode & 0b00111111) | (border << 6);
}
