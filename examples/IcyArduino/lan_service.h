#ifndef LAN_SERVICE_H
#define LAN_SERVICE_H

#include "EtherBright.h"
#include "icy_config.h"

extern "C" void network_prepare_MAC(uint8_t*);

static struct timer periodic_timer, arp_timer, play_timer;

#define BUF ((struct uip_eth_hdr *)&uip_buf[0])

void lan_init();
void lan_loop();
void connect(uint8_t idx, uint8_t update_lcd);
void disconnect();

#endif
