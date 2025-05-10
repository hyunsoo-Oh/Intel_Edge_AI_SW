/*
 * l298n.c
 *
 *  Created on: May 9, 2025
 *      Author: USER
 */

#include "l298n.h"

MotorState motor = {
	.left_direction = DIR_STOP,
	.right_direction = DIR_STOP,
	.left_speed = 0,
	.right_speed = 0
};

void MOTER_DRIVE_Init()
{
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
}

static void MOTOR_AControl(MotorDir motor)
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
		case DIR_STOP:
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, SET);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, SET);
			break;
	}
}

static void MOTOR_BControl(MotorDir motor)
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
		case DIR_STOP:
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, SET);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12, SET);
			break;
	}
}

void IN_DRIVE_Break()
{
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, SET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, SET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, SET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12, SET);
}

static void MOTOR_SetDrive(uint8_t l_dir, uint8_t r_dir)
{
	switch (DRIVE_KEY(l_dir, r_dir))
	{
		case DRIVE_KEY(DIR_FORWARD, DIR_FORWARD):
			MOTOR_AControl(DIR_FORWARD);
			MOTOR_BControl(DIR_FORWARD);
			break;
		case DRIVE_KEY(DIR_BACKWARD, DIR_BACKWARD):
			MOTOR_AControl(DIR_BACKWARD);
			MOTOR_BControl(DIR_BACKWARD);
			break;
		case DRIVE_KEY(DIR_FORWARD, DIR_BACKWARD):
			MOTOR_AControl(DIR_FORWARD);
			MOTOR_BControl(DIR_BACKWARD);
			break;
		case DRIVE_KEY(DIR_BACKWARD, DIR_FORWARD):
			MOTOR_AControl(DIR_BACKWARD);
			MOTOR_BControl(DIR_FORWARD);
			break;
		default:
			IN_DRIVE_Break();
			break;
	}
}

static void MOTOR_Speed(uint16_t l_speed, uint16_t r_speed)
{
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, l_speed);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, r_speed);
}

void MOTOR_Rotate(uint8_t dir)
{
	switch (dir)
	{
		case ROTATE_LEFT:
			MOTOR_SetDrive(DIR_FORWARD, DIR_BACKWARD);
			MOTOR_Speed(700, 700);
			break;
		case ROTATE_RIGHT:
			MOTOR_SetDrive(DIR_BACKWARD, DIR_FORWARD);
			MOTOR_Speed(700, 700);
			break;
	}
}

void MOTOR_SetMotor(MotorState motor)
{
	MOTOR_SetDrive(motor.left_direction, motor.right_direction);
	MOTOR_Speed(motor.left_speed, motor.right_speed);
}
