/*
 * ap.c
 *
 *  Created on: May 9, 2025
 *      Author: USER
 */

#include "ap.h"

void apInit()
{
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, SET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, RESET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, SET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12, RESET);
}

void apMain()
{
	TIM1->CCR1 = 500;
	TIM1->CCR2 = 500;
	while(1)
	{

	}
}
