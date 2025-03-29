
#include "servo.h"

static volatile uint8_t state = 0;
static volatile uint16_t lastAngle = 0;

void servoInit()
{
	HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_1);
}

bool angleCheck()
{
	if(lastAngle == 127 || lastAngle == 80) return true;
	return false;
}

void OpenDoor()
{
	uint16_t angle = angleCheck() ? 80 : lastAngle ;

	for(; angle<=127; angle++)
	{
		Servo_Pin->CCR1 = angle;
		lastAngle = angle;
		HAL_Delay(50);
	}
	state = 1;
}

void CloseDoor()
{
	uint16_t angle = angleCheck() ? 127 : lastAngle ;

	for(; angle>=80; angle--)
	{
		Servo_Pin->CCR1 = angle;
		lastAngle = angle;
		HAL_Delay(50);
	}
	state = 0;
}

void ControlDoor()
{
	OpenDoor();
	HAL_Delay(2000);
	CloseDoor();
}

uint8_t GetStateDoor()
{
	return state;
}
