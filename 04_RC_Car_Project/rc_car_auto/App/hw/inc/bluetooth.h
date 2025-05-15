/*
 * bluetooth.h
 *
 *  Created on: May 9, 2025
 *      Author: USER
 */

#ifndef HW_INC_BLUETOOTH_H_
#define HW_INC_BLUETOOTH_H_

#include "def.h"
#include "usart.h"
#include "l298n.h"
#include "auto_car.h"

void BLUETOOTH_Parsing(MotorState *motor, const uint8_t *rxData);

#endif /* HW_INC_BLUETOOTH_H_ */
