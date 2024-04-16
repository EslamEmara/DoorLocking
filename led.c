/* 
 * File:   led.c
 * Author: Eslam Emara
 *
 * Created on April 15, 2024, 10:22 AM
 */
#include "led.h"

void led_init(Ports_t port,uint8_t pinNo){
    DIO_SetPinDirection(port,pinNo,OUTPUT);
}
void led_on(Ports_t port,uint8_t pinNo){
    DIO_SetPinValue(port,pinNo,HIGH);
}
void led_off(Ports_t port,uint8_t pinNo){
    DIO_SetPinValue(port,pinNo,LOW);
}