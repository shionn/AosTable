#include <Arduino.h>
#include <ssd1309.h>

// CS ou SS ou CHIP SELECT : RS
#define LCD_CS 10
// DC
#define LCD_RW 9
// Reset, RS
#define LCD_RS 8
Ssd1309 lcd = Ssd1309(LCD_CS, LCD_RW, LCD_RS);

void setup() {
	lcd.init();
}

void loop() {
	lcd.clearBuffer();
	lcd.hline(0, 127, 0);
	lcd.hline(0, 127, 63);
	lcd.vline(0, 0, 63);
	lcd.vline(127, 0, 63);
	lcd.display();
}