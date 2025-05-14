/*
 * ap.c
 *
 *  Created on: May 10, 2025
 *      Author: User
 */

#include "ap.h"

uint16_t test;
uint8_t rxData[8];
uint16_t centerX = 2692;
uint16_t centerY = 2024;
volatile uint16_t adcData[2];

extern TransData transData;
extern uint8_t txData[9];

void apInit()
{
	HAL_UART_Transmit_DMA(&huart8, txData, strlen((char*)txData));
	HAL_UART_Receive_DMA(&huart8, rxData, sizeof(rxData));
	HAL_ADC_Start_DMA(&hadc1, adcData, 2);
	HAL_TIM_Base_Start_IT(&htim10);
}

void apMain()
{
	while (1)
	{
		transData.dirX = GET_Direction(adcData[0], centerX);
		transData.dirY = GET_Direction(adcData[1], centerY);

		transData.spdX = GET_Speed(transData.dirX, adcData[0], centerX);
		transData.spdY = GET_Speed(transData.dirY, adcData[1], centerY);

		sprintf((char*)txData, "%c%02d%c%02d\r\n", transData.dirX, transData.spdX, transData.dirY, transData.spdY);
	}
}
