/*
 * hw.h
 *
 *  Created on: May 10, 2025
 *      Author: User
 */

#ifndef HW_HW_H_
#define HW_HW_H_

#include "def.h"
#include "adc.h"
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

#include "parsing.h"

#define BTN_SK1		GPIO_PIN_6
#define BTN_SK2		GPIO_PIN_7
#define BTN_SWA		GPIO_PIN_4
#define BTN_SWB		GPIO_PIN_5

void hwInit();

#endif /* HW_HW_H_ */
