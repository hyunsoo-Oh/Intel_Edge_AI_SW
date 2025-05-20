/*
 * auto_car.h
 *
 *  Created on: May 15, 2025
 *      Author: User
 */

#ifndef UTIL_INC_AUTO_CAR_H_
#define UTIL_INC_AUTO_CAR_H_

#include "motor.h"
#include "ultrasonic.h"

#define AUTO_CAR_MAX_SPEED   	80
#define AUTO_CAR_MIN_SPEED		50

#define DIST_FORWARD_FAST		50
#define DIST_FORWARD_SLOW		23

#define DIST_FORWARD_FAST_EXIT  (uint16_t)(DIST_FORWARD_FAST * 1.2)
#define DIST_FORWARD_SLOW_EXIT  (uint16_t)(DIST_FORWARD_SLOW * 1.2)

#define DISTANCE_SIDE			18

#define REVERSE_TIME_MS         200
#define ROTATE_TIME_MS          300
#define WAIT_TIME_MS            200

#define ACTION_TIME				200

// 센서 필터 윈도우 크기 (중앙값 필터)
#define FILTER_WINDOW          	3

typedef enum {
	Active_mode, 	// 조종기로 조종
	Passive_mode	// 자율주행
} CarState_t;

typedef enum {
    AUTO_STATE_DECIDE,         // 다음 동작 결정
    AUTO_STATE_FAST_FORWARD,   // 빠른 속도 전진
    AUTO_STATE_SLOW_FORWARD,   // 느린 속도 전진
    AUTO_STATE_REVERSE,        // 후진
    AUTO_STATE_ROTATE,         // 회전
    AUTO_STATE_WAIT,           // 대기
} AutoCarState_t;

void AUTO_Drive();

#endif /* UTIL_INC_AUTO_CAR_H_ */
