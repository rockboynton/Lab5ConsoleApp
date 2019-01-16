/*
 * led.c
 *
 *  Created on: Dec 1, 2018
 *      Author: livingston
 */

#include "led.h"
#include "delay.h"
#include "gpio.h"
#include <inttypes.h>
#include <stdio.h>

static volatile GPIO* GPIOB = 0x40020400;


// Maintain current speed from 0-9
static uint8_t currentSpeed = 5;

// Base frequency of 500ms
const uint16_t BASE_FREQUENCY = 500;  

// Multiplier to change speed 
const uint8_t MULTIPLIER = 50;


void led_init(){ 
	// Enable the GPIOB in RCC_AHB1ENR
	*(RCC_AHB1ENR) |= (1 << GPIOBEN);
	// Turn on to set LED0 - LED9 to output mode ("01")
	// Pins 5-10, 12-15
	// *(GPIOB_MODER) &= ~0xFF3FFC00; // TODO change this to atomic by using temp value
	// *(GPIOB_MODER) |= 0x55155400;
	GPIOB->MODER = ((GPIOB->MODER & ~0xFF3FFC00) | 0x55155400);
}

void led_allOn(){
	// BSRR sets set bits in lower half-word, protects other pins
	*(GPIOB_BSRR) |= 0xF7E0;
}

void led_allOff(){
	// BSRR resets set bits in upper half-word, protects other pins
	*(GPIOB_BSRR) |= (0xF7E0 << 16);
}

void led_on(uint8_t ledIndex){
	*(GPIOB_BSRR) |= (1 << adjustIndex(ledIndex));
}

void led_off(uint8_t ledIndex){
	*(GPIOB_BSRR) |= ((1 << adjustIndex(ledIndex)) << 16);
}

void led_scan(){
	// Scan the light across
	for (int i = 0; i < 10; i++) {
		led_on(i);
		delay_1ms(BASE_FREQUENCY - currentSpeed * MULTIPLIER); 
		led_off(i);
	} 
	// Scan the light back
	for (int i = 8; i >= 0; i--) {
		led_on(i);
		delay_1ms(BASE_FREQUENCY - currentSpeed * MULTIPLIER); 
		led_off(i);
	} 
}

void led_flash(){
	for (int i = 0; i < 10; i++) {
		led_allOn();
		delay_1ms(BASE_FREQUENCY - currentSpeed * MULTIPLIER);
		led_allOff();
		delay_1ms(BASE_FREQUENCY - currentSpeed * MULTIPLIER);
	}
}

void led_setSpeed(uint8_t speed){
	if (0 < speed || speed < 9) {
		currentSpeed = speed;
	} else {
		printf("Error: Index Out of Range\n");
	}
}

void led_incSpeed(){
	if (currentSpeed < 9) {
		currentSpeed++;
	}
}

void led_decSpeed(){
	if (currentSpeed > 0) {
		currentSpeed--;
	}
}

uint8_t getCurrentSpeed() {
	return currentSpeed;
}

uint32_t adjustIndex(uint32_t ledIndex) {
	if (ledIndex <= 5) {
		ledIndex += 5;
	} else if (ledIndex <= 9) {
		ledIndex += 6;
	} 
	return ledIndex;
}


