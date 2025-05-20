/*
 * delay.c
 *
 *  Created on: May 19, 2025
 *      Author: USER
 */

#include "delay.h"

void delay_us(uint16_t us)
{
	__HAL_TIM_SET_COUNTER(&htim11, 0);  // TIM11_CNT = 0
	while((__HAL_TIM_GET_COUNTER(&htim11)) < us);
}

void delay_ms(uint16_t ms, uint8_t *flag)
{
	static uint32_t prev_time = 0xFFFFFFFF;
	uint16_t curr_time = HAL_GetTick();

	if (prev_time == 0xFFFFFFFF)
	{
		prev_time = HAL_GetTick();
	}

	if (curr_time - prev_time > ms)
	{
		flag = 1;
		prev_time = 0xFFFFFFFF;
	}
}
