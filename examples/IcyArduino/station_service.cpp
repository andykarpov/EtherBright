#include "EtherBright.h"
#include "lan_service.h"
#include "lcd_service.h"
#include "station_service.h"

void station_init() {

  // read eeprom config
  /*current_station = EEPROM.read(0);
  current_volume = EEPROM.read(1);

  // validate and constrain values
  current_station = constrain(current_station, 0, station_count-1);
  current_volume = constrain(current_volume, 0, 255);

  // update eeprom config
  EEPROM.write(0, (byte) current_station);
  EEPROM.write(1, (byte) current_volume);
*/
  // led config
  pinMode(ENCODER_LED_GREEN, OUTPUT);
  pinMode(ENCODER_LED_RED, OUTPUT);
  
  // set leds to led blink
  current_led_mode = led_mode_none;

  player.begin();
  player.setVolume(current_volume);  
  
  connect(current_station, 1);
}

void station_loop() {
  
  uint32_t cur_time = millis();
  
  // read encoder
  // set leds / mode
  if (btn_mode.isPressed() && cur_time - btn_mode_last_pressed > 1000) {
    prev_mode = current_mode;
    current_mode = (current_mode == station_mode_station) ? station_mode_volume : station_mode_station;
    btn_mode_last_pressed = cur_time;
  }
  
  if (prev_mode != current_mode) {
    switch (current_mode) {
      
      case station_mode_station:
        station_display(current_station);
        enc_value = current_station;
        prev_enc_value = current_station;
      break;
      
      case station_mode_volume:
        lcd_set_bars("Volume: ", current_volume); 
        enc_value = current_volume;
        prev_enc_value = current_volume;
      break;

    }
    prev_mode = current_mode;
  }
  
  char enc_reading = enc.readEncoder();
  if ((enc_reading == '<' || enc_reading == '>')) {        
    switch(current_mode) {
      case station_mode_station:
        if (cur_time - encoder_last_reading >= 100) {
          (enc_reading == '<') ? enc_value++ : enc_value--;
          if (enc_value >= station_count-1) enc_value = station_count-1;
          if (enc_value <= 0) enc_value = 0;
          if (enc_value != prev_enc_value) {
            disconnect();
            current_station = enc_value;
            station_display(current_station);
            prev_enc_value = enc_value;
          }
          encoder_last_reading = cur_time;
        }
      break;
      case station_mode_volume:
        if (cur_time - encoder_last_reading >= 10) {
          (enc_reading == '<') ? enc_value++ : enc_value--;
          if (enc_value >= 255) enc_value = 255;
          if (enc_value <= 0) enc_value = 0;
          if (enc_value != prev_enc_value) {
            //disconnect();
            current_volume = enc_value;
            lcd_set_bars("Volume: ", current_volume);
            prev_enc_value = enc_value;
          }
          encoder_last_reading = cur_time;
        }
      break;
    }    
  }
  
  if (cur_time - encoder_last_reading >= 700) {
    if (current_station != prev_station) {
      prev_station = current_station;
      connect(current_station , 1);
    }
    
    if (current_volume != prev_volume) {
      prev_volume = current_volume;
      set_volume(current_volume);
    }
  }
    
    if (cur_time - led_mode_last_changed >= 50) {
      led_blink_state = !led_blink_state;
      led_mode_last_changed = cur_time;
    }

  led(current_led_mode);    
}

void set_volume(uint8_t volume) {
  player.setVolume(current_volume);
  //EEPROM.write(1, (byte) current_volume);
}

