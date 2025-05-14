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
uint8_t base_speed;
uint8_t dir_speed;

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
		transData.dirX = GET_Direction(0, adcData[0], centerX);
		transData.dirY = GET_Direction(1, adcData[1], centerY);

		base_speed = GET_Speed(transData.dirX, adcData[0], centerX);
		dir_speed = GET_Speed(transData.dirY, adcData[1], centerY);
		switch (transData.dirX)
		{
			case 'R':
				transData.spdX = base_speed;
				transData.spdY = base_speed - dir_speed;
				break;
			case 'L':
				transData.spdX = base_speed - dir_speed;
				transData.spdY = base_speed;
				break;
			case 'S':
				transData.spdX = 0;
				transData.spdY = 0;
				break;
		}

		sprintf((char*)txData, "%c%02d%c%02d\r\n", transData.dirX, transData.spdX, transData.dirX, transData.spdY);
	}
}
