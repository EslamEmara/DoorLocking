#ifndef GPIO_H
#define	GPIO_H

#include <xc.h>

/*Type definitions for easy usage of bits*/
typedef unsigned char uint8_t ;
typedef signed char int8_t ; 
typedef unsigned short int uint16_t ; 
typedef signed short int int16_t ;
typedef unsigned int uint32 ;
typedef signed int int32 ;
typedef unsigned long long uint64 ; 
typedef signed long long int64 ; 

/*Some helpful macros to use in bit manipulation**/
#define SET_BIT(REG,BITNO) (REG)|= 1<<(BITNO)
#define CLEAR_BIT(REG,BITNO) (REG)&=~(1<<(BITNO))
#define TOGGLE_BIT(REG,BITNO) (REG)^= 1<<(BITNO)
#define GET_BIT(reg,n)		(((reg)>>(n)) & 1)

/*Defined enums to use in passing objects*/
typedef enum{INPUT,OUTPUT}Direction_t;
typedef enum{PORT_A,PORT_B,PORT_C,PORT_D,PORT_E}Ports_t;
typedef enum{LOW=0,HIGH=1} Value_t;

/*APIs*/
void DIO_SetPinDirection (Ports_t portName , uint8_t pinNo , Direction_t direction);
void DIO_SetPinValue(Ports_t portName , uint8_t pinNo , Value_t value);
uint8_t DIO_GetPinValue(Ports_t portName , uint8_t pinNo);
void DIO_SetPortValue(Ports_t portName , uint8_t value);
void DIO_SetUpperHalfPortValue (Ports_t portName , uint8_t value) ;
void DIO_TogglePin (Ports_t portName , uint8_t pinNo) ;

#endif	

