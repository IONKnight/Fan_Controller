/*
 * PWM.c
 *
 * Created: 27/01/2013 20:59:56
 *  Author: ION
 */ 

#define F_CPU 20000000 
// program to change brightness of an LED
// demonstration of PWM
#define duty_cycle OCR2A
#include <avr/io.h>
#include <util/delay.h>


// initialize PWM
void pwm_init()
{
	// initialize timer0 in PWM mode
	TCCR2B |= (1<<CS00);
	TCCR2A |= (1<<COM0A1)|(1<<WGM00)|(1<<WGM01);

	// make sure to make OC2 pin (pin PB3 for atmega32) as output pin
	DDRD |= (1<<0x07);
}

void main()
{
uint8_t brightness;

pwm_init();

//PORTD=0x00;

// for example, this will alternate between 75% and 42% PWM
while(1)
{
			// increasing brightness
			for (brightness = 0; brightness < 255; ++brightness)
			{
				// set the brightness as duty cycle
				duty_cycle = brightness;
				_delay_ms(10);
			}

			// decreasing brightness
			for (brightness = 255; brightness > 0; --brightness)
			{
				// set the brightness as duty cycle
				duty_cycle = brightness;
				_delay_ms(10);
			}

}
}