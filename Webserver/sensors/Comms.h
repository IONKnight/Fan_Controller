/*
 * Comms.h
 *
 * Created: 23/02/2013 14:41:07
 *  Author: ION
 */ 


#ifndef COMMS_H_
#define COMMS_H_
extern void LedInit (void);
extern void LedToggle (void);
extern void LedOn (void);
extern void LedOff (void);
extern void pwm_init(void);
extern void adc_init(void);
extern uint16_t adc_read(uint8_t pin);

#endif /* COMMS_H_ */