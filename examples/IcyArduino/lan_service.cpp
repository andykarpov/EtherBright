#include "lan_service.h"
#include "station_service.h"

void lan_init() {
  network_prepare_MAC(mac.addr);
  network_init();
  
  while (!enc28j60linkup());  

//  enc28j60Write(ECOCON, 1 & 0x7);
  enc28j60Write(ECOCON, 2 & 0x7);

  uip_ipaddr_t ipaddr;
  uip_init();
  uip_setethaddr(mac);
  uip_ipaddr(ipaddr, my_ip[0],my_ip[1],my_ip[2],my_ip[3]);
  uip_sethostaddr(ipaddr);
  uip_ipaddr(ipaddr, my_gw[0],my_gw[1],my_gw[2],my_gw[3]);
  uip_setdraddr(ipaddr);
  uip_ipaddr(ipaddr, my_nm[0],my_nm[1],my_nm[2],my_nm[3]);
  uip_setnetmask(ipaddr);
  
  timer_set(&periodic_timer, CLOCK_SECOND / 2);
  timer_set(&arp_timer, CLOCK_SECOND * 10);
}

void lan_loop() {
    uip_len = network_read();

  if(uip_len > 0) {
    if(BUF->type == htons(UIP_ETHTYPE_IP)) {
      uip_arp_ipin();
      uip_input();
      if(uip_len > 0) {
	uip_arp_out();
	network_send();
      }
    }
    else if(BUF->type == htons(UIP_ETHTYPE_ARP)) {
      uip_arp_arpin();
      if(uip_len > 0) {
	network_send();
      }
    }
  }
  else if(timer_expired(&periodic_timer)) {
    timer_reset(&periodic_timer);

    for(int i = 0; i < UIP_CONNS; i++) {
      uip_periodic(i);
      if(uip_len > 0) {
	uip_arp_out();
	network_send();
      }
    }

#if UIP_UDP
    for(int i = 0; i < UIP_UDP_CONNS; i++) {
      uip_udp_periodic(i);
      if(uip_len > 0) {
	uip_arp_out();
	network_send();
      }
    }
#endif /* UIP_UDP */

    if(timer_expired(&arp_timer)) {
      timer_reset(&arp_timer);
      uip_arp_timer();      
      //station_play(current_station);
    }
  }
}

void connect(uint8_t idx, uint8_t update_lcd) {
  if (update_lcd) {
    station_display(idx);
  }
  if (connected || connecting) {
    disconnect();
  }
  station_play(idx);
  connecting = true;
  led(led_mode_green);
}

void disconnect() {
    connecting = false;
    connected = false;
    webclient_close();
    webclient_closed();
    uip_close();
    lan_loop();
    lan_loop();
    uip_init();
    lan_loop();
    lan_loop();
    webclient_init();
    led(led_mode_red_blink);
}

void webclient_datahandler(char *data, u16_t len) {
  if (data != NULL) {
    //*(data + len) = '\0';
    player.playChunk(reinterpret_cast<uint8_t*>(data),len);
  }
}

void webclient_connected(void) {
  player.startSong();
  connected = true;
}

void webclient_timedout(void) {
  player.stopSong();
  connected = false;
}

void webclient_aborted(void) {
  player.stopSong();
  connected = false;
}

void webclient_closed(void) {
  player.stopSong();
  connected = false;
}

