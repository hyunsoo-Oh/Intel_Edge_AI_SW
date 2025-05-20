/*
 * delay.h
 *
 *  Created on: May 19, 2025
 *      Author: USER
 */

#ifndef INC_DELAY_H_
#define INC_DELAY_H_

#include "tim.h"

void delay_us(uint16_t us);
void delay_ms(uint16_t ms, uint8_t *flag);

#endif /* INC_DELAY_H_ */
