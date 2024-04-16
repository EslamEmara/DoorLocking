/* 
 * File:   motor.h
 * Author: Eslam Emara
 *
 * Created on April 15, 2024, 10:11 AM
 */

#ifndef MOTOR_H
#define	MOTOR_H

#include "gpio.h"

/*define your pins here*/
#define MOTOR_A     PORT_B,0
#define MOTOR_B     PORT_B,1
#define MOTOR_C     PORT_B,2
#define MOTOR_D     PORT_B,3

void motor_init(void);
void motor_on(void);
void motor_off(void);

#endif	/* MOTOR_H */

