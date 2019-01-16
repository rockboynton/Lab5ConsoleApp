/*
 * delay.h
 *
 * Interface for delay functions used in embedded programming.
 */

//include guards
#ifndef DELAY_H_
#define DELAY_H_

//Add address for these memory mapped registers
//Check STM Programming Manual Chapter 4.5
#define STK_CTRL (volatile uint32_t*) 0xE000E010
#define STK_LOAD (volatile uint32_t*) 0xE000E014
#define STK_VAL (volatile uint32_t*) 0xE000E018

#define EN 0
#define TICKINT 1
#define CLKSOURCE 2
#define COUNTFLAG 16

/**
 * delay_1ms
 * 		Busy wait for n ms
 *
 * 		For n iterations
 * 			load number of cycles for 1 ms
 * 			set one to enable and clock source
 *
 * 			wait for countflag to be set
 */
void delay_1ms(uint32_t n);

/**
 * delay_1us
 * 		Busy wait for n us
 *
 * 		For n iterations
 * 			load number of cycles for 1 us
 * 			set one to enable and clock source
 *
 * 			wait for countflag to be set
 */
void delay_1us(uint32_t n);

#endif /* DELAY_H_ */
