
#include "ap.h"

ElevatorState_t elevator;

static uint8_t btn;

void apInit()
{
	hwInit();
	lcd_command(CLEAR_DISPLAY);
	HAL_Delay(2);
}

void apMain()
{
	while (1)
	{
		switch (elevator.elevatorState)
		{
			case STATE_IDLE:
				LED_B_ON();
				elevator.rfid_Auth = CheckRFID();
				elevator.elevatorState = STATE_START;
				break;

			case STATE_START:
				LED_G_ON;
				btn = GetPressedButton();
				if (btn != 0)
				{
					elevator.targetFloor = btn;
					elevator.elevatorState = CheckDIR(elevator);
				}
				break;

			case STATE_MOVING_UP:

				break;

			case STATE_MOVING_DOWN:

				break;

			case STATE_ARRIVED:

				break;

			default:
				printf("Error \r\n");
				LED_R_ON();
				break;
		}
	}
}
