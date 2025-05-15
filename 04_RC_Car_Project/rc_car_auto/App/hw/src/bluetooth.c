/*
 * bluetooth.c
 *
 *  Created on: May 9, 2025
 *      Author: USER
 */

#include "bluetooth.h"

extern MotorState motor;
extern CarState_t mode;

static int16_t STR_TO_Integer(char *s)
{
	int16_t val = 0;
	while (*s >= '0' && *s <= '9')
	{
		val = val * 10 + (*s - '0');
		s++;
	}
	return val;
}

static void MODE_Change(const uint8_t *rxData)
{
    // A00A00\n 이면 Active_mode
    if (rxData[0] == 'A' && rxData[3] == 'A') {
        mode = Active_mode;
        return;
    }
    // P00P00\n 이면 Passive_mode
    if (rxData[0] == 'P' && rxData[3] == 'P') {
        mode = Passive_mode;
        return;
    }
}

void BLUETOOTH_Parsing(MotorState *motor, const uint8_t *rxData)
{
	MODE_Change(rxData);

	if (mode == Passive_mode) return;

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



