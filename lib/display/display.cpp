
#include <display.h>

Display::Display(Data* data) { this->data = data; }

void Display::init() {
  pinMode(7, INPUT_PULLUP);
  lcd.init();
}

void Display::drawBorder() {
  lcd.hline(0, 127, 0);
  lcd.hline(0, 127, 63);
  lcd.vline(0, 0, 63);
  lcd.vline(127, 0, 63);
}

void Display::drawGrid() {
  for (uint8_t x = 1; x <= 3; x++) {
    lcd.vline(x * 32 - 1, 0, 63);
    lcd.vline(x * 32, 0, 63);
    lcd.hline(0, 127, x * 16 - 1);
    lcd.hline(0, 127, x * 16);
  }
}

String Display::getAnimName(uint8_t anim) {
  switch (anim) {
  default:
  case STRIP_MODE_PULSE:
    return F("Pulse");
  case STRIP_MODE_CHENILL:
    return F("Chenille");
  case STRIP_MODE_RAIN:
    return F("Pluie");
  }
}

void Display::drawMode() {
  switch (mode) {

  case MODE_SELECT_MAP:
    drawGrid();
    for (uint8_t y = 0; y < 4; y++) {
      uint8_t t = pgm_read_byte(&(DATA_SCENARIO[data->scenario * 4 + y]));
      for (uint8_t x = 0; x < 4; x++) {
        if (((t >> (x * 2)) & 0b00000011) == 0b000000001) {
          lcd.print(x * 32 + 14, y * 16 + 3, F("A"));
        }
        if (((t >> (x * 2)) & 0b00000011) == 0b000000010) {
          lcd.print(x * 32 + 14, y * 16 + 3, F("B"));
        }
      }
    }
    break;
  case MODE_SELECT_STRIP_ANIM:
    lcd.print(0, 8 * cursor + 2, F(">"));
  case MODE_SELECT_GROUND_ANIM:
  case MODE_SELECT_BORDER_ANIM:
    lcd.print(6, 2, F("Sol"));
    lcd.print(50, 2, getAnimName(data->groundMode()));
    lcd.print(6, 10, F("Bordure"));
    lcd.print(50, 10, getAnimName(data->borderMode()));
    lcd.print(6, 18, F("Retour"));
    break;

  case MODE_SELECT_BG:
    lcd.print(0, 8 * cursor + 2, F(">"));
  case MODE_GROUND_H:
  case MODE_GROUND_S:
  case MODE_GROUND_V:
  case MODE_BORDER_H:
  case MODE_BORDER_S:
  case MODE_BORDER_V:
    lcd.print(6, 2, F("Teinte Sol"));
    lcd.print(6, 10, F("Satur. Sol"));
    lcd.print(6, 18, F("Brill. Sol"));
    lcd.print(108, 2, String(data->ground.h >> 10));
    lcd.print(108, 10, String(data->ground.s));
    lcd.print(108, 18, String(data->ground.v));
    lcd.print(6, 26, F("Teinte Bordure"));
    lcd.print(6, 34, F("Satur. Bordure"));
    lcd.print(6, 42, F("Brill. Bordure"));
    lcd.print(108, 26, String(data->border.h >> 10));
    lcd.print(108, 34, String(data->border.s));
    lcd.print(108, 42, String(data->border.v));
    lcd.print(6, 50, F("Retour"));
    break;
  case MODE_SELECT_COLOR:
    lcd.print(0, 8 * cursor + 2, F(">"));
  case MODE_JOUEUR_A_H:
  case MODE_JOUEUR_A_S:
  case MODE_JOUEUR_A_V:
  case MODE_JOUEUR_B_H:
  case MODE_JOUEUR_B_S:
  case MODE_JOUEUR_B_V:
    lcd.print(6, 2, F("Teinte Joueur A"));
    lcd.print(6, 10, F("Satur. Joueur A"));
    lcd.print(6, 18, F("Brill. Joueur A"));
    lcd.print(108, 2, String(data->playerA.h >> 10));
    lcd.print(108, 10, String(data->playerA.s));
    lcd.print(108, 18, String(data->playerA.v));
    lcd.print(6, 26, F("Teinte Joueur B"));
    lcd.print(6, 34, F("Satur. Joueur B"));
    lcd.print(6, 42, F("Brill. Joueur B"));
    lcd.print(108, 26, String(data->playerB.h >> 10));
    lcd.print(108, 34, String(data->playerB.s));
    lcd.print(108, 42, String(data->playerB.v));
    lcd.print(6, 50, F("Retour"));
    break;

  case MODE_MAIN:
  default:
    lcd.print(0, 8 * cursor + 2, F(">"));
    lcd.print(6, 2, F("Suivi Scores"));
    lcd.print(6, 10, F("Choix Scenario"));
    lcd.print(6, 18, F("Couleur Joueurs"));
    lcd.print(6, 26, F("Couleur Ambiance"));
    lcd.print(6, 34, F("Animation"));
  }
}

