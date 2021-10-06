#include <color.h>

uint32_t mapColor(uint8_t v, uint8_t s, uint8_t e, uint32_t cs, uint32_t ce) {
  uint8_t r1 = (cs & 0xff0000) >> 16;
  uint8_t g1 = (cs & 0x00ff00) >> 8;
  uint8_t b1 = (cs & 0x0000ff);
  uint8_t r2 = (ce & 0xff0000) >> 16;
  uint8_t g2 = (ce & 0x00ff00) >> 8;
  uint8_t b2 = (ce & 0x0000ff);
  uint32_t r = map(v, s, e, r1, r2);
  uint16_t g = map(v, s, e, g1, g2);
  uint8_t b = map(v, s, e, b1, b2);
  return r << 16 | g << 8 | b;
}
