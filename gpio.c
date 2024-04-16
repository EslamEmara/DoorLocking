/*
 * File:   gpio.c
 * Author: Eslam Emara
 *
 * Created on April 15, 2024, 6:44 AM
 */

#include "gpio.h"

/*Setting the directtion of a pin
 *just pass it the port name as defined (PORT_A,PORT_B,...)
 * and the pin number 
 * and direction (OUTPUT|INPUT)
 */
void DIO_SetPinDirection (Ports_t portName , uint8_t pinNo , Direction_t direction){
    switch (portName){
        case PORT_A:
            if(direction == OUTPUT){
                CLEAR_BIT(TRISA,pinNo);         /*check out this macro defined fn in the .h file*/
            }
            else{
                SET_BIT(TRISA,pinNo);           /*this one also*/
            }
        break;
        case PORT_B:
            if(direction == OUTPUT){
                CLEAR_BIT(TRISB,pinNo);
            }
            else{
                SET_BIT(TRISB,pinNo);
            }
        break;
        case PORT_C:
            if(direction == OUTPUT){
                CLEAR_BIT(TRISC,pinNo);
            }
            else{
                SET_BIT(TRISC,pinNo);
            }
        break;
        case PORT_D:
            if(direction == OUTPUT){
                CLEAR_BIT(TRISD,pinNo);
            }
            else{
                SET_BIT(TRISD,pinNo);
            }
        break;
        case PORT_E:
            if(direction == OUTPUT){
                CLEAR_BIT(TRISE,pinNo);
            }
            else{
                SET_BIT(TRISE,pinNo);
            }
        break;
            
    }
}

/*same passing arguments as before but send value instead of direction (HIGH|LOW)*/
void DIO_SetPinValue(Ports_t portName , uint8_t pinNo , Value_t value){
    switch (portName){
        case PORT_A:
            if(value == LOW){
                CLEAR_BIT(PORTA,pinNo);
            }
            else{
                SET_BIT(PORTA,pinNo);
            }
        break;
        case PORT_B:
            if(value == LOW){
                CLEAR_BIT(PORTB,pinNo);
            }
            else{
                SET_BIT(PORTB,pinNo);
            }
        break;
        case PORT_C:
            if(value == LOW){
                CLEAR_BIT(PORTC,pinNo);
            }
            else{
                SET_BIT(PORTC,pinNo);
            }
        break;
        case PORT_D:
            if(value == LOW){
                CLEAR_BIT(PORTD,pinNo);
            }
            else{
                SET_BIT(PORTD,pinNo);
            }
        break;
        case PORT_E:
            if(value == LOW){
                CLEAR_BIT(PORTE,pinNo);
            }
            else{
                SET_BIT(PORTE,pinNo);
            }
        break;
    }
}
uint8_t DIO_GetPinValue(Ports_t portName , uint8_t pinNo){
    uint8_t flush = PORTA;          /*from the datasheet i figured that we need to clear the port before reading from it*/
    flush = PORTB;                      /*so this readings does it, it flushed the port*/
    flush = PORTC;
    flush = PORTD;
    flush = PORTE;
    switch (portName){
        case PORT_A:
            return GET_BIT(PORTA,pinNo);
        break;
        case PORT_B:
            return GET_BIT(PORTB,pinNo);
        break;
        case PORT_C:
            return GET_BIT(PORTC,pinNo);
        break;
        case PORT_D:
            return GET_BIT(PORTD,pinNo);
        break;
        case PORT_E:
            return GET_BIT(PORTE,pinNo);
        break;
    }
    return 1;
}
/*Setting the whole port one time*/
void DIO_SetPortValue(Ports_t portName , uint8_t value){
    switch (portName){
        case PORT_A:
             PORTA = value;
        break;
        case PORT_B:
             PORTB = value;
        break;
        case PORT_C:
             PORTC = value;
        break;
        case PORT_D:
             PORTD = value;
        break;
        case PORT_E:
             PORTE = value;
        break;
    }
}
/*Setting only upper 4 bits of the port (helpful in lcd)*/
void DIO_SetUpperHalfPortValue (Ports_t portName , uint8_t value) {
	switch(portName) {
		case PORT_A :
		PORTA = (PORTA & 0x0F) |  value ;
		break;
		
		case PORT_B :
		PORTB = (PORTB & 0x0F) |  value ;
		break;
		
		case PORT_C :
		PORTC = (PORTC & 0x0F) |  value ;
		break;
		
		case PORT_D :
		PORTD = (PORTD & 0x0F) | value  ;
		break;
        
        case PORT_E :
		PORTE = (PORTE & 0x0F) | value  ;
		break;
        
        
	}
}
/*Toggle a pin(helpful in led)*/
void DIO_TogglePin (Ports_t portName , uint8_t pinNo) {
	switch(portName) {
		case PORT_A :
            TOGGLE_BIT(PORTA,pinNo);
		break;
		
		case PORT_B :
            TOGGLE_BIT(PORTB,pinNo);
		break;
		
		case PORT_C :
            TOGGLE_BIT(PORTC,pinNo);
		break;
		
		case PORT_D :
            TOGGLE_BIT(PORTD,pinNo);
		break;
        
        case PORT_E :
            TOGGLE_BIT(PORTE,pinNo);
		break;
	}
}

