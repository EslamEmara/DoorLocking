/* 
 * File:   button.h
 * Author: Eslam Emara
 *
 * Created on April 15, 2024, 10:22 AM
 */

#ifndef BUTTON_H
#define	BUTTON_H

#include "gpio.h"
#include <xc.h>

/*define your pins here*/
#define SYSTEM_BUTTON       PORT_A,3
#define RESET_BUTTON        PORT_A,4
#define EMERGENCY_BUTTON    PORT_A,5

void button_init(Ports_t port , uint8_t pinNo);
uint8_t button_getState(Ports_t port , uint8_t pinNo);
#endif	/* BUTTON_H */

