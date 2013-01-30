/*
 * GPIO.c
 *
 * Created: 29/01/2013 20:45:14
 *  Author: ION
 */ 

#define F_CPU 20000000    // AVR clock frequency in Hz, used by util/delay.h
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRC |= (1 << 0);
    while(1)
    {
        			PORTC ^= (1 << 0);    // toggles the led

        			_delay_ms(300);

    }
}