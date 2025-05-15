/*
 * ultrasonic.c
 *
 *  Created on: May 13, 2025
 *      Author: USER
 */

#include "ultrasonic.h"

static UltraConfig cfg[3] = {
	{ L_TRIG_PORT, L_TRIG_PIN, TIM_CHANNEL_2, TIM_IT_CC2, TRIGGER_STATE },
	{ R_TRIG_PORT, R_TRIG_PIN, TIM_CHANNEL_3, TIM_IT_CC3, TRIGGER_STATE },
	{ C_TRIG_PORT, C_TRIG_PIN, TIM_CHANNEL_4, TIM_IT_CC4, TRIGGER_STATE }
};

UltraData uData[3] = {
	{ 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0 }
};

void ULTRASONIC_Init()
{
	HAL_TIM_Base_Start(&htim10);
    for (int i = 0; i < 3; i++)
    {
        HAL_GPIO_WritePin(cfg[i].trig_port, cfg[i].trig_pin, GPIO_PIN_RESET);
    }
	HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_2);
	HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_3);
	HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_4);
}

static void ULTRASONIC_TRIG_On(UltraConfig *cfg)
{
	HAL_GPIO_WritePin(cfg->trig_port, cfg->trig_pin, SET);
}

static void ULTRASONIC_TRIG_Off(UltraConfig *cfg)
{
	HAL_GPIO_WritePin(cfg->trig_port, cfg->trig_pin, RESET);
}

static void delay_us()
{
	__HAL_TIM_SET_COUNTER(&htim10, 0);  // TIM10_CNT = 0
	while((__HAL_TIM_GET_COUNTER(&htim10)) < 10);
}

static void delay_ms(uint8_t *idx)
{
	static uint32_t prev_time = 0xFFFFFFFF;
	uint32_t curr_time = HAL_GetTick();

	if (prev_time == 0xFFFFFFFF)
	{
		prev_time = HAL_GetTick();
	}

	if (curr_time - prev_time > 25)
	{
		cfg[*idx].status = TRIGGER_STATE;
		*idx = (*idx + 1) % 3;
		prev_time = 0xFFFFFFFF;
	}
}

void ULTRASONIC_GetData()
{
	static uint8_t idx = 0;

	UltraConfig *p = &cfg[idx];
//	UltraData *pData = &uData[idx];

	switch (p->status)
	{
		case TRIGGER_STATE:
			ULTRASONIC_TRIG_On(p);
			delay_us();
			ULTRASONIC_TRIG_Off(p);
			__HAL_TIM_ENABLE_IT(&htim3, p->it_flag);
			p->status = MEASURE_STATE;
			break;

		case MEASURE_STATE:

			break;

		case DONE_STATE:
			delay_ms(&idx);
			break;
	}
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
			pData->echo_us = pData->ic_val2 - pData->ic_val1;
		else
			pData->echo_us = (0xFFFF - pData->ic_val1) + pData->ic_val2;
		pData->distance_cm = pData->echo_us / 58;
		pData->capture_flag = 0;
		p->status = DONE_STATE;

	    __HAL_TIM_DISABLE_IT(&htim3, p->it_flag);
	}
}
