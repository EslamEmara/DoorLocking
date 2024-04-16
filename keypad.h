/* 
 * File:   keypad.h
 * Author: Eslam Emara
 *
 * Created on April 15, 2024, 7:22 AM
 */

#ifndef KEYPAD_H
#define	KEYPAD_H

#include "keypadConfig.h"
#include "gpio.h"

#define NO_KEY_PRESSED		0				/*return value if no button is pressed*/

void keypad_init(void);
void keypad_line_scan(void);
uint8_t keypad_value(uint8_t portValue);
uint8_t keypad_read(void);

#endif	/* KEYPAD_H */

