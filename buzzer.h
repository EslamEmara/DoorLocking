/* 
 * File:   buzzer.h
 * Author: Eslam Emara
 *
 * Created on April 15, 2024, 10:22 AM
 */

#ifndef BUZZER_H
#define	BUZZER_H
#include "gpio.h"

#define BUZZER    PORT_A,0

void buzzer_init(Ports_t port,uint8_t pinNo);
void buzzer_on(Ports_t port,uint8_t pinNo);
void buzzer_off(Ports_t port,uint8_t pinNo);

#endif	/* BUZZER_H */

