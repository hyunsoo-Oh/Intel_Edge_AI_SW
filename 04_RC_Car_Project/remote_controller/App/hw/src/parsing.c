/*
 * bluetooth.c
 *
 *  Created on: May 12, 2025
 *      Author: USER
 */

#include "parsing.h"

ControlData data = {
	.dirF = 'S',
	.dirS = 'S',
	.spdL = 0,
	.spdR = 0
};

uint8_t map(uint16_t value, uint16_t rawMin, uint16_t rawMax, uint8_t scaled_min, uint8_t scaled_max)
{
	int32_t hnum = (int32_t)(value - rawMin) * (scaled_max - scaled_min);
	int32_t lnum = (int32_t)(rawMax - rawMin);
	uint32_t result = hnum / lnum + scaled_min;

	if (scaled_min < scaled_max) {
		if (result > scaled_max) result = scaled_max;
		if (result < scaled_min) result = scaled_min;
	} else {
		if (result > scaled_min) result = scaled_min;
		if (result < scaled_max) result = scaled_max;
	}

	return (uint8_t)	result;
}

uint8_t GET_Direction(uint8_t idx, uint16_t adcValue, uint16_t center)
{
    if (adcValue >= center + DEAD_SPACE)		return idx == y ? 'F' : 'R';
    else if (adcValue <= center - DEAD_SPACE)	return idx == y ? 'B' : 'L';
    else										return 'S';
}

uint8_t GET_Speed(uint8_t dir, uint16_t adcValue, uint16_t center)
{
    switch (dir)
    {
    	case 'F':
    		return map(adcValue, center + DEAD_SPACE, 4095, 50, 99);
    	case 'B':
    		return map(adcValue, 0, center - DEAD_SPACE, 99, 50);
    	case 'R':
    		return map(adcValue, center + DEAD_SPACE, 4095, 10, 50);
    	case 'L':
    		return map(adcValue, 0, center - DEAD_SPACE, 50, 10);
    	case 'S':
    		return 0;
    	default:
    		return 0;
    }
}

ControlData CONTROL_Data(uint16_t *adcData, uint16_t centerF, uint16_t centerS)
{
	ControlData data = {0};

	uint8_t base_speed = 0;
	uint8_t dir_speed  = 0;

	data.dirF = GET_Direction(0, adcData[0], centerF);
	data.dirS = GET_Direction(1, adcData[1], centerS);

	base_speed = GET_Speed(data.dirF, adcData[0], centerF);
	dir_speed = GET_Speed(data.dirS, adcData[1], centerS);

	if (data.dirF == 'S')	base_speed = 0;
	if (data.dirS == 'S')	dir_speed = 0;


	switch (data.dirS)
	{
		case 'R':
			data.spdL = (base_speed > dir_speed) ? (base_speed - dir_speed) : 0;
			data.spdR = base_speed;
			break;
		case 'L':
			data.spdL = base_speed;
			data.spdR = (base_speed > dir_speed) ? (base_speed - dir_speed) : 0;
			break;
		case 'S':
			data.spdL = base_speed;
			data.spdR = base_speed;
			break;
	}
	return data;
}
