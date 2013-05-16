/*
 * Sensors.h
 *
 * Created: 15/05/2013 01:42:57
 *  Author: ION
 */ 


#ifndef SENSORS_H_
#define SENSORS_H_
#define Calibration_num 53 // was 43 might have made error in report might have been 53
#define Calibration_div 100
extern uint16_t lm35dz (void);
extern uint8_t lm35dz_calibration (uint8_t adc);
#endif /* SENSORS_H_ */