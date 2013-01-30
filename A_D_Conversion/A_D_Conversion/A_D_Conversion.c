/*
 * A_D_Conversion.c
 *
 * Created: 29/01/2013 22:29:26
 *  Author: ION
 */

#define F_CPU 20000000 
#include <avr/io.h>
#include <util/delay.h>
#define two_one_degree 80
//#define two_two_degree 90
#define two_four_degree 90
#define Temperature ADC
#define TEMPERATURE_MAX 25

uint16_t calibrate_temp(uint16_t c_temp)
{
	c_temp = c_temp*TEMPERATURE_MAX/1024;
	return(c_temp);
}


// initialize adc
void adc_init()
{
	// AREF = AVcc
	ADMUX = (1<<REFS0)|(1<<REFS1);

	// ADC Enable and prescaler of 128
	// 20000000/128 = 156250
	ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
}

// read adc value
uint16_t adc_read(uint8_t pin)
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

int main()
{
	uint16_t adc_result0,adc_result;
	unsigned int c_temp;
	DDRC |= (1 << 0);           // to connect led to PC0
	// initialize adc
	adc_init();
	
	


	while(1)
	{
		adc_result0 = adc_read(0);      // read adc value at PA0
		//adc_result= calibrate_temp(adc_result0);
		c_temp = (int)adc_result0*100/1023;
		// condition for led to glow
		if (adc_result0 > two_one_degree)
		{
				PORTC |= (1<<PORTC0);
				_delay_ms(100);
				PORTC |= (0<<PORTC0);
				_delay_ms(100);
		}
		
		if (adc_result0 > two_four_degree)
		{
				PORTC |= (1<<PORTC0);
				//_delay_ms(100);
				//PORTC |= (0<<PORTC0);
				//_delay_ms(100);
				//PORTC |= (1<<PORTC0);
		}
		
		if (adc_result0 < two_one_degree)
		
				PORTC |= (1<<PORTC0);
				_delay_ms(100);
				PORTC |= (0<<PORTC0);
				_delay_ms(100);
				PORTC |= (1<<PORTC0);
				_delay_ms(100);
				PORTC |= (0<<PORTC0);
				_delay_ms(100);

	}
}