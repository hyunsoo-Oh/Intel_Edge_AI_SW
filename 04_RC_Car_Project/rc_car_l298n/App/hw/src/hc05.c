/*
 * hm10.c
 *
 *  Created on: May 9, 2025
 *      Author: USER
 */

#include "hc05.h"

extern MotorState motor;

void BLUETOOTH_Parsing(MotorState *motor, const uint8_t *rxData)
{
	char left_buff[3] = { rxData[1], rxData[2], '\0' };
	char right_buff[3] = { rxData[4], rxData[5], '\0' };

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
