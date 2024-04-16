/* 
 * File:   led.h
 * Author: Eslam Emara
 *
 * Created on April 15, 2024, 10:22 AM
 */

#ifndef LED_H
#define	LED_H
#include "gpio.h"
/*define your pins here*/
#define LED1    PORT_B,4
#define LED2    PORT_B,5

void led_init(Ports_t port,uint8_t pinNo);
void led_on(Ports_t port,uint8_t pinNo);
void led_off(Ports_t port,uint8_t pinNo);

#endif	/* LED_H */

