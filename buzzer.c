/* 
 * File:   buzzer.c
 * Author: Eslam Emara
 *
 * Created on April 15, 2024, 10:22 AM
 */
#include "buzzer.h"

void buzzer_init(Ports_t port,uint8_t pinNo){
    DIO_SetPinDirection(port,pinNo,OUTPUT);
}
void buzzer_on(Ports_t port,uint8_t pinNo){
    DIO_SetPinValue(port,pinNo,HIGH);
}
void buzzer_off(Ports_t port,uint8_t pinNo){
    DIO_SetPinValue(port,pinNo,LOW);
}