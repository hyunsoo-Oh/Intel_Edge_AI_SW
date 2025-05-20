/*
 * ap.c
 *
 *  Created on: May 9, 2025
 *      Author: USER
 */

#include "ap.h"

extern uint8_t txData[16];
extern CarState_t mode;
extern MotorState motor;
extern UltraData uData[3];

void apInit()
{
    HAL_UART_Transmit_DMA(&huart1, (uint8_t *)"Start\n", strlen("Start\n"));
    HAL_UART_Transmit_DMA(&huart2, (uint8_t *)"Start\n", strlen("Start\n"));
	ULTRASONIC_Init();
	BLUETOOTH_Init();

	HAL_TIM_Base_Start_IT(&htim11);
	MOTER_DRIVE_Init();
}

void apMain()
{
	while(1)
	{
		BLUETOOTH_Parsing(&motor);

		switch (mode)
		{
			case Active_mode:
				ULTRASONIC_GetData();
				MOTOR_SetMotor(motor);
				break;
			case Passive_mode:
				ULTRASONIC_GetData();
				MOTOR_SetMotor(motor);
				AUTO_Drive();
				break;
		}

		snprintf((char*)txData, sizeof(txData),
				"L:%2d R:%2d C:%2d\n", uData[0].distance_cm, uData[1].distance_cm, uData[2].distance_cm);
	}
}

/*
 * Arduino IDE의 Serial Plotter
 *
 * Data Frame (,) 혹은 ( ) 공백 혹은 (Label:Value) 공백 없이 전송
 * %d,%d,%d\n or %d %d %d or T1:%dT2:%dT3:%d
 */
