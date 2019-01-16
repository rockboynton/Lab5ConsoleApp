/*
 * keypad.h 
 * 
 * API for interfacing with the MSOE dev board keypad
 */

//Include Guards 
#ifndef KEYPAD_H_
#define KEYPAD_H_

#include <inttypes.h>

// Keypad pin assignments for GPIOC
#define KEYPAD_COL1 0
#define KEYPAD_COL2 1
#define KEYPAD_COL3 2
#define KEYPAD_COL4 3
#define KEYPAD_ROW1 4
#define KEYPAD_ROW2 5
#define KEYPAD_ROW3 6
#define KEYPAD_ROW4 7


#define ROW_COUNT 4
#define COL_COUNT 4

/**
 * Initialize the keypad GPIO port.
 */
void key_init();

/**
 * Returns a numeric code representing the button on the keypad that was pressed (1 to 16), or 0 if 
 * no button is pressed. 
 * 
 * @return uint8_t 
 *      numeric code representing the button on the keypad that was pressed
 */
uint8_t key_getKey_noBlock();

/**
 * Waits until a key on the keypad is pressed then returns the numeric code representing it (1 to 
 * 16), or 0 if no button is pressed. 
 * Returns after said key is released.
 * 
 * @return uint8_t 
 *      numeric code representing the button on the keypad that was pressed
 */
uint8_t key_getKey();

/**
 * Waits until a key on the keypad is pressed then returns the ASCII code corresponding to the key 
 * press.
 * Returns after said key is released.
 * 
 * @return uint8_t 
 *      ASCII code corresponding to the key press
 */
uint8_t key_getChar();


#endif
