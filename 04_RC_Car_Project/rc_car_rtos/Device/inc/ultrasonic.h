/*
 * ultrasonic.h
 *
 *  Created on: May 13, 2025
 *      Author: USER
 */

#ifndef HW_INC_ULTRASONIC_H_
#define HW_INC_ULTRASONIC_H_

#include "def.h"
#include "usart.h"
#include "gpio.h"
#include "tim.h"
#include "delay.h"

#define L_TRIG_PORT		GPIOB
#define L_TRIG_PIN		GPIO_PIN_2

#define R_TRIG_PORT		GPIOC
#define R_TRIG_PIN		GPIO_PIN_1

#define C_TRIG_PORT		GPIOB
#define C_TRIG_PIN		GPIO_PIN_15

#define SENSOR_COUNT		3
#define STABLE_COUNT		3
#define OUTLIER_THRESHOLD	60

typedef struct {
    GPIO_TypeDef *trig_port;
    uint16_t      trig_pin;
    uint32_t    	tim_channel;
    uint32_t	    it_flag;
} UltraConfig;

typedef struct {
    uint16_t      ic_val1;
    uint16_t      ic_val2;
    uint16_t      echo_us;
    uint16_t			distance_cm;
    uint8_t       capture_flag;
} UltraData;

void ULTRASONIC_Init(void);
void ULTRASONIC_TRIG_On(uint8_t idx);
void ULTRASONIC_TRIG_Off(uint8_t idx);
void ULTRASONIC_GetData(uint16_t out_dist[3]);

#endif /* HW_INC_ULTRASONIC_H_ */

