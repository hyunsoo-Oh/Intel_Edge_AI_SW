/*
 * ap.c
 *
 *  Created on: May 9, 2025
 *      Author: USER
 */

#include "ap.h"

uint8_t pc_rxData[7];
uint8_t bt_rxData[7];
uint8_t txData[32];

volatile uint8_t txFlag = 0;
extern MotorState motor;
extern UltraData uData[3];

void apInit()
{
	ADXL345_Init();
	ULTRASONIC_Init();
	HAL_TIM_Base_Start_IT(&htim11);
	HAL_UART_Receive_DMA(&huart1, bt_rxData, 7);
	HAL_UART_Receive_DMA(&huart2, pc_rxData, 7);
	MOTER_DRIVE_Init();
}

void apMain()
{
	while(1)
	{
		ULTRASONIC_GetData();
		BLUETOOTH_Parsing(&motor, bt_rxData);
		MOTOR_SetMotor(motor);

		uint8_t len = snprintf((char*)txData, sizeof(txData),
				"%u,%u,%u\r\n", uData[0].distance_cm, uData[1].distance_cm, uData[2].distance_cm);
		if (txFlag == 1)
		{
			txFlag = 0;
			HAL_UART_Transmit_DMA(&huart2, txData, len);
		}
	}
}

/*
 * Arduino IDE의 Serial Plotter
 *
 * Data Frame (,) 혹은 ( ) 공백 혹은 (Label:Value) 공백 없이 전송
 * %d,%d,%d\n or %d %d %d or T1:%dT2:%dT3:%d
 */
