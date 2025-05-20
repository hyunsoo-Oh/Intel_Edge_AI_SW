/*
 * ap.h
 *
 *  Created on: May 10, 2025
 *      Author: User
 */

#ifndef AP_H_
#define AP_H_

#include "hw.h"

void apInit();
void apMain();

void BTN_Control(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, uint8_t f);

#endif /* AP_H_ */
