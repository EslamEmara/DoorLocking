/* 
 * File:   button.c
 * Author: Eslam Emara
 *
 * Created on April 15, 2024, 10:23 AM
 */
#include "button.h"
void button_init(Ports_t port , uint8_t pinNo){
    DIO_SetPinDirection(port,pinNo,INPUT);
}
uint8_t button_getState(Ports_t port , uint8_t pinNo){
    return DIO_GetPinValue(port,pinNo);
}