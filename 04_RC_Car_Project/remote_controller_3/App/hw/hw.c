/*
 * hw.c
 *
 *  Created on: May 10, 2025
 *      Author: User
 */


#include "hw.h"

uint8_t txData[9] = "S00S00\r\n";
volatile uint8_t txFlag = 0;

void hwInit()
{

}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *hu)
{
    if (hu->Instance == UART8)
    	txFlag = 1;                    // 주기 루프 쪽에 알려 줌
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if (htim->Instance == TIM10)
	{
		if (txFlag == 1)
		{
			txFlag = 0;
			HAL_UART_Transmit_DMA(&huart8, txData, strlen((char*)txData));
		}

//		if (HAL_UART_GetState(&huart1) == HAL_UART_STATE_READY)
//			HAL_UART_Transmit_DMA(&huart1, txData, strlen((char*)txData));
		HAL_GPIO_TogglePin(GPIOG, GPIO_PIN_13);
	}
}
