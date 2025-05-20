/*
 * ap.h
 *
 *  Created on: May 9, 2025
 *      Author: USER
 */

#ifndef AP_H_
#define AP_H_

#include "hw.h"
#include "bluetooth.h"
#include "ultrasonic.h"
#include "auto_car.h"
#include "imu.h"
#include "motor.h"

void apInit();
void apMain();

void UART_Transmit();

#endif /* AP_H_ */
