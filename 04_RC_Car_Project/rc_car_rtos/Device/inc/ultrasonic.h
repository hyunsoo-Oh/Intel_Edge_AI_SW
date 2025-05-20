/*
 * ultrasonic.h
 *
 *  Created on: May 19, 2025
 *      Author: USER
 */

#ifndef INC_ULTRASONIC_H_
#define INC_ULTRASONIC_H_

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

#define SENSOR_COUNT	3
#define STABLE_COUNT	3

typedef enum {
	TRIGGER_STATE,
	MEASURE_STATE,
	DONE_STATE
} SensorState_t;

typedef struct {
    GPIO_TypeDef *trig_port;
    uint16_t      trig_pin;
    uint32_t      tim_channel;
    uint32_t	  it_flag;
    SensorState_t status;
    uint8_t		  delay;
} UltraConfig;

typedef struct {
    uint16_t      ic_val1;
    uint16_t      ic_val2;
    uint16_t      echo_us;
    uint16_t	  raw_data;
    uint16_t	  distance_cm;
    uint16_t 	  outlier_distance;
    uint16_t	  outlier_count;
    uint8_t       capture_flag;
} UltraData;

void ULTRASONIC_Init(void);
UltraData ULTRASONIC_GetData(void);

#endif /* INC_ULTRASONIC_H_ */
