/*
 * hw.c
 *
 *  Created on: May 10, 2025
 *      Author: User
 */


#include "hw.h"

uint8_t txData[7] = "S00S00\n";
extern uint8_t rxData[33];
extern uint8_t rxStart;

volatile uint8_t txFlag = 0;
volatile uint8_t rxFlag = 0;
volatile uint8_t btnFlag = 0;

static const uint8_t sk1Data[] = "B80F80\n";
static const uint8_t sk2Data[] = "F80B80\n";
static const uint8_t swaData[] = "A00A00\n";
static const uint8_t swbData[] = "P00P00\n";

void hwInit()
{

}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if (huart->Instance == UART8)
	{
		if (rxStart == '\n')
		{
			HAL_UART_AbortReceive_IT(&huart8);
			rxFlag = 1;
		}
		else
		{
			HAL_UART_Receive_IT(&huart8, &rxStart, 1);
		}
	}
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == UART8)
    	txFlag = 1;                    // 주기 루프 쪽에 알려 줌
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if (htim->Instance == TIM10)
	{
		if (txFlag == 1 && btnFlag == 0)
		{
			txFlag = 0;
			HAL_UART_Transmit_DMA(&huart8, txData, strlen((char*)txData));
		}
		else if (txFlag == 1 && btnFlag == 1)
		{
			txFlag = 0; btnFlag = 0;
			HAL_UART_Transmit_DMA(&huart8, sk1Data, strlen((char*)sk1Data));
		}
		else if (txFlag == 1 && btnFlag == 2)
		{
			txFlag = 0; btnFlag = 0;
			HAL_UART_Transmit_DMA(&huart8, sk2Data, strlen((char*)sk2Data));
		}
		else if (txFlag == 1 && btnFlag == 3)
		{
			txFlag = 0; btnFlag = 0;
			HAL_UART_Transmit_DMA(&huart8, swaData, strlen((char*)swaData));
		}
		else if (txFlag == 1 && btnFlag == 4)
		{
			txFlag = 0;	btnFlag = 0;
			HAL_UART_Transmit_DMA(&huart8, swbData, strlen((char*)swbData));
		}

		if (rxFlag == 1)
		{
			rxFlag = 0;
			HAL_UART_Transmit_DMA(&huart1, rxData, sizeof(rxData));
		}
	}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	switch (GPIO_Pin)
	{
		case BTN_SWA:
			btnFlag = 3;
			break;
		case BTN_SWB:
			btnFlag = 4;
			break;
	}
}
