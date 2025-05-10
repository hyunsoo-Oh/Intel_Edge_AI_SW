/*
 * ap.c
 *
 *  Created on: May 9, 2025
 *      Author: USER
 */

#include "ap.h"

uint8_t pc_rxData[5];
uint8_t bt_rxData[6];
uint8_t remoteData[6];
uint8_t prv_rxData[5];
uint8_t buff;

extern MotorState motor;

void apInit()
{
	HAL_UART_Receive_DMA(&huart1, bt_rxData, 6);
	HAL_UART_Receive_DMA(&huart2, pc_rxData, 5);
	MOTER_DRIVE_Init();
}

void apMain()
{
	while(1)
	{
		motor.left_direction  = (MotorDir)(pc_rxData[0]);
		motor.right_direction = (MotorDir)(pc_rxData[1]);
		motor.left_speed      = atoi(&pc_rxData[2]) * 100;
		motor.right_speed     = atoi(pc_rxData[3] + '\n') * 100;
		MOTOR_SetMotor(motor);
		if (memcmp(pc_rxData, prv_rxData, 5) != 0)
		{
			sprintf(remoteData, "%s\r\n", pc_rxData);
			HAL_UART_Transmit(&huart1, remoteData, sizeof(remoteData), 100);
			HAL_UART_Transmit(&huart2, remoteData, sizeof(remoteData), 100);
			memcpy(prv_rxData, pc_rxData, 5);
		}
	}
}
