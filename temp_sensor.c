/*
 * temp_sensor.c
 *
 *  Created on: Jan 7, 2019
 *      Author: Rock Boynton
 * 
 * Implements functions specified in temp_sensor.h to use the MSOE dev board temperature sensor
 */

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

#include "temp_sensor.h"
#include "delay.h"
#include "gpio.h"

#define ADC1_CR2 (ADC1_BASE + ADC_CR2)
#define ADC1_SQR3 (ADC1_BASE + ADC_SQR3)
#define ADC1_SR (ADC1_BASE + ADC_SR)
#define ADC1_DR (ADC1_BASE + ADC_DR)

static volatile GPIO* GPIOB = 0x40020400;
static volatile ADC* TEMP_SENSOR = 0x40012000;

void temp_init() {
    // Enable GPIOB in RCC_AHB1ENR
	*(RCC_AHB1ENR) |= (1 << GPIOBEN);
    // Enable ADC1EN in RCC_APB2ENR
	*(RCC_APB2ENR) |= (1 << ADC1EN);
    // Configure GPIOB pin 0 to analog mode
    GPIOB->MODER |= 0b11;
    // Turn on ADC1 - continuous conversion
    TEMP_SENSOR->CR2 |= 0b11; 
    // Select channel ADC Channel 8 
    TEMP_SENSOR->SQR3 = ((TEMP_SENSOR->SQR3 & ~0x1F) | 0x08);
    // Set ADC to scan 
    TEMP_SENSOR->CR1 |=(1 << SCAN);
    // Start conversion 
    TEMP_SENSOR->CR2 |= (1 << SWSTART);
}

uint16_t temp_voltage() {
    // convert unitless quantity to voltage 
    // 0 -> 2^12 - 1 
    // 0mV -> 3300mV
    return (uint16_t) TEMP_SENSOR->DR * 0.8059;
}

uint16_t temp_current_fahrenheit(uint16_t voltage) {
    return (uint16_t) (voltage * 0.189) - 65.79;
}

uint16_t temp_current_celsius(uint16_t voltage) {
    return (uint16_t) (voltage * 0.105) - 54.33;
}
