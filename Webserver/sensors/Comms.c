/*
 * Comms.c
 *
 * Created: 23/02/2013 14:42:18
 *  Author: ION
 */ 
 #include <avr/io.h>
 
 extern void LedInit (void)
 {
	 DDRC |= (1 << PORTC0);
 }
 
extern void LedToggle (void)
{
	PORTC ^= (1 << PORTC0);// toggles the led
}	

extern void LedOn (void)
{
	PORTC |= (1<<PORTC0);// turn on the led			
}

extern void LedOff (void)
{
	PORTC &= (0<<PORTC0);// turn off the led
}
extern void pwm_init(void)
{
	// initialize timer0 in PWM mode
	TCCR2B |= (1<<CS20);
	TCCR2A |= (1<<COM2A1)|(1<<WGM20);

	// set pin
	DDRD |= (1<<DDRD7);
}

// initialize adc
extern void adc_init(void)
{
	// AREF = AVcc
	ADMUX = (1<<REFS1); // Vref 1.1V max volt of lm35 based on 10mv/degrees C 100 degree 1v ish

	// ADC Enable and prescaler of 128
	// 20000000/128 = 156250
	ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
}

// read adc value
extern uint16_t adc_read(uint8_t pin)
{
	
ADMUX |= (0<<MUX0)|(0<<MUX1)|(0<<MUX2)|(0<<MUX3)|(0<<MUX4);// clears the bottom 5 bits before ORing
	switch(pin)
	{
		case 0:
		ADMUX |= (0<<MUX0)|(0<<MUX1)|(0<<MUX2); 
		break; 
		case 1:
		ADMUX |= (1<<MUX0)|(0<<MUX1)|(0<<MUX2);
		break;
		case 2:
		ADMUX |= (0<<MUX0)|(1<<MUX1)|(0<<MUX2);
		break;
		case 3:
		ADMUX |= (1<<MUX0)|(1<<MUX1)|(0<<MUX2);
		break;
		case 4:
		ADMUX |= (0<<MUX0)|(0<<MUX1)|(1<<MUX2);
		break;
		case 5:
		ADMUX |= (1<<MUX0)|(0<<MUX1)|(1<<MUX2);
		break;
		case 6:
		ADMUX |= (0<<MUX0)|(1<<MUX1)|(1<<MUX2);
		break;
		case 7:
		ADMUX |= (1<<MUX0)|(1<<MUX1)|(1<<MUX2);
		break;												
	}
	  

	// start single conversion
	// write '1' to ADSC
	ADCSRA |= (1<<ADSC);

	// wait for conversion to complete
	// ADSC becomes '0' again
	// till then, run loop continuously
	while(ADCSRA & (1<<ADSC));

	return (ADC);
	
}