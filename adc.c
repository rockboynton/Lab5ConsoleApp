/*
 * adc.c
 *
 *  Created on: Jan 7, 2019
 *      Author: Rock Boynton
 * 
 * Implements functions specified in adc.h to use the MSOE dev board temperature sensor
 */

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

#include "lcd.h"
#include "delay.h"
#include "gpio.h"

void adc_init() {
    // Enable ADC1EN in RCC_APB2ENR
	*(RCC_APB2ENR) |= (1 << ADC1EN);

}