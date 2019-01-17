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

#define DEBUG 4

#define BUFFER_SIZE 20

// Initialize variables to be used 
char buffer[BUFFER_SIZE+1];
uint32_t *address;
uint32_t value;
uint32_t length;

// File scope helper methods
static void print_help_screen();
static uint32_t read_memory(uint32_t * address);
static void write_memory(uint32_t * address, uint32_t value);
static void dump_memory(uint32_t * address, uint32_t length); // ? length is optional, defaults to 16 bytes
static uint32_t get_input();



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

	// --------------------- USART TEST CODE -------------------
	if (DEBUG == 4) {
		char entry[20];
			while (1) {
				printf("Enter name: ");
				gets(entry);
				delay_1ms(500);
				printf("Your name: %s\n", entry);
				delay_1ms(1000);
			}
	}
	//-----------------------------------------------------------

	// Main program 
	// Never return
	print_help_screen();
	while (1) {
		printf("Enter Command: ");
		gets(buffer); 
		switch (0) {
			case 'r':
				printf("Enter address to read from in hex(0x...) or decimal (...): ");
				address = (uint32_t*) get_input();
				value = read_memory(address);
				printf("Value at address %x:  %d", address, value);
				break;
			case 'w':
				printf("Enter address to write to in hex(0x...) or decimal (...): ");
				address = (uint32_t*) get_input();
				printf("Enter value to write to %x in hex(0x...) or decimal (...): ", address);
				value = get_input();
				write_memory(address, value);
				break;
			case 'd':
				printf("Enter address to begin dump in hex(0x...) or decimal (...): ");
				address = get_input();
				printf("Enter length of dump starting at %x in hex(0x...) or decimal (...): ", address);
				length = get_input();
				dump_memory(address,length);
				break;
			case 'h':
				print_help_screen();
				break;	
			default:
				puts("Invalid Command.");
				break;
		}
	}
	// Never returns
	return 0;
}

static void print_help_screen() {
	printf(	"Read memory – 	The user will provide an address and the program will read that\n" 				"					address and print the contents of that address to the console in\n"
			" 			 		hex and decimal format (optional – also binary).\n"
			"Write memory – The user will provide an address and a value and the program will\n" 		"				write the provided value to the provided address.\n"
			"Dump memory – 	The user will provide an address and an optional length and the program 					will dump the contents of that block of memory to the console.  If 						no length is supplied, defaults to 16 bytes.  The output should be 						formatted with 8 or 16 bytes per line, in hex.  Each line starts 						with the address.\n"
			"Help – 		Provides the user with detailed help in using your program\n");
}

static uint32_t read_memory(uint32_t * address) {
	return *address;
}

static void write_memory(uint32_t * address, uint32_t value) {
	*address = value;
}

static void dump_memory(uint32_t * address, uint32_t length) {
	for(int i = 0; i < length; i++) {
		printf("Value at address %x:  %d", address, *address);
		address++;
	}
}

static uint32_t get_input() {
	char input_str[BUFFER_SIZE + 1];
	uint32_t input;
	char *ptr; // for strtol()
	uint8_t valid = 0;
	while (!valid) {
		gets(input_str);
		input = (uint32_t) strtol(input_str, &ptr, 0); 
		if (input != 0) {
			valid = 1;
		} else {
			puts("Invalid.");
		}
	}
	return input;
}
