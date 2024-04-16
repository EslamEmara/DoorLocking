/* 
 * File:   lcd.c
 * Author: Eslam Emara
 *
 * Created on April 15, 2024, 8:40 AM
 */

#include "lcd.h"
#define _XTAL_FREQ     4000000

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
void LCD_init(void)
{
//	LCD_CTRL_PORT_DIR |= (1<<E) | (1<<RS) | (1<<RW); /* Configure the control pins(E,RS,RW) as output pins */
	DIO_SetPinDirection( E, OUTPUT);
	DIO_SetPinDirection( RS, OUTPUT);
	DIO_SetPinDirection( RW, OUTPUT);
	
	DIO_SetPortValue(LCD_CTRL_PORT_DIR, 0x00);
	DIO_SetPortValue(LCD_DATA_PORT_DIR, 0x00);

			//LCD_DATA_PORT_DIR |= 0xF0; /* Configure the highest 4 bits of the data port as output pins */
    DIO_SetPinDirection(LCD_DATA_PORT_DIR, 4, OUTPUT);
    DIO_SetPinDirection(LCD_DATA_PORT_DIR, 5, OUTPUT);
    DIO_SetPinDirection(LCD_DATA_PORT_DIR, 6, OUTPUT);
    DIO_SetPinDirection(LCD_DATA_PORT_DIR, 7, OUTPUT);
    
	LCD_sendCommand(FOUR_BITS_DATA_MODE); /* initialize LCD in 4-bit mode */
	LCD_sendCommand(TWO_LINE_LCD_Four_BIT_MODE); /* use 2-line lcd + 4-bit Data Mode + 5*7 dot display Mode */


	LCD_sendCommand(CURSOR_OFF); /* cursor off */
	LCD_sendCommand(CLEAR_COMMAND); /* clear LCD at the beginning */
}

void LCD_sendCommand(uint8_t command)
{
	//CLEAR_BIT(LCD_CTRL_PORT,RS); /* Instruction Mode RS=0 */
	DIO_SetPinValue(RS, LOW);
	
	//CLEAR_BIT(LCD_CTRL_PORT,RW); /* write data to LCD so RW=0 */
	DIO_SetPinValue(RW, LOW);
	__delay_ms(1);
	//delay_us(1); /* delay for processing Tas = 50ns */
	
	//SET_BIT(LCD_CTRL_PORT,E); /* Enable LCD E=1 */
	DIO_SetPinValue(E, HIGH);
	
	//delay_us(1); /* delay for processing Tpw - Tdws = 190ns */
	__delay_ms(1);
	
	
	/* out the highest 4 bits of the required command to the data bus D4 --> D7 */
		//LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | (command & 0xF0);
    DIO_SetUpperHalfPortValue(LCD_DATA_PORT, (command & 0xF0));

	//delay_us(1); /* delay for processing Tdsw = 100ns */
	__delay_ms(1);
	
	//CLEAR_BIT(LCD_CTRL_PORT,E); /* disable LCD E=0 */
	DIO_SetPinValue( E, LOW);
	
	//delay_us(1); /* delay for processing Th = 13ns */
	__delay_ms(1);
	
//	SET_BIT(LCD_CTRL_PORT,E); /* Enable LCD E=1 */
	DIO_SetPinValue( E, HIGH);
	//delay_us(1); /* delay for processing Tpw - Tdws = 190ns */
	__delay_ms(1);

	/* out the lowest 4 bits of the required command to the data bus D4 --> D7 */
	//LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | ((command & 0x0F) << 4);
	DIO_SetUpperHalfPortValue(LCD_DATA_PORT, ((command & 0x0F) << 4));

	//delay_us(1); /* delay for processing Tdsw = 100ns */
	__delay_ms(1);
	
	//CLEAR_BIT(LCD_CTRL_PORT,E); /* disable LCD E=0 */
	DIO_SetPinValue(E, LOW);
	
	//delay_us(1); /* delay for processing Th = 13ns */
	__delay_ms(1);
	

}

void LCD_displayCharacter(uint8_t data)
{
	DIO_SetPinValue(RS, HIGH);
	
	DIO_SetPinValue(RW, LOW);
	
	__delay_ms(1);
	
    DIO_SetPinValue(E, HIGH);
	__delay_ms(1);
	/* out the highest 4 bits of the required data to the data bus D4 --> D7 */
	//LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | (data & 0xF0);
	DIO_SetUpperHalfPortValue(LCD_DATA_PORT, (data & 0xF0));

	__delay_ms(1);
	
	DIO_SetPinValue( E, LOW);
	
	__delay_ms(1);
	DIO_SetPinValue( E, HIGH);
	
	__delay_ms(1);

	/* out the lowest 4 bits of the required data to the data bus D4 --> D7 */
	DIO_SetUpperHalfPortValue(LCD_DATA_PORT, ((data & 0x0F) << 4));
	__delay_ms(1);
	DIO_SetPinValue( E, LOW);
    __delay_ms(1);
	

}

void LCD_displayString(char *Str)
{
	uint8_t i = 0;
	while(Str[i] != '\0')
	{
		LCD_displayCharacter(Str[i]);
		i++;
	}
}

void LCD_goToRowColumn(uint8_t row,uint8_t col)
	{
	uint8_t Address = 0;

	/* first of all calculate the required address */
	switch(row)
	{
		case 0:
				Address=col;
				break;
		case 1:
				Address=col+0x40;
				break;
		case 2:
				Address=col+0x10;
				break;
		case 3:
				Address=col+0x50;
				break;
			
	}
	/* to write to a specific address in the LCD
	 * we need to apply the corresponding command 0b10000000+Address */
	LCD_sendCommand(Address | SET_CURSOR_LOCATION);
}

void LCD_displayStringRowColumn(uint8_t row,uint8_t col,char *Str)
{
	LCD_goToRowColumn(row,col); /* go to to the required LCD position */
	LCD_displayString(Str); /* display the string */
}

void LCD_clearScreen(void)
{
	LCD_sendCommand(CLEAR_COMMAND); //clear display
}


