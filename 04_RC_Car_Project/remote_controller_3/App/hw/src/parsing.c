/*
 * bluetooth.c
 *
 *  Created on: May 12, 2025
 *      Author: USER
 */

#include "parsing.h"

TransData transData = {
	.dirX = 'S',
	.dirY = 'S',
	.spdX = 0,
	.spdY = 0
};

uint8_t map(uint16_t value, uint16_t rawMin, uint16_t rawMax, uint8_t scaled_min, uint8_t scaled_max)
{
	int32_t hnum = (int32_t)(value - rawMin) * (scaled_max - scaled_min);
	int32_t lnum = (int32_t)(rawMax - rawMin);
	uint32_t result = hnum / lnum + scaled_min;
	if (result > 99)		result = 99;
	else if (result < 40)	result = 40;

	return (uint8_t)	result;
}

uint8_t GET_Direction(uint16_t adcValue, uint16_t center)
{
    if (adcValue >= center + DEAD_SPACE)		return 'F';
    else if (adcValue <= center - DEAD_SPACE)	return 'B';
    else										return 'S';
}

uint8_t GET_Speed(uint8_t dir, uint16_t adcValue, uint16_t center)
{
    switch (dir)
    {
    	case 'F':
    		return map(adcValue, center + DEAD_SPACE, 4095, 40, 99);
    	case 'B':
    		return map(adcValue, 0, center - DEAD_SPACE, 99, 40);
    	case 'S':
    		return 0;
    	default:
    		return 0;
    }
}
