/*
 * hw.c
 *
 *  Created on: May 9, 2025
 *      Author: USER
 */

#include "hw.h"

volatile uint8_t txFlag = 0;

extern uint8_t txData[32];

void hwInit()
{

}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART2)
    {
        txFlag = 1;
    }
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if (htim->Instance == TIM11)
	{
		if (txFlag == 1)
		{
			txFlag = 0;
			HAL_UART_Transmit_DMA(&huart2, txData, strlen((char*)txData));
		}
	}
}
