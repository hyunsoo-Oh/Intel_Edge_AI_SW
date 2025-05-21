/*
 * ultrasonic.c
 *
 *  Created on: May 13, 2025
 *      Author: USER
 */

#include "ultrasonic.h"

static UltraConfig cfg[3] = {
	{ L_TRIG_PORT, L_TRIG_PIN, TIM_CHANNEL_2, TIM_IT_CC2 },
	{ R_TRIG_PORT, R_TRIG_PIN, TIM_CHANNEL_3, TIM_IT_CC3 },
	{ C_TRIG_PORT, C_TRIG_PIN, TIM_CHANNEL_4, TIM_IT_CC4 }
};

UltraData uData[3] = {
	{0, 0, 0, 30, 0},
	{0, 0, 0, 30, 0},
	{0, 0, 0, 30, 0}
};

void ULTRASONIC_Init(void)
{
	HAL_TIM_Base_Start(&htim11);
	for (uint8_t i = 0; i < 3; i++)
	{
			HAL_GPIO_WritePin(cfg[i].trig_port, cfg[i].trig_pin, GPIO_PIN_RESET);
	}
	HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_2);
	HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_3);
	HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_4);
}

void ULTRASONIC_TRIG_On(uint8_t idx)
{
	HAL_GPIO_WritePin(cfg[idx].trig_port, cfg[idx].trig_pin, SET);
}

void ULTRASONIC_TRIG_Off(uint8_t idx)
{
	HAL_GPIO_WritePin(cfg[idx].trig_port, cfg[idx].trig_pin, RESET);
	__HAL_TIM_ENABLE_IT(&htim3, cfg[idx].it_flag);
}

void ULTRASONIC_GetData(uint16_t out_dist[3])
{
	for (uint8_t i = 0; i < 3; i++)
		out_dist[i] = uData[i].distance_cm;
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	static uint8_t idx = 0;

    switch (htim->Channel)
    {
        case HAL_TIM_ACTIVE_CHANNEL_2: idx = 0; break;
        case HAL_TIM_ACTIVE_CHANNEL_3: idx = 1; break;
        case HAL_TIM_ACTIVE_CHANNEL_4: idx = 2; break;
        default:                       return;
    }
    UltraConfig *p 		= &cfg[idx];
    UltraData 	*pData 	= &uData[idx];

	if (pData->capture_flag == 0)
	{
		pData->ic_val1 		= HAL_TIM_ReadCapturedValue(&htim3, p->tim_channel);
		pData->capture_flag = 1;

		__HAL_TIM_SET_CAPTUREPOLARITY(&htim3, p->tim_channel, TIM_INPUTCHANNELPOLARITY_FALLING);
	}
	else if (pData->capture_flag == 1)
	{
		pData->ic_val2 = HAL_TIM_ReadCapturedValue(&htim3, p->tim_channel);
		__HAL_TIM_SET_COUNTER(&htim3, 0);

		__HAL_TIM_SET_CAPTUREPOLARITY(&htim3, p->tim_channel, TIM_INPUTCHANNELPOLARITY_RISING);

		if (pData->ic_val2 > pData->ic_val1)
			pData->echo_us 	= pData->ic_val2 - pData->ic_val1;
		else
			pData->echo_us 	= (0xFFFF - pData->ic_val1) + pData->ic_val2;
		pData->distance_cm 	= pData->echo_us / 58;
		pData->capture_flag = 0;

	    __HAL_TIM_DISABLE_IT(&htim3, p->it_flag);
	}
}
