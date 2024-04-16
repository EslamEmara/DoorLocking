/*
 * File:   keypad.c
 * Author: Eslam Emara
 *
 * Created on April 15, 2024, 7:21 AM
 */


#include "keypad.h"

/*check keypadConfig.h before calling the init function*/
void keypad_init(){
	#ifdef ROW_1						/*Configure rows as output*/
		DIO_SetPinDirection(ROW_1,OUTPUT);
	#endif
	#ifdef ROW_2
		DIO_SetPinDirection(ROW_2,OUTPUT);
	#endif
	#ifdef ROW_3
		DIO_SetPinDirection(ROW_3,OUTPUT);
	#endif
	#ifdef ROW_4
		DIO_SetPinDirection(ROW_4,OUTPUT);
	#endif
	
	#ifdef COL_1						/*configure columns as inputs */
		DIO_SetPinDirection(COL_1,INPUT);
	#endif
	
	#ifdef COL_2
		DIO_SetPinDirection(COL_2,INPUT);
	#endif
	
	#ifdef COL_3
		DIO_SetPinDirection(COL_3,INPUT);
	#endif
	
}

/*Output 1 to desired rows one at a time*/
void keypad_line_scan(){
    static uint8_t keypadScan = 0x01;
    keypadScan =( keypadScan <<1);
    if( keypadScan > 0x08){
        keypadScan = 0x01;
    }
    PORTC = keypadScan;     /*outputting to portC directly*/
    /*it's better to output to the defined pins in config file but 
     according to our connection this is easier*/
}

uint8_t keypad_value(uint8_t portValue){
    switch (portValue){
        case 0x11:                  /*map the port value to the pressed button*/
            return '1';
            break;
        case 0x12:
            return '4';
            break;
        case 0x14:
            return '7';
            break;
        case 0x18:
            return '*';
            break;
        
        case 0x21:
            return '2';
            break;
        case 0x22:
            return '5';
            break;
        case 0x24:
            return '8';
            break;
        case 0x28:
            return '0';
            break;
       
        case 0x41:
            return '3';
            break;
        case 0x42:
            return '6';
            break;   
        case 0x44:
            return '9';
            break;
        case 0x48:
            return '#';
            break;
    }
    return NO_KEY_PRESSED;
}
uint8_t keypad_read(){
    keypad_line_scan();                 /*scan the rows*/
    if((KEYPAD_PORT & 0b01110000) != 0){  /*a number is pressed*/
        uint8_t keyValue = keypad_value(KEYPAD_PORT); /*see which one is pressed*/
        return keyValue;            /*return a character of the pressed button*/
    }
    return NO_KEY_PRESSED;           /*return NO_KEY_PRESSED*/
}
