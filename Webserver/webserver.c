/* @project 
 * 
 * License to access, copy or distribute this file.
 * This file or any portions of it, is Copyright (C) 2012, Radu Motisan ,  http://www.pocketmagic.net . All rights reserved.
 * @author Radu Motisan, radu.motisan@gmail.com
 * 
 * This file is protected by copyright law and international treaties. Unauthorized access, reproduction 
 * or distribution of this file or any portions of it may result in severe civil and criminal penalties.
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * 
 * @purpose Eth interface for Atmega microcontrollers
 * http://www.pocketmagic.net/?p=2866
 */

/*
 * CS can be configured in hw_enc28j60.h
 * Configure mymac and myip below
 */

#include <avr/io.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "timeout.h" // defines F_CPU

#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <util/delay.h>
// ethernet interf
#include "net/ip_arp_udp_tcp.h"
#include "net/enc28j60.h"
#include "net/net.h"

// sensors
#include "sensors/Comms.h"
#include "sensors/Sensors.h"
// HD44780 LCD Class
// enc28j60 Ethernet Class
// please modify the following two lines. mac and ip have to be unique
// in your local area network. You can not have the same numbers in
// two devices:
static uint8_t mymac[6] = {0xcd,0x15,0x16,0x17,0x18,0x19};
static uint8_t myip[4] = {192,168,1,150};
// listen port for tcp/www (max range 1-254)
#define MYWWWPORT 80
// working buffer
#define BUFFER_SIZE 500
static uint8_t buf[BUFFER_SIZE+1];
// servers counters
static int nPingCount = 0, nAccessCount = 0;
// Objects
#define duty_cycle OCR2A
void PingCallback(uint8_t *ip) 
{
	nPingCount++;
}

/*
 * Main entry point
 */
int main(void) {
	
	//=====init green led	
	//LEDInit();

	// Init ADC
	adc_init();
	// Init PWM
	pwm_init();
	//=====setup eth interface
	uint16_t dat_p = 0;
	uint8_t adc_value = 0;
	uint8_t temperature = 0;
	uint8_t fan_speed = 0;
	char speed[6];
	//initialize enc28j60
    enc28j60Init(mymac);
	_delay_ms(100);
        
    // Magjack leds configuration, see enc28j60 datasheet, page 11 
    // LEDB=yellow LEDA=green
    // 0x476 is PHLCON LEDA=links status, LEDB=receive/transmit
    // enc28j60PhyWrite(PHLCON,0b0000 0100 0111 01 10);
	enc28j60PhyWrite(PHLCON,0x476);
	_delay_ms(100);

	//init the ethernet/ip layer:
	init_udp_or_www_server(mymac,myip);
	www_server_port(MYWWWPORT);
	register_ping_rec_callback(PingCallback);
	duty_cycle = 255;

	uint16_t x = 0;
	while(1)
	{
	fan_speed = 0;
		// handle ping and wait for a tcp packet:
		dat_p=packetloop_arp_icmp_tcp(buf,enc28j60PacketReceive(BUFFER_SIZE, buf));
		adc_value = lm35dz();
		
		temperature = lm35dz_calibration(adc_value);

		// dat_p will be unequal to zero if there is a valid http get
		for(x = 0; x <= adc_value; x=x+3)
		{
			fan_speed = fan_speed+1;
		}
		if(dat_p==0)
		{
		    // do nothing
		    continue;
		}
	    // tcp port 80 begin
	    if (strncmp("GET ",(char *)&(buf[dat_p]),4)!=0)
		{
		    dat_p=fill_tcp_data_p(buf,0,PSTR("HTTP/1.0 200 OK\r\nContent-Type: text/html\r\nPragma: no-cache\r\n\r\n"));
		    dat_p=fill_tcp_data_p(buf,dat_p,PSTR("<h1>200 OK</h1>"));
	    }
	    
		if (strncmp("/index.htm",(char *)&(buf[dat_p+4]),10)==0)
		{
			for (x = 0; x <= 255; x++)
			{
				*speed = "test";
				sprintf(speed, "/D%03d",x);
				if (strncmp((char *)&(buf[dat_p+14]),speed,5)==0)
				{
					fan_speed = x;
					duty_cycle = fan_speed;
				}
			}
			
			if (strncmp("/NORM",(char *)&(buf[dat_p+14]),5)==0)
			{
				duty_cycle = adc_value+100;
			}

			nAccessCount++;
			dat_p=fill_tcp_data_p(buf,0,PSTR("HTTP/1.0 200 OK\r\nContent-Type: text/html\r\nPragma: no-cache\r\n\r\n"));
			// webcontent
			char szWebText[140] = {0};									
			sprintf(szWebText, "<b>ATmega1284 Webserver / ENC28J60</b><br><br>Fan & Temperature stats:<br>Temperature:%d°C Fan Speed:%d<br>ADC Value:%d<br>By Nick Herniman",temperature, fan_speed,adc_value);
			dat_p=fill_tcp_data(buf,dat_p,szWebText);
		}
		else
		{
			// all other URLs:
			dat_p=fill_tcp_data_p(buf,0,PSTR("HTTP/1.0 401 Unauthorized\r\nContent-Type: text/html\r\n\r\n<h1>401 Unauthorized</h1>"));
		}
	    www_server_reply(buf,dat_p); // send web page data			
	}    
	return (0);
} 