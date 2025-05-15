/*
 * hw.c
 *
 *  Created on: May 9, 2025
 *      Author: USER
 */

#include "hw.h"

extern volatile uint8_t txFlag;

void hwInit()
{

}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if (htim->Instance == TIM11)
	{
		txFlag = 1;
	}
}
