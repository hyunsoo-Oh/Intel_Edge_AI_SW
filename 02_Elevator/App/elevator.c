/*
 * elevator.c
 *
 *  Created on: Mar 31, 2025
 *      Author: User
 */

#include "elevator.h"

static uint8_t status;
static uint8_t str[16];
static uint8_t sNum[5];

static uint32_t ckTime = 200;
volatile uint8_t ret = 0;

uint8_t CheckRFID()
{
	static uint32_t prevTime = 0xFFFFFFFF;

	if (prevTime == 0xFFFFFFFF)
		prevTime = HAL_GetTick();
	uint32_t curTime = HAL_GetTick();

	if (curTime - prevTime > ckTime)
	{
		status = MFRC522_Request(PICC_REQIDL, str);
		status = MFRC522_Anticoll(str);
		memcpy(sNum, str, 5);
		if((sNum[0]==195) && (sNum[1]==159) && (sNum[2]==70) && (sNum[3]==150) && (sNum[4]==140) )
		{
			ret = true;
			ckTime = ResponseTime;
//			printf("%s \r\n", MSG1);
			prevTime = HAL_GetTick();
		}
		else if((sNum[0]==18) && (sNum[1]==35) && (sNum[2]==141) && (sNum[3]==83) && (sNum[4]==239) )
		{
			ret = true;
			ckTime = ResponseTime;
//			printf("%s \r\n", MSG2);
			prevTime = HAL_GetTick();
		}
		else
		{
			ret = false;
			ckTime = RequestTime;
//			printf("%s \r\n", MSG3);
			prevTime = HAL_GetTick();
		}
	}
	return ret;
}

void LED_Switch()
{
	if(GetStateStep())
	{
		LED_G_OFF();
		LED_R_ON();
	}
	else
	{
		LED_R_OFF();
		LED_G_ON();
	}
}

uint8_t CheckDIR(ElevatorState_t elevator)
{
	uint8_t ret = STATE_START;

	int8_t dir = elevator.targetFloor - elevator.currentFloor;

	if (dir > 0)
		ret = STATE_MOVING_UP;
	if (dir < 0)
		ret = STATE_MOVING_DOWN;
	if (dir == 0)
		ret = STATE_ARRIVED;

	return ret;
}









