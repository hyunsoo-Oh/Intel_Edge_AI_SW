/*
 * motor.h
 *
 *  Created on: May 19, 2025
 *      Author: USER
 */

#ifndef INC_MOTOR_H_
#define INC_MOTOR_H_

#include "gpio.h"
#include "tim.h"

#define IN0_PORT			GPIOC
#define IN1_PORT			GPIOC
#define IN2_PORT			GPIOC
#define IN3_PORT			GPIOC
#define IN0_PIN				GPIO_PIN_6		// Left
#define IN1_PIN				GPIO_PIN_8
#define IN2_PIN				GPIO_PIN_10		// Right
#define IN3_PIN				GPIO_PIN_12

#define MODE_SWITCH			'Z'

typedef enum {
	DIR_FORWARD		= 'F',
	DIR_BACKWARD 	= 'B',
	DIR_RIGHT		= 'R',
	DIR_LEFT		= 'L'
} MotorDir_t;

typedef enum {
	PASSIVE_MODE,
	ACTIVE_MODE
} ModeState_t;

typedef struct {
	MotorDir_t 	left_direction;
	MotorDir_t 	right_direction;
	uint8_t		left_speed;
	uint8_t		right_speed;
} MotorState;

void MOTOR_Init(void);
void MOTOR_Control(MotorState *motor);

#endif /* INC_MOTOR_H_ */
