/*
 * main.c
 *
 * Console application that will present a menu to the user and offer basic system control.
 * 
 * The following menu options are implemented:
 * 		Read memory – 	The user will provide an address and the program will read that 
 *       				  address and print the contents of that address to the console in hex and
 *  					  decimal format (optional – also binary).
 * 		Write memory –  The user will provide an address and a value and the program will write the
 * 						  provided value to the provided address.
 * 		Dump memory – 	The user will provide an address and an optional length and the program 	*						  will dump the contents of that block of memory to the console.  If no 	*						  length is supplied, defaults to 16 bytes.  The output should be formatted *						  with 8 or 16 bytes per line, in hex.  Each line starts with the address.  *						  As an example, look at the memory view window in the System Workbench 	*						  debugger.
 * 		Help – 			Provides the user with detailed help in using your program
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "uart_driver.h"
#include "led.h"
#include "lcd.h"
#include "keypad.h"
#include "delay.h"
#include "temp_sensor.h"

#define F_CPU 16000000UL

// 0 = main program
// 1 = Thermometer tests
// 2 = Keypad tests
// 1 = LED tests

#define DEBUG 0

#define BUFFER_SIZE 10

// Initialize variables to be used 
uint8_t buffer[BUFFER_SIZE];
uint8_t lastchar = 0;
uint8_t stop = 0;

// File scope helper methods
static void print_help_screen();
static uint32_t read_memory(uint32_t address);
static void write_memory(uint32_t address, uint32_t value);
static void dump_memory(uint32_t address, uint32_t length); // ? length is optional, defaults to 16 bytes



// main
int main() {
	
	// Initialize hardware
	init_usart2(19200,F_CPU);
	led_init();
	lcd_init();
	key_init();
	temp_init();

	// --------------------- THERMOMETER TEST CODE -------------------
	if (DEBUG == 1) {
		uint16_t voltage;
		while (1) {
			voltage = temp_voltage();
			lcd_print_num(voltage);
			delay_1ms(500);
			lcd_clear();
			lcd_print_num(temp_current_celsius(voltage));
			delay_1ms(500);
			lcd_clear();
			lcd_print_num(temp_current_fahrenheit(voltage));
			delay_1ms(500);
			lcd_clear();
			delay_1ms(500);
		}
	}
	//-----------------------------------------------------------

	// --------------------- KEYPAD TEST CODE -------------------
	if (DEBUG == 2) {
			uint8_t key;
			while (1) {
				lcd_clear();
				key = key_getChar();
				lcd_write_data(key);
				delay_1ms(500);
			}
	}
	//-----------------------------------------------------------

	// --------------------- LED TEST CODE -------------------
			if (DEBUG == 3) {
					while (1) {
						led_allOff();
						for (int i = 0; i < 10; i++) {
							led_on(i);
							delay_1ms(500);
						}
					}
			}
	//-----------------------------------------------------------

	// Main program 
	// Never return
	print_help_screen();
	while (1) {
		lastchar = 0;
		stop = 0;
		// Read characters into array. Stop if end of line, or array full.
		// while(stop != 1){
		// 	buffer[lastchar] = getchar();
		// 	if(buffer[lastchar] == '\n')
		// 		stop = 1;
		// 	else
		// 		lastchar = lastchar + 1;
		// 	if(lastchar == BUFFER_SIZE)
		// 		stop = 1;
		// }
		// lastchar = lastchar - 1;

		switch (key) {
			case 'A':
				current_temp_mode();
				break;
			case 'B':
				extremes_mode();
				break;
			case 'C':
				troubleshooting_mode();
				break;
			case 'D':
				toggle_units();
				break;
			case '1':
				print_help_screen();
				break;	
			default:
				break;
		}
	}
	// Never returns
	return 0;
}

static void print_help_screen() {
	printf("H: Help Screen\n"
           "B: Extremes Mode - displays the current warmest and coldest temperatures read\n"
           "C: Trouble Shooting Mode - displays the current temperature and the input voltage "
           "   value coming from the temperatures sensor\n"
           "D: Toggle Celsius/Fahrenheit\n"
		   "1: Help Screen\n");
}

static uint32_t read_memory(uint32_t address) {

}

static void write_memory(uint32_t address, uint32_t value) {
	
}

static void dump_memory(uint32_t address, uint32_t length) {
	
}
