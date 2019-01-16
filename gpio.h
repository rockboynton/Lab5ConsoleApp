/*
 * gpio.h
 *
 *  Created on: Dec 9, 2018
 *      Author: livingston
 */

#ifndef GPIO_H_
#define GPIO_H_

/**
 * How to use:
 *   In the C file you wish to use gpio port do the following:
 *   	0. include gpio.h header
 *
 *   		#include "gpio.h"
 *
 *   	1. Create a gpio pointer to the structure.
 *   					(usually as a file static pointer)
 *
 *   		EG: static volatile GPIO* GPIOC = 0x40020800;
 *
 *   	2. To use the control registers use the '->' operator
 *
 *   		EG:  GPIOC->MODER |= .......;
 *
 *   				or
 *
 *   		 	(*GPIOC).MODER (I like the above form).
 */

#include <inttypes.h>

#define RCC_AHB1ENR (volatile uint32_t*) 0x40023830
#define RCC_APB2ENR (volatile uint32_t*) 0x40023844
#define GPIOAEN 0		// GPIOA Enable is bit 0 in RCC_APB1LPENR
#define GPIOBEN 1
#define GPIOCEN 2
#define ADC1EN  8


typedef struct {
	uint32_t MODER;
	uint32_t OTYPER;
	uint32_t OSPEEDER;
	uint32_t PUPDR;
	uint32_t IDR;
	uint32_t ODR;
	uint32_t BSRR;
} GPIO;

// Analog to Digital Converter
typedef struct {
	uint32_t SR;
	uint32_t CR1;	
	uint32_t CR2;
	uint32_t SMPR1;
	uint32_t SMPR2;
	uint32_t JOFR1;
	uint32_t JOFR2;
	uint32_t JOFR3;
	uint32_t JOFR4;
	uint32_t HTR;
	uint32_t LTR;
	uint32_t SQR1;
	uint32_t SQR2;
	uint32_t SQR3;
	uint32_t JSQR;
	uint32_t JDR1;
	uint32_t JDR2;
	uint32_t JDR3;
	uint32_t JDR4;
	uint32_t DR;
} ADC;

#endif /* GPIO_H_ */
