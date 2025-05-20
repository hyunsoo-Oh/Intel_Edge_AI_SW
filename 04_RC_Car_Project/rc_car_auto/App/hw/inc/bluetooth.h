/*
 * bluetooth.h
 *
 *  Created on: May 9, 2025
 *      Author: USER
 */

#ifndef HW_INC_BLUETOOTH_H_
#define HW_INC_BLUETOOTH_H_

#include <motor.h>
#include "def.h"
#include "usart.h"
#include "auto_car.h"

#define DMA_BUF_SIZE		64
#define COMMAND_MAX			6

void Bluetooth_Init(void);
void BLUETOOTH_Parsing(MotorState *motor);

#endif /* HW_INC_BLUETOOTH_H_ */
