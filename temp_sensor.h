/*
 * temp_sensor.h 
 * 
 * API for interfacing with the MSOE dev board temperature sensor
 */

//Include Guards 
#ifndef TEMP_SENSOR_H_
#define TEMP_SENSOR_H_

#define ADC1_BASE (volatile uint32_t*) 0x40012000
#define ADC_SR 0x00
#define ADC_CR2 0x08
#define ADC_SQR3 0x34
#define ADC_DR 0x4C
#define SCAN 8
#define SWSTART 30

/**
 * Initialize the temperature sensor GPIO port.
 */
void temp_init();

/**
 * Displays the current temperature in fahrenheit.
 */
uint16_t temp_current_fahrenheit(uint16_t voltage);

/**
 * Displays the current temperature in celsius.
 */
uint16_t temp_current_celsius(uint16_t voltage);

uint16_t temp_voltage(); 

#endif