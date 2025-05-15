/*
 * ap.h
 *
 *  Created on: May 9, 2025
 *      Author: USER
 */

#ifndef AP_H_
#define AP_H_

#include "hw.h"
#include "l298n.h"
#include "bluetooth.h"
#include "ultrasonic.h"
#include "adxl345.h"
#include "auto_car.h"

void apInit();
void apMain();

void UART_Transmit();

#endif /* AP_H_ */
