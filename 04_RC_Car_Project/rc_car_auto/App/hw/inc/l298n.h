/*
 * l298n.h
 *
 *  Created on: May 9, 2025
 *      Author: USER
 */

#ifndef HW_INC_L298N_H_
#define HW_INC_L298N_H_

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

#define DRIVE_KEY(l,r)   	((l << 2) | (r))
#define DRIVE_SPEED(s, hz)	((s) * (hz) / 100)

typedef enum {
	DIR_STOP = 'S',
	DIR_FORWARD = 'F',
    DIR_BACKWARD = 'B'
} MotorDir;

typedef enum {
	ROTATE_LEFT = 0,
	ROTATE_RIGHT
} RotateDir;

typedef struct {
	MotorDir 	left_direction;
	MotorDir 	right_direction;
	uint8_t		left_speed;
	uint8_t		right_speed;
} MotorState;

void MOTER_DRIVE_Init();

void MOTOR_Rotate(uint8_t dir);
void MOTOR_SetMotor(MotorState motor);

#endif /* HW_INC_L298N_H_ */
