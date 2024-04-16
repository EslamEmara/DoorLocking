/* 
 * File:   motor.c
 * Author: Eslam Emara
 *
 * Created on April 15, 2024, 10:12 AM
 */
#include "motor.h"
void motor_init(void){
    DIO_SetPinDirection(MOTOR_A,OUTPUT);
    DIO_SetPinDirection(MOTOR_B,OUTPUT);
    DIO_SetPinDirection(MOTOR_C,OUTPUT);
    DIO_SetPinDirection(MOTOR_D,OUTPUT);
    
    DIO_SetPinValue(MOTOR_A,LOW);
    DIO_SetPinValue(MOTOR_B,LOW);
    DIO_SetPinValue(MOTOR_C,LOW);
    DIO_SetPinValue(MOTOR_D,LOW);
        
}
void motor_on(void){
    DIO_SetPinValue(MOTOR_A,LOW);
    DIO_SetPinValue(MOTOR_B,HIGH);
    DIO_SetPinValue(MOTOR_C,LOW);
    DIO_SetPinValue(MOTOR_D,LOW);
}
void motor_off(void){
    DIO_SetPinValue(MOTOR_A,HIGH);
    DIO_SetPinValue(MOTOR_B,LOW);
    DIO_SetPinValue(MOTOR_C,LOW);
    DIO_SetPinValue(MOTOR_D,LOW);
}