/*
 * auto_car.h
 *
 *  Created on: May 15, 2025
 *      Author: User
 */

#ifndef UTIL_INC_AUTO_CAR_H_
#define UTIL_INC_AUTO_CAR_H_

#include "l298n.h"
#include "ultrasonic.h"

typedef enum {
	Active_mode, Passive_mode
} CarState_t;

#define AUTO_CAR_MAX_SPEED   	99
#define AUTO_CAR_MID_SPEED      80
#define AUTO_CAR_MIN_SPEED		50

void AUTO_Drive();

#endif /* UTIL_INC_AUTO_CAR_H_ */
