/*
 * bluetooth.h
 *
 *  Created on: May 19, 2025
 *      Author: USER
 */

#ifndef INC_BLUETOOTH_H_
#define INC_BLUETOOTH_H_

#include "motor.h"
#include "FreeRTOS.h"
#include "queue.h"

void BLUETOOTH_Init(void);
void BLUETOOTH_Parsing(void);

#endif /* INC_BLUETOOTH_H_ */
