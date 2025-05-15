/*
 * ap.c
 *
 *  Created on: May 10, 2025
 *      Author: User
 */

#include "ap.h"

uint16_t test;
uint8_t rxData[8];
uint16_t centerF = 2900;
uint16_t centerS = 1980;
volatile uint16_t adcData[2];
uint8_t base_speed;
uint8_t dir_speed;

extern ControlData data;
extern uint8_t txData[7];

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
		data = CONTROL_Data(adcData, centerF, centerS);

		sprintf((char*)txData, "%c%02d%c%02d\n", data.dirF, data.spdL, data.dirF, data.spdR);
	}
}
