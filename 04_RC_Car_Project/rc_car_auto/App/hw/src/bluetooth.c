/*
 * hm10.c
 *
 *  Created on: May 9, 2025
 *      Author: USER
 */

#include "bluetooth.h"

extern MotorState motor;

void BLUETOOTH_Parsing(MotorState *motor, const uint8_t *rxData)
{
	if ((rxData[0] != 'F' && rxData[0] != 'B' && rxData[0] != 'S') ||
		(rxData[3] != 'F' && rxData[3] != 'B' && rxData[3] != 'S') ||
		rxData[6] != '\n')
	{
		memset(rxData, 0, 7);
		memcpy(rxData, "S00S00\n", 7);
	}

	char left_buff[2] = { rxData[1], rxData[2] };
	char right_buff[2] = { rxData[4], rxData[5] };

	motor->left_direction  = (MotorDir)(rxData[0]);
	motor->right_direction = (MotorDir)(rxData[3]);
	motor->left_speed      = STR_TO_Integer(left_buff);
	motor->right_speed     = STR_TO_Integer(right_buff);
}

int16_t STR_TO_Integer(char *s)
{
	int16_t val = 0;
	while (*s >= '0' && *s <= '9')
	{
		val = val * 10 + (*s - '0');
		s++;
	}
	return val;
}