void station_play(uint8_t idx) {
  //EEPROM.write(0, (byte) idx);
  switch(idx) {
    case 0: webclient_get_P(PSTR("195.91.237.50"), 8000, PSTR("/detskoe128"));        break;
    case 1: webclient_get_P(PSTR("95.170.181.50"),  8075, PSTR("/"));                 break;
    case 2: webclient_get_P(PSTR("95.170.181.50"),  8085, PSTR("/"));                 break;
    case 3: webclient_get_P(PSTR("46.174.49.15"),  8001, PSTR("/agakids"));           break;
    case 4: webclient_get_P(PSTR("208.76.152.74"), 8000, PSTR("/"));                   break;
    case 5: webclient_get_P(PSTR("77.88.252.125"), 8000, PSTR("/retro"));              break;
    case 6: webclient_get_P(PSTR("173.244.214.174"), 8056, PSTR("/"));                  break;
    case 7: webclient_get_P(PSTR("77.88.252.125"), 8000, PSTR("/jamfm"));              break;
    case 8: webclient_get_P(PSTR("77.88.252.125"), 8000, PSTR("/europaplus"));         break;
    case 9: webclient_get_P(PSTR("77.88.252.125"), 8000, PSTR("/106fm"));              break;    
    case 10: webclient_get_P(PSTR("77.88.252.125"), 8000, PSTR("/nashe"));              break;
    case 11: webclient_get_P(PSTR("77.88.252.125"), 8000, PSTR("/radioalla"));          break;
    case 12: webclient_get_P(PSTR("77.88.252.125"), 8000, PSTR("/avtoradio"));          break;
    case 13: webclient_get_P(PSTR("208.92.52.60"), 80, PSTR("/RUVR_RUS_SC"));           break;
    case 14: webclient_get_P(PSTR("194.50.90.139"), 80, PSTR("/"));                     break;
  }
}

void station_display(uint8_t idx) {
  switch(idx) {
    case 0:  lcd_set_P(PSTR("Detskoe"), PSTR("Radio"));       break;
    case 1:  lcd_set_P(PSTR("Skazki"), PSTR(""));       break;
    case 2:  lcd_set_P(PSTR("Kids"), PSTR("Hits"));       break;
    case 3:  lcd_set_P(PSTR("AGA"), PSTR("Kids"));       break;
    case 4:  lcd_set_P(PSTR("C89.5"), PSTR("Radio"));       break;
    case 5:  lcd_set_P(PSTR("Retro"), PSTR("FM"));          break;
    case 6:  lcd_set_P(PSTR("Radio"), PSTR("Paradize"));    break;
    case 7:  lcd_set_P(PSTR("JAM"), PSTR("FM"));            break;
    case 8:  lcd_set_P(PSTR("Europa"), PSTR("Plus"));       break;
    case 9:  lcd_set_P(PSTR("106 FM"), PSTR("Dynamo"));     break;
    case 10:  lcd_set_P(PSTR("Nashe"), PSTR("Radio"));       break;
    case 11:  lcd_set_P(PSTR("Radio"), PSTR("Alla"));        break;
    case 12:  lcd_set_P(PSTR("Avto"), PSTR("Radio"));        break;
    case 13:  lcd_set_P(PSTR("Voice of"), PSTR("Russia"));   break;
    case 14: lcd_set_P(PSTR("BBC"), PSTR("Radio"));         break;
  }
}

void led(led_mode_e mode) {
  
  current_led_mode = mode;
  
  switch (mode) {
    case led_mode_none:
      digitalWrite(ENCODER_LED_GREEN, LOW);
      digitalWrite(ENCODER_LED_RED,   LOW);
    break;
    case led_mode_green:
      digitalWrite(ENCODER_LED_GREEN, HIGH);
      digitalWrite(ENCODER_LED_RED,   LOW);
    break;
    case led_mode_red:
      digitalWrite(ENCODER_LED_GREEN, LOW);
      digitalWrite(ENCODER_LED_RED,   HIGH);
    break;
    case led_mode_orange:
      digitalWrite(ENCODER_LED_GREEN, HIGH);
      digitalWrite(ENCODER_LED_RED,   HIGH);
    break;
    case led_mode_green_blink:
      digitalWrite(ENCODER_LED_GREEN, (led_blink_state) ? HIGH : LOW);
      digitalWrite(ENCODER_LED_RED  , LOW);
    break;
    case led_mode_red_blink:
      digitalWrite(ENCODER_LED_RED  , (led_blink_state) ? HIGH : LOW);
      digitalWrite(ENCODER_LED_GREEN, LOW);
    break;
    case led_mode_orange_blink:
      digitalWrite(ENCODER_LED_RED  , (led_blink_state) ? HIGH : LOW);
      digitalWrite(ENCODER_LED_GREEN, (led_blink_state) ? HIGH : LOW);
    break;
    case led_mode_green_orange_blink:
      digitalWrite(ENCODER_LED_RED  , (led_blink_state) ? HIGH : LOW);
      digitalWrite(ENCODER_LED_GREEN, HIGH);    
    break;
    case led_mode_red_orange_blink:
      digitalWrite(ENCODER_LED_GREEN, (led_blink_state) ? HIGH : LOW);
      digitalWrite(ENCODER_LED_RED  , HIGH);
    break;
  }
}

