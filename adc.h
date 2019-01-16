/*
 * led.h 
 * 
 * API for interfacing with the MSOE dev board Analog-to-Digital Converter
 */

#define ADC1_BASE (volatile uint32_t*) 0x40012000
#define ADC_SR 0x00
#define ADC_CR2 0x08
#define ADC_SQR3 0x34
#define ADC_DR 0x4C

void adc_init();