#ifndef LCD_SERVICE_H
#define LCD_SERVICE_H

#include <avr/pgmspace.h>
#include "icy_config.h"

void lcd_set_P(const char *line1, const char *line2);
void lcd_set(const char *line1, const char *line2);
void lcd_set_bars(const char *line1, int bars);
void lcd_init();
void lcd_clear();

#endif
