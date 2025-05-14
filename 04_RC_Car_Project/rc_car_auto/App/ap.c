/*
 * ap.c
 *
 *  Created on: May 9, 2025
 *      Author: USER
 */

#include "ap.h"

uint8_t pc_rxData[8];
uint8_t bt_rxData[8];
uint8_t txData[8];

volatile uint8_t txFlag = 0;
extern MotorState motor;

void apInit()
{
	ADXL345_Init();
	ULTRASONIC_Init();
	HAL_UART_Receive_DMA(&huart1, bt_rxData, 8);
//	HAL_UART_Receive_DMA(&huart2, pc_rxData, 8);
	MOTER_DRIVE_Init();
}

void apMain()
{
	while(1)
	{
		ULTRASONIC_Read();
		BLUETOOTH_Parsing(&motor, bt_rxData);
		MOTOR_SetMotor(motor);
	}
}

