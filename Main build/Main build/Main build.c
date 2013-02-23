/*
 * Main_build.c
 *
 * Created: 23/02/2013 14:30:33
 *  Author: ION
 */ 

#define F_CPU 20000000
#include <avr/io.h>
#include <util/delay.h>
#include "Comms.h"
#define duty_cycle OCR2A
int main(void)
{
	uint8_t brightness;

	pwm_init();
    while(1)
    {
		// increasing brightness
		for (brightness = 0; brightness < 255; ++brightness)
		{
			// set the brightness as duty cycle
			duty_cycle = brightness;
			ToggleLed();
			_delay_ms(10);
		}

		// decreasing brightness
		for (brightness = 255; brightness > 0; --brightness)
		{
			// set the brightness as duty cycle
			duty_cycle = brightness;
			ToggleLed();
			_delay_ms(10);
		}

    }
}