
#ifndef INC_SERVO_H_
#define INC_SERVO_H_

#include "def.h"
#include "tim.h"

#define Servo_Pin TIM5

typedef enum
{
	CLOSED, OPENED
}DOOR_STATE;

void servoInit();
void OpenDoor();
void CloseDoor();
void ControlDoor();
uint8_t GetStateDoor();

#endif /* INC_SERVO_H_ */
