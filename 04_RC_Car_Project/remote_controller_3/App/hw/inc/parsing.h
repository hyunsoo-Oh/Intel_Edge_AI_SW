/*
 * bluetooth.h
 *
 *  Created on: May 12, 2025
 *      Author: USER
 */

#ifndef HW_INC_PARSING_H_
#define HW_INC_PARSING_H_

#include "def.h"

#define ADC_CENTER		2047
#define DEAD_SPACE		400

typedef enum {
	y, x
} DirType_t;

typedef struct {
	uint8_t dirX;
	uint8_t dirY;
	uint8_t spdX;
	uint8_t spdY;
} TransData;

uint8_t map(uint16_t value, uint16_t rawMin, uint16_t rawMax, uint8_t scaled_min, uint8_t scaled_max);
uint8_t GET_Direction(uint8_t idx, uint16_t adcValue, uint16_t center);
uint8_t GET_Speed(uint8_t dir, uint16_t adcValue, uint16_t center);

#endif /* HW_INC_PARSING_H_ */
