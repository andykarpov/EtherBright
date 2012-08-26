#include "EtherBright.h"
#include "station_service.h"
#include "lcd_service.h"
#include "lan_service.h"
#include "icy_config.h"
#include <LiquidCrystal_SR.h>
#include <EEPROM.h>
#include <Button.h>
#include <digitalWriteFast.h>
#include <VS1003.h>
#include <QuadEncoder.h>
#include <SPI.h>

extern char* __brkval;
extern char __heap_start;

void setup(void) {
  SPI.begin();
  lcd_init();  
  lan_init();
  webclient_init();
  station_init();
}

void loop(void) {
  lan_loop();  
  station_loop();
}

