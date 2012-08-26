#ifndef ICY_CONFIG_H
#define ICY_CONFIG_H

#include <Arduino.h>
#include <EtherBright.h>

#define LOCAL_LAN

static struct uip_eth_addr 
            mac      =     {{0x00, 0xbd, 0x3b, 0x33, 0x05, 0x71}};
#ifndef LOCAL_LAN
static byte my_ip[4] =     {192,168,10,22};
static byte my_gw[4] =     {192,168,10,1};
static byte my_nm[4] =     {255,255,255,0};
#else
static byte my_ip[4] =     {192,168,13,22};
static byte my_gw[4] =     {192,168,13,1};
static byte my_nm[4] =     {255,255,255,0};
#endif

#define LCD_SR_DATA        A1
#define LCD_SR_CLOCK       A2
#define LCD_SR_ENABLE      A0

#define ENCODER_PIN_A      11 
#define ENCODER_PIN_B      10
#define ENCODER_BTN        28
#define ENCODER_LED_GREEN  27
#define ENCODER_LED_RED    29

#define VS1003_CS_PIN      0
#define VS1003_DCS_PIN     3
#define VS1003_DREQ_PIN    2
#define VS1003_RESET_PIN   1

#endif
