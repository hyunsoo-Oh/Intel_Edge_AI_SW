/*
 * average_filter.c
 *
 *  Created on: May 15, 2025
 *      Author: USER
 */

#include "average_filter.h"

Data_Handler scaled_data = { 0 };


//// 구조체 초기화
//void UltraData_Init(UltraData *pData) {
//    pData->prev_distance = 0;
//    pData->history_idx = 0;
//    for (int i = 0; i < HISTORY_SIZE; i++) {
//        pData->distance_history[i] = 0;
//    }
//}
//
//// 데이터 업데이트: 이상치 제거 + 이동 평균 필터
//void UltraData_Update(UltraData *pData, uint32_t new_distance) {
//    // 이상치 제거
//    if (pData->prev_distance == 0 || abs(new_distance - pData->prev_distance) < OUTLIER_THRESHOLD) {
//        pData->distance_cm = new_distance;
//        pData->prev_distance = new_distance;
//    } else {
//        pData->distance_cm = pData->prev_distance;  // 이상치 무시
//    }
//
//    // 이동 평균 필터
//    pData->distance_history[pData->history_idx] = pData->distance_cm;
//    pData->history_idx = (pData->history_idx + 1) % HISTORY_SIZE;
//    uint32_t sum = 0;
//    for (int i = 0; i < HISTORY_SIZE; i++) {
//        sum += pData->distance_history[i];
//    }
//    pData->distance_avg = sum / HISTORY_SIZE;
//}
