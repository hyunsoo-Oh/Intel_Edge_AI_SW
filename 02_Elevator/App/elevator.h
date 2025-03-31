/*
 * elevator.h
 *
 *  Created on: Mar 31, 2025
 *      Author: User
 */

#ifndef ELEVATOR_H_
#define ELEVATOR_H_

#include "hw.h"

#define		RequestTime			  200
#define		ResponseTime		  5000

typedef enum {
	STATE_IDLE,
	STATE_START,
	STATE_MOVING_UP,
	STATE_MOVING_DOWN,
	STATE_ARRIVED
} ElevatorState;

typedef struct {
	uint8_t 					rfid_Auth : 1;
	ElevatorState			elevatorState : 3;
	uint8_t 					currentFloor;
	uint8_t 					targetFloor;
} ElevatorState_t;

uint8_t CheckRFID();
void LED_Switch();
uint8_t CheckDIR();

#endif /* ELEVATOR_H_ */
