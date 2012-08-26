//Project specific configurations
#ifndef __GLOBAL_CONF_H__
#define __GLOBAL_CONF_H__

//#include <Arduino.h>

//Define frequency
#ifndef F_CPU
#define F_CPU 16000000
#endif

// ENC28J60 SPI port
#define ENC28J60_SPI_PORT		PORTB
#define ENC28J60_SPI_DDR		DDRB

// pre ATMega328p 
#if defined(__AVR_ATmega1284P__)
#define ENC28J60_SPI_SCK		7
#define ENC28J60_SPI_MOSI		5
#define ENC28J60_SPI_MISO		6
#define ENC28J60_SPI_SS			4
#define ENC28J60_CONTROL_CS		4
#else
#define ENC28J60_SPI_SCK		5
#define ENC28J60_SPI_MOSI		3
#define ENC28J60_SPI_MISO		4
#define ENC28J60_SPI_SS			2
#define ENC28J60_CONTROL_CS		2
#endif

// ENC28J60 control port
#define ENC28J60_CONTROL_PORT	PORTB
#define ENC28J60_CONTROL_DDR	DDRB


//Include uip.h gives all the uip configurations in uip-conf.h
#include "uip.h"

#endif /*__GLOBAL_CONF_H__*/
