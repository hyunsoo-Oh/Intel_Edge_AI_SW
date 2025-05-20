/*
 * motor.c
 *
 *  Created on: May 19, 2025
 *      Author: USER
 */

#include "motor.h"

MotorState motor = {
	.left_direction = DIR_STOP,
	.right_direction = DIR_STOP,
	.left_speed = 0,
	.right_speed = 0
};

void MOTOR_Init(void)
{
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
}

void MOTOR_Control(MotorState *motor)
{

}
