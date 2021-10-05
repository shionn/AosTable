#include <Adafruit_NeoPixel.h>
#include <Arduino.h>

#include <data.h>
#include <display.h>

Data data = Data();
Display display = Display(&data);

Adafruit_NeoPixel border =
    Adafruit_NeoPixel(BORDER_STRIP_LEN, 2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel ground =
    Adafruit_NeoPixel(GROUND_STRIP_LEN, 3, NEO_GRB + NEO_KHZ800);

uint8_t step = 0; // step d'affichage du ruban de 0 a 255

void setup() {
  display.init();
  border.begin();
  ground.begin();
  Serial.begin(9600);

  for (uint8_t pixel = 0; pixel < max(BORDER_STRIP_LEN, GROUND_STRIP_LEN);
       pixel++) {
    border.fill(border.Color(0, 0, 0));
    ground.fill(ground.Color(0, 0, 0));
    if (pixel < BORDER_STRIP_LEN) {
      border.setPixelColor(pixel, border.Color(255, 255, 255));
    }
    if (pixel < GROUND_STRIP_LEN) {
      ground.setPixelColor(pixel, ground.Color(255, 255, 255));
    }
    border.show();
    ground.show();
    delay(20);
  }

  for (uint8_t loop = 0; loop < 2; loop++) {
    border.fill(border.Color(255, 255, 255));
    ground.fill(ground.Color(255, 255, 255));
    border.show();
    ground.show();
    delay(50);
    border.fill(border.Color(0, 0, 0));
    ground.fill(ground.Color(0, 0, 0));
    border.show();
    ground.show();
    delay(50);
  }
}

PROGMEM const uint8_t STRIP_DATA_A[]{
    10, 13, 14, 15, 16, 32, 33, 34, 35, 36, 37,                         //
    8,  3,  5,  15, 17, 35, 36, 37, 38,                                 //
    8,  5,  11, 14, 20, 31, 32, 33, 34,                                 //
    12, 2,  6,  12, 14, 18, 24, 34, 35, 36, 37, 38, 39,                 //
    12, 4,  6,  10, 15, 19, 21, 30, 31, 31, 33, 34, 35,                 //
    12, 17, 18, 19, 20, 31, 32, 33, 34, 35, 36, 37, 38,                 //
    8,  5,  6,  17, 18, 35, 36, 37, 38,                                 //
    8,  5,  6,  19, 20, 31, 32, 33, 34,                                 //
    12, 5,  6,  7,  8,  25, 26, 35, 36, 37, 38, 39, 40,                 //
    16, 8,  10, 20, 22, 25, 26, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, //
    16, 2,  8,  17, 23, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, //
    16, 3,  5,  15, 17, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 39, 40, //
    16, 5,  11, 14, 20, 25, 26, 27, 28, 29, 30, 35, 36, 37, 38, 39, 40, //
    8,  3,  4,  11, 12, 18, 19, 34, 35,                                 //
    8,  1,  2,  9,  10, 18, 19, 26, 27,                                 //
    8,  2,  3,  10, 11, 14, 15, 22, 23,                                 //
    8,  2,  3,  10, 11, 14, 15, 22, 23,                                 //
    8,  2,  3,  10, 11, 14, 15, 22, 23,                                 //
    12, 1,  2,  9,  10, 17, 20, 25, 28, 29, 30, 39, 40,                 //
    12, 3,  4,  11, 12, 17, 20, 31, 32, 34, 36, 37, 38,                 //
};

PROGMEM const uint8_t STRIP_DATA_B[]{
    10, 21, 22, 23, 24, 25, 26, 27, 28, 29, 40,         //
    8,  8,  10, 20, 22, 27, 28, 29, 30,                 //
    8,  2,  8,  17, 23, 25, 26, 39, 40,                 //
    12, 1,  7,  11, 13, 19, 23, 26, 27, 28, 29, 30, 31, //
    12, 3,  7,  9,  16, 18, 22, 25, 26, 27, 38, 39, 40, //
    12, 17, 18, 19, 20, 25, 26, 27, 28, 29, 30, 39, 40, //
    8,  7,  8,  19, 20, 27, 28, 29, 30,                 //
    8,  7,  8,  17, 18, 25, 26, 39, 40,                 //
    12, 5,  6,  7,  8,  27, 28, 29, 30, 31, 32, 33, 34, //
    8,  8,  10, 20, 22, 27, 28, 29, 30,                 //
    8,  2,  8,  17, 23, 25, 26, 39, 40,                 //
    8,  3,  5,  15, 17, 35, 36, 37, 38,                 //
    8,  5,  11, 14, 20, 31, 32, 33, 34,                 //
    12, 17, 18, 19, 20, 25, 26, 27, 28, 29, 30, 39, 40, //
    12, 17, 18, 19, 20, 31, 32, 33, 34, 35, 36, 37, 38, //
    18, 2,  3,  10, 11, 13, 16, 22, 23, 25, 26, 27, 28,
    29, 30, 31, 38, 39, 40, //
    18, 2,  3,  10, 11, 14, 15, 21, 24, 30, 31, 32, 33,
    34, 35, 36, 37, 38, 39, //
    24, 2,  3,  10, 11, 14, 15, 22, 23, 25, 26, 27, 28,
    29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,     //
    12, 17, 18, 19, 20, 31, 32, 33, 34, 35, 36, 37, 38, //
    12, 17, 18, 19, 20, 25, 26, 27, 28, 29, 30, 39, 40, //
};

uint8_t getSegCode(uint8_t seg) {
  uint8_t iA = 0;
  uint8_t iB = 0;
  for (uint8_t i = 0; i < data.scenario; i++) {
    iA += pgm_read_byte(&(STRIP_DATA_A[iA])) + 1;
    iB += pgm_read_byte(&(STRIP_DATA_B[iB])) + 1;
  }
  uint8_t result = 0;
  for (uint8_t i = 0; i < pgm_read_byte(&(STRIP_DATA_A[iA])); i++) {
    if (pgm_read_byte(&(STRIP_DATA_A[iA + i + 1])) == seg)
      result += 1;
  }
  for (uint8_t i = 0; i < pgm_read_byte(&(STRIP_DATA_B[iB])); i++) {
    if (pgm_read_byte(&(STRIP_DATA_B[iB + i + 1])) == seg)
      result += 2;
  }
  return result;
}

uint8_t getPixelCode(uint8_t pixel) {
  switch (pixel) {
  case GROUND_STRIP_LEN ... GROUND_STRIP_LEN + BORDER_STRIP_LEN:
    return getSegCode(pixel - GROUND_STRIP_LEN + 25);
  default:
    return getSegCode(pixel + 1);
  }
}
uint32_t map(uint8_t s, uint8_t e, uint32_t cs, uint32_t ce) {
  uint8_t r1 = (cs & 0xff0000) >> 16;
  uint8_t g1 = (cs & 0x00ff00) >> 8;
  uint8_t b1 = (cs & 0x0000ff);
  uint8_t r2 = (ce & 0xff0000) >> 16;
  uint8_t g2 = (ce & 0x00ff00) >> 8;
  uint8_t b2 = (ce & 0x0000ff);
  uint32_t r = map(step, s, e, r1, r2);
  uint16_t g = map(step, s, e, g1, g2);
  uint8_t b = map(step, s, e, b1, b2);
  return r << 16 | g << 8 | b;
}

uint32_t pulse(uint32_t c1, uint32_t c2, uint32_t c3, uint32_t c4) {
  switch (step) {
  case 0:
    return c1;
  case 1 ... 63:
    return map(0, 64, c1, c2);
  case 64:
    return c2;
  case 65 ... 127:
    return map(64, 128, c2, c3);
  case 128:
    return c3;
  case 129 ... 195:
    return map(128, 196, c3, c4);
  case 196:
    return c4;
  case 197 ... 255:
    return map(196, 255, c4, c1);
  }
}

uint32_t pulse(uint32_t c1, uint32_t c2) { return pulse(c1, c2, c1, c2); }

uint32_t getPixelColor(uint8_t pixel, Adafruit_NeoPixel *strip) {
  uint8_t code = getPixelCode(pixel);
  switch (code) {
  case 1:
    return pulse(data.playerA.hsv(strip), data.ground.hsv(strip));
  case 2:
    return pulse(data.playerB.hsv(strip), data.ground.hsv(strip));
  case 3:
    return pulse(data.playerA.hsv(strip), data.ground.hsv(strip),
                 data.playerB.hsv(strip), data.ground.hsv(strip));
  default:
    return data.ground.hsv(strip);
  }
}

void updateStrips() {
  for (uint8_t pixel = 0; pixel < GROUND_STRIP_LEN; pixel++) {
    ground.setPixelColor(pixel, getPixelColor(pixel, &ground));
  }
  for (uint8_t pixel = 0; pixel < BORDER_STRIP_LEN; pixel++) {
    border.setPixelColor(pixel,
                         getPixelColor(GROUND_STRIP_LEN + pixel, &border));
  }
  ground.show();
  border.show();
}

void loop() {
  updateStrips();
  display.print();
  display.update();
  step++;
}
