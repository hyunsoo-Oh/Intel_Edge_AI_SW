/*
 * auto_car.c
 *
 *  Created on: May 15, 2025
 *      Author: User
 */

#include "auto_car.h"

CarState_t mode = Active_mode;
static AutoCarState_t autoState = AUTO_STATE_FAST_FORWARD;
static uint32_t actionStartTime = 0;

extern MotorState motor;
extern UltraData uData[3];

// 내부 함수: 중앙값 필터
static uint16_t median_filter(uint16_t *buf, uint8_t size) {
    uint16_t tmp[size];
    for (uint8_t i = 0; i < size; i++) tmp[i] = buf[i];
    for (uint8_t i = 0; i < size - 1; i++) {
        for (uint8_t j = i + 1; j < size; j++) {
            if (tmp[j] < tmp[i]) {
                uint16_t t = tmp[i]; tmp[i] = tmp[j]; tmp[j] = t;
            }
        }
    }
    return tmp[size/2];
}

void AUTO_Drive(void) {
    // 거리 읽기 및 필터링
    static uint16_t bufLeft[FILTER_WINDOW];
    static uint16_t bufRight[FILTER_WINDOW];
    static uint16_t bufCenter[FILTER_WINDOW];
    static uint8_t idx = 0;

    bufLeft[idx]   = uData[0].distance_cm;
    bufRight[idx]  = uData[1].distance_cm;
    bufCenter[idx] = uData[2].distance_cm;
    if (++idx >= FILTER_WINDOW) idx = 0;

    uint16_t distL = median_filter(bufLeft, FILTER_WINDOW);
    uint16_t distR = median_filter(bufRight, FILTER_WINDOW);
    uint16_t distC = median_filter(bufCenter, FILTER_WINDOW);

    switch (autoState)
    {
        case AUTO_STATE_DECIDE:
            if (distC > DIST_FORWARD_FAST)			autoState = AUTO_STATE_FAST_FORWARD;
            else if (distC > DIST_FORWARD_SLOW)		autoState = AUTO_STATE_SLOW_FORWARD;
            else
            {
                autoState = AUTO_STATE_REVERSE;
                actionStartTime = HAL_GetTick();
            }
            break;

        case AUTO_STATE_FAST_FORWARD:
        case AUTO_STATE_SLOW_FORWARD:
        	uint16_t exitThresh = (autoState == AUTO_STATE_FAST_FORWARD) ?
						  			DIST_FORWARD_FAST_EXIT : DIST_FORWARD_SLOW_EXIT;
			uint8_t speed 		= (autoState == AUTO_STATE_FAST_FORWARD) ?
									AUTO_CAR_MAX_SPEED : AUTO_CAR_MIN_SPEED;

            motor.front_direction = DIR_FORWARD;

            if (distR < 9)
            {
                motor.side_direction = DIR_LEFT;
                motor.base_speed     = speed;
                motor.dir_speed      = speed / 2;
            }
            else if (distL < 9)
            {
                motor.side_direction = DIR_RIGHT;
                motor.base_speed     = speed;
                motor.dir_speed      = speed / 2;
            }
            else
            {
                motor.side_direction = DIR_FORWARD;
                motor.base_speed     = speed;
                motor.dir_speed      = speed;
            }

            MOTOR_SetMotor(motor);

            if (distC <= exitThresh)
			{
            	autoState = AUTO_STATE_DECIDE;
			}
            break;

        case AUTO_STATE_REVERSE:
            if ((HAL_GetTick() - actionStartTime) < REVERSE_TIME_MS)
            {
                motor.front_direction = DIR_BACKWARD;
                motor.side_direction  = DIR_BACKWARD;
                motor.base_speed      = AUTO_CAR_MIN_SPEED;
                motor.dir_speed       = AUTO_CAR_MIN_SPEED;

                MOTOR_SetMotor(motor);
            }
            else
            {
                autoState = AUTO_STATE_ROTATE;
                actionStartTime = HAL_GetTick();
            }
            break;


        case AUTO_STATE_ROTATE:
            if ((HAL_GetTick() - actionStartTime) < ROTATE_TIME_MS)
            {
                motor.base_speed = AUTO_CAR_MIN_SPEED;
                motor.dir_speed  = AUTO_CAR_MIN_SPEED;

                if (distR + 5 > distL)
                {
                    MOTOR_Rotate(ROTATE_LEFT);
                }
                else if (distL + 5 > distR)
                {
                    MOTOR_Rotate(ROTATE_RIGHT);
                }
                else
                {
                    motor.front_direction = DIR_BACKWARD;
                    motor.side_direction  = DIR_BACKWARD;
                    motor.base_speed      = AUTO_CAR_MIN_SPEED;
                    motor.dir_speed       = AUTO_CAR_MIN_SPEED;

                    MOTOR_SetMotor(motor);
                }
            }
            else
            {
                autoState = AUTO_STATE_WAIT;
                actionStartTime = HAL_GetTick();

                motor.front_direction = DIR_STOP;
                motor.side_direction  = DIR_STOP;
                motor.base_speed      = 0;
                motor.dir_speed       = 0;

                MOTOR_SetMotor(motor);
            }
            break;

        case AUTO_STATE_WAIT:
            if ((HAL_GetTick() - actionStartTime) >= WAIT_TIME_MS)
            {
                autoState = AUTO_STATE_DECIDE;
            }
            break;

        default:
            autoState = AUTO_STATE_DECIDE;
            break;
    }
}
