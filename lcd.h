/* 
 * File:   lcd.h
 * Author: Eslam Emara
 *
 * Created on April 15, 2024, 8:39 AM
 */

#ifndef LCD_H
#define	LCD_H
#include "gpio.h"

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/
/* Use higher 4 bits in the data port */

/* LCD HW Pins */
#define RS PORT_D,1
#define RW PORT_D,2
#define E  PORT_D,3

#define LCD_CTRL_PORT		 PORT_D
#define LCD_CTRL_PORT_DIR	 PORT_D

#define LCD_DATA_PORT		 PORT_D
#define LCD_DATA_PORT_DIR	 PORT_D

/* LCD Commands */
#define CLEAR_COMMAND					0x01
#define FOUR_BITS_DATA_MODE				0x02
#define TWO_LINE_LCD_Four_BIT_MODE	    0x28
#define TWO_LINE_LCD_Eight_BIT_MODE		0x38
#define CURSOR_OFF						0x0C
#define CURSOR_ON						0x0E
#define SET_CURSOR_LOCATION			    0x80

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void LCD_sendCommand(uint8_t command);
void LCD_displayCharacter(uint8_t data);
void LCD_displayString(char *Str);
void LCD_init(void);
void LCD_clearScreen(void);
void LCD_displayStringRowColumn(uint8_t row,uint8_t col,char *Str);
void LCD_goToRowColumn(uint8_t row,uint8_t col);


#endif	/* LCD_H */

