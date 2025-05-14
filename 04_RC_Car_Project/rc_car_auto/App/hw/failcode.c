/////*
//// * failcode.c
//// *
//// *  Created on: May 14, 2025
//// *      Author: USER
//// */
////
////
/////*
//// * ultrasonic.c
//// *
//// *  Created on: May 13, 2025
//// *      Author: USER
//// */
////
////#include "ultrasonic.h"
////
////UltraSonic sensor[3] = {
////	{ CH2_TRIG_PORT, CH2_TRIG_PIN, TIM_CHANNEL_2, TIM_IT_CC2, 0, 0, 0, 0, 0, IDLE_STATE },
////	{ CH3_TRIG_PORT, CH3_TRIG_PIN, TIM_CHANNEL_3, TIM_IT_CC3, 0, 0, 0, 0, 0, IDLE_STATE },
////	{ CH4_TRIG_PORT, CH4_TRIG_PIN, TIM_CHANNEL_4, TIM_IT_CC4, 0, 0, 0, 0, 0, IDLE_STATE }
////};
////
////void ULTRASONIC_Init()
////{
////	HAL_TIM_Base_Start(&htim5);
////	HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_2);
////	HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_3);
////	HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_4);
////}
////
////static void ULTRASONIC_TRIG_On(UltraSonic *sensor)
////{
////	HAL_GPIO_WritePin(sensor->trig_port, sensor->trig_pin, SET);
////}
////
////static void ULTRASONIC_TRIG_Off(UltraSonic *sensor)
////{
////	HAL_GPIO_WritePin(sensor->trig_port, sensor->trig_pin, RESET);
////}
////
////static void delay_us(uint8_t idx)
////{
////	static uint32_t prev_time = 0xFFFFFFFF;
////	uint32_t curr_time = __HAL_TIM_GET_COUNTER(&htim5);
////
////	if (prev_time == 0xFFFFFFFF)
////	{
////		prev_time = __HAL_TIM_GET_COUNTER(&htim5);
////	}
////
////	if (curr_time - prev_time > 10)
////	{
////		sensor[idx].status = TRIGGER_STATE;
////		prev_time = 0xFFFFFFFF;
////	}
////}
////
////void ULTRASONIC_Read(UltraSonic *sensor)
////{
////	static uint8_t idx = 0;
////	UltraSonic *p = &sensor[idx];
////	static uint32_t prev_time = 0;
////	static uint32_t curr_time = 0;
////
////	switch (p->status)
////	{
////		case IDLE_STATE:
////			ULTRASONIC_TRIG_On(p);
////			delay_us(idx);
////			break;
////		case TRIGGER_STATE:
////			ULTRASONIC_TRIG_Off(p);
////			__HAL_TIM_ENABLE_IT(&htim3, p->it_flag);
////			prev_time = __HAL_TIM_GET_COUNTER(&htim5);
////			p->status = MEASURE_STATE;
////			break;
////		case MEASURE_STATE:
////			curr_time = __HAL_TIM_GET_COUNTER(&htim5);
////			if (curr_time - prev_time > 50000)
////			{
////				p->status = DONE_STATE;
////			}
////			break;
////		case DONE_STATE:
////			p->status = IDLE_STATE;
////			idx = (idx + 1) % 3;
////			break;
////	}
////}
////
////void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
////{
////	static uint8_t idx = 0;
////
////    switch (htim->Channel)
////    {
////        case HAL_TIM_ACTIVE_CHANNEL_2: idx = 0; break;
////        case HAL_TIM_ACTIVE_CHANNEL_3: idx = 1; break;
////        case HAL_TIM_ACTIVE_CHANNEL_4: idx = 2; break;
////        default:                       return;
////    }
////	UltraSonic *p = &sensor[idx];
////
////	if (p->capture_flag == 0)
////	{
////		p->ic_val1 = HAL_TIM_ReadCapturedValue(&htim3, p->tim_channel);
////		p->capture_flag = 1;
////
////		__HAL_TIM_SET_CAPTUREPOLARITY(&htim3, p->tim_channel, TIM_INPUTCHANNELPOLARITY_FALLING);
////	}
////	else if (p->capture_flag == 1)
////	{
////		p->ic_val2 = HAL_TIM_ReadCapturedValue(&htim3, p->tim_channel);
////		__HAL_TIM_SET_COUNTER(&htim3, 0);
////
////		if (p->ic_val2 > p->ic_val1)
////		{
////			p->echo_us = p->ic_val2 - p->ic_val1;
////		}
////		else
////		{
////			p->echo_us = (0xFFFF - p->ic_val1) + p->ic_val2;
////		}
////		p->distance_cm = p->echo_us / 58;
////		p->capture_flag = 0;
////		p->status = DONE_STATE;
////		__HAL_TIM_SET_CAPTUREPOLARITY(&htim3, p->tim_channel, TIM_INPUTCHANNELPOLARITY_RISING);
////
////	    __HAL_TIM_DISABLE_IT(&htim3, p->it_flag);
////	}
////}
//
///*
// * ultrasonic.c
// *
// *  Created on: May 13, 2025
// *      Author: USER
// */
//
//#include "ultrasonic.h"
//
//UltraSonic sensor[3] = {
//	{ L_TRIG_PORT, L_TRIG_PIN, TIM_CHANNEL_2, TIM_IT_CC2, 0, 0, 0, 0, 0, IDLE_STATE },
//	{ R_TRIG_PORT, R_TRIG_PIN, TIM_CHANNEL_3, TIM_IT_CC3, 0, 0, 0, 0, 0, IDLE_STATE },
//	{ C_TRIG_PORT, C_TRIG_PIN, TIM_CHANNEL_4, TIM_IT_CC4, 0, 0, 0, 0, 0, IDLE_STATE }
//};
//
///*──────────────────────────────────────────────────────────────*/
///* 1.  디버그 출력 함수                                         */
///*──────────────────────────────────────────────────────────────*/
//static void Print(uint8_t idx, UltraSonic *p)
//{
//    /* 최대 "CH0 65535 65535\r\n" = 18 byte → 32 byte 버퍼 여유 */
//    char buf[32];
//    int len = sprintf(buf, "CH%u %u %u\r\n", idx, p->status, p->capture_flag);
//    HAL_UART_Transmit(&huart2, (uint8_t*)buf, len, 100);
//}
//
//
//void ULTRASONIC_Init()
//{
//	HAL_TIM_Base_Start(&htim5);
//	HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_2);
//	HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_3);
//	HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_4);
//}
//
//static void ULTRASONIC_TRIG_On(UltraSonic *sensor)
//{
//	HAL_GPIO_WritePin(sensor->trig_port, sensor->trig_pin, SET);
//}
//
//static void ULTRASONIC_TRIG_Off(UltraSonic *sensor)
//{
//	HAL_GPIO_WritePin(sensor->trig_port, sensor->trig_pin, RESET);
//}
//
//static void delay_us(uint8_t idx)
//{
//	static uint32_t prev_time = 0xFFFFFFFF;
//	uint32_t curr_time = __HAL_TIM_GET_COUNTER(&htim5);
//
//	if (prev_time == 0xFFFFFFFF)
//	{
//		prev_time = __HAL_TIM_GET_COUNTER(&htim5);
//	}
//
//	if (curr_time - prev_time > 15)
//	{
//		sensor[idx].status = TRIGGER_STATE;
//		prev_time = 0xFFFFFFFF;
//	}
//}
//
//static void delay_ms(uint8_t *idx)
//{
//	static uint32_t prev_time = 0xFFFFFFFF;
//	uint32_t curr_time = HAL_GetTick();
//
//	if (prev_time == 0xFFFFFFFF)
//	{
//		prev_time = HAL_GetTick();
//	}
//
//	if (curr_time - prev_time > 20)
//	{
//		sensor[*idx].status = IDLE_STATE;
//		*idx = (*idx + 1) % 3;
//		prev_time = 0xFFFFFFFF;
//	}
//}
//
//void ULTRASONIC_Read()
//{
//	static uint8_t idx = 0;
//	static uint32_t prev_time = 0;
//	static uint32_t curr_time = 0;
//
//	UltraSonic *p = &sensor[idx];
//
//	switch (p->status)
//	{
//		case IDLE_STATE:
//			ULTRASONIC_TRIG_On(p);
//			delay_us(idx);
//			Print(idx, p);
//			break;
//		case TRIGGER_STATE:
//			ULTRASONIC_TRIG_Off(p);
//			prev_time = __HAL_TIM_GET_COUNTER(&htim5);
//			__HAL_TIM_ENABLE_IT(&htim3, p->it_flag);
//			p->status = MEASURE_STATE;
//			Print(idx, p);
//			break;
//		case MEASURE_STATE:
//			curr_time = __HAL_TIM_GET_COUNTER(&htim5);
//			if (curr_time - prev_time > 50000)
//			{
//				p->status = DONE_STATE;
//			}
//			Print(idx, p);
//			break;
//		case DONE_STATE:
//			delay_ms(&idx);
//			break;
//	}
//}
//
//void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
//{
//	static uint8_t idx = 0;
//
//    switch (htim->Channel)
//    {
//        case HAL_TIM_ACTIVE_CHANNEL_2: idx = 0; break;
//        case HAL_TIM_ACTIVE_CHANNEL_3: idx = 1; break;
//        case HAL_TIM_ACTIVE_CHANNEL_4: idx = 2; break;
//        default:                       return;
//    }
//	UltraSonic *p = &sensor[idx];
//
//	if (p->capture_flag == 0)
//	{
//		p->ic_val1 = HAL_TIM_ReadCapturedValue(&htim3, p->tim_channel);
//		p->capture_flag = 1;
//
//		__HAL_TIM_SET_CAPTUREPOLARITY(&htim3, p->tim_channel, TIM_INPUTCHANNELPOLARITY_FALLING);
//	}
//	else if (p->capture_flag == 1)
//	{
//		p->ic_val2 = HAL_TIM_ReadCapturedValue(&htim3, p->tim_channel);
//		__HAL_TIM_SET_COUNTER(&htim3, 0);
//
//		if (p->ic_val2 > p->ic_val1)
//		{
//			p->echo_us = p->ic_val2 - p->ic_val1;
//		}
//		else
//		{
//			p->echo_us = (0xFFFF - p->ic_val1) + p->ic_val2;
//		}
//		p->distance_cm = p->echo_us / 58;
//		p->capture_flag = 0;
//		p->status = DONE_STATE;
//		__HAL_TIM_SET_CAPTUREPOLARITY(&htim3, p->tim_channel, TIM_INPUTCHANNELPOLARITY_RISING);
//
//	    __HAL_TIM_DISABLE_IT(&htim3, p->it_flag);
//	}
//}
//
