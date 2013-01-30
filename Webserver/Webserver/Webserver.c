/*
 * Webserver.c
 *
 * Created: 25/01/2013 17:56:47
 *  Author: ION
 AVR_SWLED_1

 Set output port bit 0 to output
 Loop forever:
 -- if input port bit 7 is '1':
 -- -- set output port to '1'
 -- else
 -- -- set output port to '0'
 */

#include <avr/io.h>
#include <util/delay.h>
#include <spi.h>

//#define INPORT      PIND
#define OUTPORT     PORTC
#define OUTDDR      DDRC


int main( void )
{
	OUTDDR  = 0x01;             // set bit 0 of output port to output

	while (1)
	{
//		if ( INPORT & 0x80)     // read bit 7 of input port
		OUTPORT = 1;        // if input bit is '1', set output bit to '1'
		_delay_us(1000);
		OUTPORT = 0;        // otherwise set output bit to '0'
	}

	return(0);                  // never gets here, but you know that by now
}