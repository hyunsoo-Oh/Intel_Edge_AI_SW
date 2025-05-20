/*
 * l298n.c
 *
 *  Created on: May 9, 2025
 *      Author: USER
 */

#include "motor.h"

MotorState motor = {
	.front_direction = DIR_STOP,
	.side_direction  = DIR_STOP,
	.base_speed 	 = 0,
	.dir_speed 	 	 = 0
};

void MOTER_DRIVE_Init(void)
{
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
}

static void MOTOR_AControl(MotorDir_t motor)
{
	switch (motor)
	{
		case DIR_FORWARD:
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, SET);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, RESET);
			break;
		case DIR_BACKWARD:
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, RESET);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, SET);
			break;
		default:
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, SET);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, SET);
			break;
	}
}

static void MOTOR_BControl(MotorDir_t motor)
{
	switch (motor)
	{
		case DIR_FORWARD:
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, SET);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12, RESET);
			break;
		case DIR_BACKWARD:
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, RESET);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12, SET);
			break;
		default:
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, SET);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12, SET);
			break;
	}
}

static void IN_DRIVE_Break(void)
{
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, SET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, SET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, SET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12, SET);
}

static void MOTOR_SetDrive(uint8_t front, uint8_t side)
{
	switch (front)
	{
		case DIR_FORWARD:
			MOTOR_AControl(DIR_FORWARD);
			MOTOR_BControl(DIR_FORWARD);
			break;
		case DIR_BACKWARD:
			MOTOR_AControl(DIR_BACKWARD);
			MOTOR_BControl(DIR_BACKWARD);
			break;
		default:
			IN_DRIVE_Break();
			break;
	}
}

static void MOTOR_Speed(uint16_t spdA, uint16_t spdB)
{
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, DRIVE_SPEED(spdA, 20000));
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, DRIVE_SPEED(spdB, 20000));
}

void MOTOR_Rotate(uint8_t dir)
{
	switch (dir)
	{
		case ROTATE_LEFT:
			MOTOR_AControl(DIR_FORWARD);
			MOTOR_BControl(DIR_BACKWARD);
			MOTOR_Speed(80, 80);
			break;
		case ROTATE_RIGHT:
			MOTOR_AControl(DIR_BACKWARD);
			MOTOR_BControl(DIR_FORWARD);
			MOTOR_Speed(80, 80);
			break;
	}
}

void MOTOR_SetMotor(MotorState motor)
{
	uint16_t base  = motor.base_speed;  // 앞뒤 이동 속도
	uint16_t dir   = motor.dir_speed;   // 좌우 보조 속도
	int16_t  spdA  = base;
	int16_t  spdB  = base;

	switch (motor.side_direction)
	{
		case DIR_LEFT:
			spdA = base - dir;
			spdB = base + dir;
			break;
		case DIR_RIGHT:
			spdA = base + dir;
			spdB = base - dir;
			break;
		default:
			spdA = base;
			spdB = base;
			break;
	}

	if (spdA < 0)    spdA = 0;
	if (spdA >= 100) spdA = 99;
	if (spdB < 0)    spdB = 0;
	if (spdB >= 100) spdB = 99;

	MOTOR_SetDrive(motor.front_direction, motor.side_direction);
	MOTOR_Speed(spdA, spdB);
}
