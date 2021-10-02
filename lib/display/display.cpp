
#include <display.h>

Display::Display(Data* data) {
    this->data = data;
}

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
    for (uint8_t x = 1;x <= 3;x++) {
        lcd.vline(x * 32 - 1, 0, 63);
        lcd.vline(x * 32, 0, 63);
        lcd.hline(0, 127, x * 16 - 1);
        lcd.hline(0, 127, x * 16);
    }
}

void Display::print() {
    lcd.clearBuffer();
    drawBorder();

    switch (mode) {
    case MODE_SELECT_MAP:
        drawGrid();
        for (uint8_t y = 0;y < 4;y++) {
            uint8_t t = pgm_read_byte(&(DATA_SCENARIO[data->scenario * 4 + y]));
            for (uint8_t x = 0;x < 4;x++) {
                if (((t >> (x * 2)) & 0b00000011) == 0b000000001) {
                    lcd.print(x * 32 + 14, y * 16 + 3, F("A"));
                }
                if (((t >> (x * 2)) & 0b00000011) == 0b000000010) {
                    lcd.print(x * 32 + 14, y * 16 + 3, F("B"));
                }
            }
        }
        break;

    case MODE_MAIN:
    default:
        lcd.print(0, 8 * cursor + 2, F(">"));
        lcd.print(6, 2, F("Suivi Scores"));
        lcd.print(6, 10, F("Choix Scenario"));
        lcd.print(6, 18, F("Choix Couleur"));
        lcd.print(6, 26, F("Choix Ambiance"));
    }

    lcd.display();
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

    case MODE_MAIN:
        cursor = map(analog, 0, 1023, 0, 4);
        if (press) {
            mode = MODE_SCORE + cursor;
        }
        break;
    default:
        mode = MODE_MAIN;
        break;
    }

}