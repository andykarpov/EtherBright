#ifndef STATION_SERVICE_H
#define STATION_SERVICE_H

#include <digitalWriteFast.h>
#include <VS1003.h>
#include <EEPROM.h>
#include <Button.h>
#include <QuadEncoder.h>
#include "icy_config.h"

static VS1003 player(VS1003_CS_PIN, VS1003_DCS_PIN, VS1003_DREQ_PIN, VS1003_RESET_PIN);
static QuadEncoder enc(ENCODER_PIN_A, ENCODER_PIN_B);
static Button btn_mode(ENCODER_BTN, PULLUP);

static uint32_t btn_mode_last_pressed = 0;
static uint32_t led_mode_last_changed = 0;
static uint32_t encoder_last_reading = 0;
static boolean led_blink_state = false;

enum station_mode_e {
  station_mode_none = 0,
  station_mode_station,
  station_mode_volume
};

enum led_mode_e {
  led_mode_none = 0,
  led_mode_green = 1,
  led_mode_red = 2,
  led_mode_orange = 3,
  led_mode_green_blink = 4,
  led_mode_red_blink = 5,
  led_mode_orange_blink = 6,
  led_mode_green_orange_blink = 7,
  led_mode_red_orange_blink = 8
};

static uint8_t station_count = 15;

static uint8_t current_station = 0, prev_station = 0;
static uint8_t current_volume = 255, prev_volume = 255;
static uint8_t current_mode = station_mode_station, prev_mode = station_mode_station;
static led_mode_e current_led_mode = led_mode_none;
static bool connected = false;
static bool connecting = false;
static int enc_value = 0, prev_enc_value = 0;

void station_init();
void station_loop();
void station_display(uint8_t idx);
void station_play(uint8_t idx);
void led(led_mode_e mode);
void set_volume(uint8_t volume);

#endif