uint8_t speed = 0;

void Display::print() {
  lcd.startRankDisplay();
  while (lcd.haveRankToDisplay()) {
    lcd.clearBuffer();
    lcd.print(90, 50, String(speed));
    drawBorder();
    drawMode();
    lcd.display();
  }
  speed++;
}

void Display::update() {
  bool press = !digitalRead(7);
  while (!digitalRead(7))
    delay(50);
  analog = (analog * 4 + analogRead(A0)) / 5;

  switch (mode) {

  case MODE_SELECT_MAP:
    data->scenario = map(analog, 0, 1023, 0, 20);
    if (press) {
      mode = MODE_MAIN;
    }
    break;

  case MODE_SELECT_STRIP_ANIM:
    cursor = map(analog, 0, 1023, 0, 3);
    if (press) {
      if (cursor == 2)
        mode = MODE_MAIN;
      else
        mode = MODE_SELECT_GROUND_ANIM + cursor;
    }
    break;

  case MODE_SELECT_GROUND_ANIM:
    data->groundMode(map(analog, 0, 1023, 0, 3));
    if (press)
      mode = MODE_SELECT_STRIP_ANIM;
    break;
  case MODE_SELECT_BORDER_ANIM:
    data->borderMode(map(analog, 0, 1023, 0, 3));
    if (press)
      mode = MODE_SELECT_STRIP_ANIM;
    break;

  case MODE_SELECT_BG:
    cursor = map(analog, 0, 1023, 0, 7);
    if (press) {
      if (cursor == 6)
        mode = MODE_MAIN;
      else
        mode = MODE_GROUND_H + cursor;
    }
    break;
  case MODE_GROUND_H:
    data->ground.h = analog << 6;
    if (press)
      mode = MODE_SELECT_BG;
    break;
  case MODE_GROUND_S:
    data->ground.s = analog >> 2;
    if (press)
      mode = MODE_SELECT_BG;
    break;
  case MODE_GROUND_V:
    data->ground.v = analog >> 2;
    if (press)
      mode = MODE_SELECT_BG;
    break;
  case MODE_BORDER_H:
    data->ground.h = analog << 6;
    if (press)
      mode = MODE_SELECT_BG;
    break;
  case MODE_BORDER_S:
    data->ground.s = analog >> 2;
    if (press)
      mode = MODE_SELECT_BG;
    break;
  case MODE_BORDER_V:
    data->ground.v = analog >> 2;
    if (press)
      mode = MODE_SELECT_BG;
    break;

  case MODE_SELECT_COLOR:
    cursor = map(analog, 0, 1023, 0, 7);
    if (press) {
      if (cursor == 6)
        mode = MODE_MAIN;
      else
        mode = MODE_JOUEUR_A_H + cursor;
    }
    break;
  case MODE_JOUEUR_A_H:
    data->playerA.h = analog << 6;
    if (press)
      mode = MODE_SELECT_COLOR;
    break;
  case MODE_JOUEUR_A_S:
    data->playerA.s = analog >> 2;
    if (press)
      mode = MODE_SELECT_COLOR;
    break;
  case MODE_JOUEUR_A_V:
    data->playerA.v = analog >> 2;
    if (press)
      mode = MODE_SELECT_COLOR;
    break;
  case MODE_JOUEUR_B_H:
    data->playerB.h = analog << 6;
    if (press)
      mode = MODE_SELECT_COLOR;
    break;
  case MODE_JOUEUR_B_S:
    data->playerB.s = analog >> 2;
    if (press)
      mode = MODE_SELECT_COLOR;
    break;
  case MODE_JOUEUR_B_V:
    data->playerB.v = analog >> 2;
    if (press)
      mode = MODE_SELECT_COLOR;
    break;

  case MODE_MAIN:
    cursor = map(analog, 0, 1023, 0, 5);
    if (press) {
      mode = MODE_SCORE + cursor;
    }
    break;

  default:
    mode = MODE_MAIN;
    break;
  }
}