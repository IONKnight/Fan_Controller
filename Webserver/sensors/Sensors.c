/*
 * Sensors.c
 *
 * Created: 15/05/2013 01:42:28
 *  Author: ION
 */ 


#include <avr/io.h>
#include "Comms.h"
#include "Sensors.h"
extern uint16_t lm35dz (void)
{
	
	uint16_t adc_result;
	uint8_t adc;
	adc_result = adc_read(0);//1.1Vref 1V max temp
	adc_result = adc_result >> 2;
	//adc_result = adc_result * Calibration_num; //move adc 10bit number down to 8bit
	//adc_result = adc_result / Calibration_div;
	adc = adc_result;
	return adc;
}

extern uint8_t lm35dz_calibration (uint8_t adc)
{
	adc = (adc * Calibration_num) / Calibration_div;
	return adc;
}