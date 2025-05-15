/*
 * average_filter.h
 *
 *  Created on: May 15, 2025
 *      Author: USER
 */

#ifndef UTIL_INC_AVERAGE_FILTER_H_
#define UTIL_INC_AVERAGE_FILTER_H_

/*
 * 	Moving Average Filter 	: 최근 N개의 측정값을 평균 내어 노이즈를 줄이는 간단하고 효과적인 방법
 * 	Outlier Rejection		: 비정상적으로 큰 변화가 있는 측정값을 필터링
 * 	Kalman Filter			: 센서 노이즈와 시스템 모델을 기반으로 최적의 값을 추정
 *
 * 	Outlier Rejection + Moving Average Filter
 */
#include "stm32f4xx_hal.h"
#include "def.h"

#define HISTORY_SIZE 		5
#define OUTLIER_THRESHOLD 	50

typedef struct {
	uint16_t	up_limit;
	uint16_t	lo_limit;

};

typedef struct {
	uint16_t 	buf[16];
	uint16_t 	sum;
    uint8_t 	max_len;
    uint8_t 	idx;
    uint8_t 	count;
} MAF_Handler;

void FILTER_Init(MAF_Handler* h, uint8_t window_size);
uint16_t FILTER_Update(MAF_Handler* h, uint16_t new_sample);

#endif /* UTIL_INC_AVERAGE_FILTER_H_ */
