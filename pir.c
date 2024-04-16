/* 
 * File:   pir.c
 * Author: Eslam Emara
 *
 * Created on April 16, 2024, 12:55 AM
 */
#include "pir.h"
void pir_init(Ports_t port , uint8_t pinNo){
    DIO_SetPinDirection(port,pinNo,INPUT);
}
uint8_t pir_getState(Ports_t port , uint8_t pinNo){
    return DIO_GetPinValue(port,pinNo);
}

