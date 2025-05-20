/*
 * ap.c
 *
 *  Created on: May 10, 2025
 *      Author: User
 */

#include "ap.h"

uint8_t rxData[33];
uint16_t centerF = 2900;
uint16_t centerS = 1980;
volatile uint16_t adcData[2];
uint8_t rxStart;

extern volatile uint8_t btnFlag;
extern volatile uint8_t rxFlag;
extern ControlData data;
extern uint8_t txData[7];

void apInit()
{
	HAL_UART_Transmit_DMA(&huart8, txData, strlen((char*)txData));
	HAL_UART_Receive_IT(&huart8, &rxStart, 1);
	HAL_ADC_Start_DMA(&hadc1, adcData, 2);
	HAL_TIM_Base_Start_IT(&htim10);
}

void apMain()
{
	while (1)
	{
		if (rxFlag == 1)
		{
			rxFlag == 0;
			HAL_UART_Receive_DMA(&huart8, rxData, sizeof(rxData));
		}

		data = CONTROL_Data(adcData, centerF, centerS);

		if (HAL_GPIO_ReadPin(GPIOA, BTN_SK1) == RESET)
		{
			BTN_Control(GPIOA, BTN_SK1, 1);
		}
		if (HAL_GPIO_ReadPin(GPIOC, BTN_SK2) == RESET)
		{
			BTN_Control(GPIOC, BTN_SK2, 2);
		}

		sprintf((char*)txData, "%c%02d%c%02d\n", data.dirF, data.spdL, data.dirF, data.spdR);
	}
}

void BTN_Control(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, uint8_t f)
{
	static uint32_t prev_time = 0xFFFFFFFF;
	uint32_t curr_time = HAL_GetTick();

	if (prev_time == 0xFFFFFFFF)
	{
		prev_time = HAL_GetTick();
	}

	if (curr_time - prev_time > 20)
	{
		if (HAL_GPIO_ReadPin(GPIOx, GPIO_Pin) == RESET)
		{
			btnFlag = f;
			prev_time == 0xFFFFFFFF;
		}
	}
}
