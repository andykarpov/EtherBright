#include "lcd_service.h"
#include <Wire.h>
#include <Arduino.h>
#include <LiquidCrystal_SR.h>

LiquidCrystal_SR lcd(LCD_SR_DATA, LCD_SR_CLOCK, LCD_SR_ENABLE); // data, clock, enable = A1, A2, A0

void lcd_init() {
  lcd.begin(8,2);
  uint8_t custom_char[8] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00};
  lcd.createChar(0, custom_char);
}

void lcd_clear() {
  lcd.clear();
}

void lcd_set(const char *line1, const char *line2) {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(line1);
  lcd.setCursor(0,1);
  lcd.print(line2);
}

void lcd_set_bars(const char *line1, int bars) {
  int b = map(bars, 0, 255, 0, 8);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(line1);
  lcd.setCursor(0,1);
  lcd.print(bars);
  /*if (b > 0)
  for (int i=0; i<b; i++) {
    lcd.setCursor(i,1);
    lcd.print(char(0));
  }
  for (int i=b; i<8; i++) {
    lcd.setCursor(i,1);
    lcd.print(" ");
  }*/
}

void lcd_set_P(const char *line1, const char *line2) {
  char* buf_line1 = (char*)(malloc(strlen_P(line1)+1));
  char* buf_line2 = (char*)(malloc(strlen_P(line2)+1));

  strcpy_P(buf_line1, line1);
  strcpy_P(buf_line2, line2);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(buf_line1);
  lcd.setCursor(0,1);
  lcd.print(buf_line2);
  
  free (buf_line1);
  free (buf_line2);
}

