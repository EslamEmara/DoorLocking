/* 
 * File:   pir.h
 * Author: Eslam Emara
 *
 * Created on April 16, 2024, 12:55 AM
 */

#ifndef PIR_H
#define	PIR_H

#include "gpio.h"
#include <xc.h>

/*define your pin here*/
#define PIR       PORT_A,2


void pir_init(Ports_t port , uint8_t pinNo);
uint8_t pir_getState(Ports_t port , uint8_t pinNo);
#endif	/* PIR_H */

