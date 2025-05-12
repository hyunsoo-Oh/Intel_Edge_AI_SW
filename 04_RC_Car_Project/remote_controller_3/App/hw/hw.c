/*
 * hw.c
 *
 *  Created on: May 10, 2025
 *      Author: User
 */


#include "hw.h"

uint8_t txData[8] = "S00S00\r\n";

void hwInit()
{

}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if (htim->Instance == TIM10)
	{
		if (HAL_UART_GetState(&huart8) == HAL_UART_STATE_READY)
			HAL_UART_Transmit_DMA(&huart8, txData, strlen((char*)txData));

//		if (HAL_UART_GetState(&huart1) == HAL_UART_STATE_READY)
//			HAL_UART_Transmit_DMA(&huart1, txData, strlen((char*)txData));
	}
}
