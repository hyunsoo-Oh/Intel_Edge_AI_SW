/*
 * l298n.h
 *
 *  Created on: May 9, 2025
 *      Author: USER
 */

/*
 * IN0 : PC6
 * IN1 : PC8
 * IN2 : PC10
 * IN3 : PC12
 */

#ifndef HW_INC_L298N_H_
#define HW_INC_L298N_H_

#include "gpio.h"

void MOTER_Ctrl(uint8_t r_dir, uint8_t l_dir);

#endif /* HW_INC_L298N_H_ */
