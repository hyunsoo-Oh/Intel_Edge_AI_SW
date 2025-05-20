/*
 * motor.h
 *
 *  Created on: May 9, 2025
 *      Author: USER
 */

#ifndef HW_INC_MOTOR_H_
#define HW_INC_MOTOR_H_

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

#define DRIVE_SPEED(s, hz)	((s) * (hz) / 100)

typedef enum {
	DIR_STOP     = 'S',
	DIR_FORWARD  = 'F',
    DIR_BACKWARD = 'B',
	DIR_RIGHT	 = 'R',
	DIR_LEFT	 = 'L'
} MotorDir_t;

typedef enum {
	ROTATE_LEFT,
	ROTATE_RIGHT
} RotateDir_t;

typedef struct {
	MotorDir_t 	front_direction;
	MotorDir_t 	side_direction;
	uint8_t		base_speed;
	uint8_t		dir_speed;
} MotorState;

void MOTER_DRIVE_Init();

void MOTOR_Rotate(uint8_t dir);
void MOTOR_SetMotor(MotorState motor);

#endif /* HW_INC_MOTOR_H_ */
