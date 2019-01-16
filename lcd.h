/*
 * lcd.h 
 * 
 * API for interfacing with the MSOE dev board LCD display
 */

//Include Guards 
#ifndef LCD_H_
#define LCD_H_

#include <inttypes.h>


/**
 * See LCD documentation ST7066U
 * DB0 = PA4
 * DB1 = PA5
 * DB2 = PA6
 * DB3 = PA7
 * DB4 = PA8
 * DB5 = PA9
 * DB6 = PA10
 * DB7 = PA11 (also busy flag)
 * 
 * RS = PC8 
 * R/W = PC9
 * E = PC10
 * 
 */

#define DB0 4
#define DB1 5
#define DB2 6
#define DB3 7
#define DB4 8
#define DB5 9
#define DB6 10
#define DB7 11 // also busy flag
#define RS  8   
#define RW  9
#define E   10


/**
 * Initializes I/O to interface to communicate with LCD module.
 * Clears and homes the display.
 */ 
void lcd_init();

/**
 * Clears the display.
 * Includes necessary delay.
 */
void lcd_clear();

/**
 * Moves cursor to the home position.
 * Includes necessary delay.
 */ 
void lcd_home();

/**
 * Moves cursor to the position indicated. 
 * 
 * @param row 
 *      zero-based row of desired position
 * @param col 
 *      zero-based column of desired position 
 * Includes necessary delay  
 */ 
void lcd_set_position(uint8_t row, uint8_t col);

/**
 * Prints a null terminated string to the display.
 * Accepts the pointer to a null-terminated string, returns the number of characters written to 
 * the display.
 * 
 * @param str_ptr 
 *      pointer to a null-terminated string
 * @return 
 *      number of characters written to the display
 */ 
uint8_t lcd_print_string(char *str_ptr);

/**
 * Prints a (decimal) number to the display. 
 * Accepts the number to be printed, returns the number of characters written to the display.
 * 
 * @param num 
 *      number to be printed 
 * @return uint32_t 
 *      number of characters written to the display
 */
uint32_t lcd_print_num(uint32_t num);

/**
 * Writes an instruction to the LCD controller.
 *
 * @param instr
 *      instruction to be written to LCD controller
 */
void lcd_write_instr(uint32_t instr);

/**
 * TODO 
 */ 
void lcd_write_data(uint32_t data);

#endif
