/*
 * Webserver.c
 *
 * Created: 25/01/2013 17:56:47
 *  Author: ION
*/
#define F_CPU 20000000    // AVR clock frequency in Hz, used by util/delay.h
#include <avr/io.h>
#include <util/delay.h>
#define pwm_duty_cycle OCR2A
#include <avr/interrupt.h>
/*
// global variable to count the number of overflows
volatile uint8_t tot_overflow;
// program to change brightness of an LED
// demonstration of PWM

// initialize PWM
void pwm_init()
{
	// initialize timer0 in PWM mode
	TCCR0B |= (1<<CS00)|(1<<CS01);
	TCCR0A |= (1<<COM0A0)|(1<<WGM00)|(1<<WGM01);
	// make sure to make OC0 pin (pin PB3 for atmega32) as output pin
	PORTC = 0b00000000;    // toggles the led
	DDRC |= (1 << 1);
//	TCCR2B = 0x81;
//	TCCR2B = (1 << FOC2) | (1 << CS20);
//	TCCR2A = (1 << WGM20) | (1 << WGM21) | (1 << COM;
//	TCCR2B = (1 << CS20)
}

void main()
{
	uint8_t brightness;

	// initialize timer0 in PWM mode
	pwm_init();

	// run forever
	while(1)
	{
		// increasing brightness
		for (brightness = 0; brightness < 255; ++brightness)
		{
			// set the brightness as duty cycle
			pwm_duty_cycle = brightness;
			//PORTC ^= (1 << 1);    // toggles the led
			// delay so as to make the user "see" the change in brightness
			//_delay_ms(10);
			//PORTC ^= (1 << 1);    // toggles the led
			//_delay_ms(10);
			// delay so as to make the user "see" the change in brightness
			_delay_ms(10);
		}

		// decreasing brightness
		for (brightness = 255; brightness > 0; --brightness)
		{
			// set the brightness as duty cycle
			pwm_duty_cycle = brightness;
			//PORTC ^= (1 << 1);    // toggles the led
			// delay so as to make the user "see" the change in brightness
			//_delay_ms(10);
			//PORTC ^= (1 << 1);    // toggles the led
			_delay_ms(10);
		}

		// repeat this forever
	}
}
/*
// initialize timer, interrupt and variable
void timer0_init()
{
	// set up timer with prescaler = 256
	TCCR0B |= (1 << CS02);

	// initialize counter
	TCNT0 = 0;

	// enable overflow interrupt
	TIMSK0 |= (1 << TOIE0);

	// enable global interrupts
	sei();

	// initialize overflow counter variable
	tot_overflow = 0;
}

// TIMER0 overflow interrupt service routine
// called whenever TCNT0 overflows
ISR(TIMER0_OVF_vect)
{
	// keep a track of number of overflows
	tot_overflow++;
}

int main(void)
{
	// connect led to pin PC0
	DDRC |= (1 << 1);

	// initialize timer
	timer0_init();

	// loop forever
	while(1)
	{
		// check if no. of overflows = 12
		if (tot_overflow >= 12)  // NOTE: '>=' is used
		{
			// check if the timer count reaches 53
			if (TCNT0 >= 53)
			{
				PORTC ^= (1 << 1);    // toggles the led
				TCNT0 = 0;            // reset counter
				tot_overflow = 0;     // reset overflow counter
			}
		}
	}
}

int main() 
{
	DDRC |= (1<<0x01);          // set LED pin PD1 to output
	//int x = 0;
	while (1) 
	{
		
		//PORTC |= (1<<PORTC1);   // drive PD1 high
		
		_delay_ms(100);         // delay 100 ms
		//PORTC &= ~(1<<PORTC1);  // drive PD1 low
		_delay_ms(100);         // delay 900 ms
		//x++;
	}
}
*/


