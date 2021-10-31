#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

// #include <MemoryFree.h>
#include <color.h>
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
    18, 2,  3,  10, 11, 13, 16, 22, 23, 25, 26, 27, 28, 29, 30, 31, 38, 39, 40, //
    18, 2,  3,  10, 11, 14, 15, 21, 24, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, //
    24, 2,  3,  10, 11, 14, 15, 22, 23, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,     //
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
  uint8_t result = seg > 24 ? 4 : 0; // 24 : nombre de seg au sol
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

uint8_t getPixelCode(uint16_t pixel) {
  switch (pixel) {
    case 0 ... 7 : return getSegCode(1);
    case 8 : return getSegCode(1) | getSegCode(2) | getSegCode(23) | getSegCode(24);
    case 9 ... 15 : return getSegCode(2);
    case 16 : return getSegCode(2) | getSegCode(3) | getSegCode(17) | getSegCode(18);
    case 17 ... 23 : return getSegCode(3);
    case 24 : return getSegCode(3) | getSegCode(4) | getSegCode(15) | getSegCode(16);
    case 25 ... 32 : return getSegCode(4);
    case 33 ... 40 : return getSegCode(5);
    case 41 : return getSegCode(5) | getSegCode(6) | getSegCode(14) | getSegCode(15);
    case 42 ... 48 : return getSegCode(6);
    case 49 : return getSegCode(6) | getSegCode(7) | getSegCode(18) | getSegCode(19);
    case 50 ... 56 : return getSegCode(7);
    case 57 : return getSegCode(7) | getSegCode(8) | getSegCode(22) | getSegCode(23);
    case 58 ... 65 : return getSegCode(8);
    case 66 ... 73 : return getSegCode(9);
    case 74 : return getSegCode(9) | getSegCode(10) | getSegCode(21) | getSegCode(22);
    case 75 ... 81 : return getSegCode(10);
    case 82 : return getSegCode(10) | getSegCode(11) | getSegCode(19) | getSegCode(20);
    case 83 ... 89 : return getSegCode(11);
    case 90 : return getSegCode(11) | getSegCode(12) | getSegCode(13) | getSegCode(14);
    case 91 ... 98 : return getSegCode(12);
    case 99 ... 109 : return getSegCode(13);
    case 110 ... 120 : return getSegCode(14);
    case 121 ... 131 : return getSegCode(15);
    case 132 ... 142 : return getSegCode(16);
    case 143 ... 153 : return getSegCode(17);
    case 154 ... 164 : return getSegCode(18);
    case 165 ... 175 : return getSegCode(19);
    case 176 ... 186 : return getSegCode(20);
    case 187 ... 197 : return getSegCode(21);
    case 198 ... 208 : return getSegCode(22);
    case 209 ... 219 : return getSegCode(23);
    case 220 ... 230 : return getSegCode(24);
    //
    case 231 ... 241 : return getSegCode(25);
    case 242 : return getSegCode(25) | getSegCode(26);
    case 243 ... 253 : return getSegCode(26);
    case 254 ... 264 : return getSegCode(27);
    case 265 : return getSegCode(27) | getSegCode(28);
    case 266 ... 276 : return getSegCode(28);
    case 277 ... 284 : return getSegCode(29);
    case 285 : return getSegCode(29) | getSegCode(30);
    case 286 ... 293 : return getSegCode(30);
    case 294 ... 301 : return getSegCode(31);
    case 302 : return getSegCode(31) | getSegCode(32);
    case 303 ... 310 : return getSegCode(32);
    case 311 ... 321 : return getSegCode(33);
    case 322 : return getSegCode(33) | getSegCode(34);
    case 323 ... 333 : return getSegCode(34);
    case 334 ... 344 : return getSegCode(35);
    case 345 : return getSegCode(35) | getSegCode(36);
    case 346 ... 356 : return getSegCode(36);
    case 357 ... 364 : return getSegCode(37);
    case 365 : return getSegCode(37) | getSegCode(38);
    case 366 ... 373 : return getSegCode(38);
    case 374 ... 381 : return getSegCode(39);
    case 382 : return getSegCode(39) | getSegCode(40);
    case 383 ... 390 : return getSegCode(40);
  default:
    return getSegCode(0);
  }
}

uint32_t pulse(uint32_t c1, uint32_t c2, uint32_t c3, uint32_t c4) {
  switch (step) {
  case 0:
    return c1;
  case 1 ... 63:
    return mapColor(step, 0, 64, c1, c2);
  case 64:
    return c2;
  case 65 ... 127:
    return mapColor(step, 64, 128, c2, c3);
  case 128:
    return c3;
  case 129 ... 195:
    return mapColor(step, 128, 196, c3, c4);
  case 196:
    return c4;
  case 197 ... 255:
    return mapColor(step, 196, 255, c4, c1);
  }
}

uint32_t pulse(uint32_t c1, uint32_t c2) { return pulse(c1, c2, c1, c2); }

uint32_t pulse(uint16_t pixel, Adafruit_NeoPixel* strip) {
  uint8_t code = getPixelCode(pixel);
  switch (code) {
  default:
  case 0:
    return data.ground.hsv(strip);
  case 1:
    return pulse(data.playerA.hsv(strip), data.ground.hsv(strip));
  case 2:
    return pulse(data.playerB.hsv(strip), data.ground.hsv(strip));
  case 3:
    return pulse(data.playerA.hsv(strip), data.ground.hsv(strip),
      data.playerB.hsv(strip), data.ground.hsv(strip));
  case 4:
    return data.border.hsv(strip);
  case 5:
    return pulse(data.playerA.hsv(strip), data.border.hsv(strip));
  case 6:
    return pulse(data.playerB.hsv(strip), data.border.hsv(strip));
  case 7:
    return pulse(data.playerA.hsv(strip), data.border.hsv(strip),
      data.playerB.hsv(strip), data.border.hsv(strip));
  }
}

uint32_t chenille(uint16_t pixel, uint32_t color, uint32_t background) {
  if (pixel % 32 <= step && pixel % 32 > step  - 8) {
    return mapColor(step - pixel %32, 0, 8, color, background);
  }
  return background;
}

uint32_t chenille(uint16_t pixel, Adafruit_NeoPixel* strip) {
  uint8_t code = getPixelCode(pixel);
  switch (code) {
  default:
  case 0:
    return data.ground.hsv(strip);
  case 1:
    return chenille(pixel, data.playerA.hsv(strip), data.ground.hsv(strip));
  case 2:
    return chenille(pixel, data.playerB.hsv(strip), data.ground.hsv(strip));
  case 3:
    return chenille(pixel, data.bothPlayerHsv(strip), data.ground.hsv(strip));
  case 4:
    return data.border.hsv(strip);
  case 5:
    return chenille(pixel, data.playerA.hsv(strip), data.border.hsv(strip));
  case 6:
    return chenille(pixel, data.playerB.hsv(strip), data.border.hsv(strip));
  case 7:
    return chenille(pixel, data.bothPlayerHsv(strip), data.border.hsv(strip));
  }
}

uint32_t getPixelColor(uint16_t pixel, Adafruit_NeoPixel* strip) {
  uint8_t mode = data.groundMode();
  if (pixel > GROUND_STRIP_LEN)
    mode = data.borderMode();

  switch (mode) {
  default:
  case STRIP_MODE_PULSE:
    return pulse(pixel, strip);
  case STRIP_MODE_CHENILL:
    return chenille(pixel, strip);
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
