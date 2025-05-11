/*
 * hm10.h
 *
 *  Created on: May 9, 2025
 *      Author: USER
 */

#ifndef HW_INC_HC05_H_
#define HW_INC_HC05_H_

#include "def.h"
#include "usart.h"
#include "l298n.h"

void BLUETOOTH_Parsing(MotorState *motor, const uint8_t *rxData);
int16_t STR_TO_Integer(char *s);

#endif /* HW_INC_HC05_H_ */
