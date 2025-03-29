
#include "ap.h"

char *MSG[3] = { "Place card", "Read From Card", "Read From Tag"};
uint16_t TargetDegrees = 1000;

uint8_t prevFloor = 0;
uint8_t currFloor = 0;
uint8_t targetFloor = 0;
uint8_t cnt = 0;

uint8_t IDflag = 0;
uint8_t IRflag = 0;
uint8_t BtnFlag = 0;

uint8_t prevState = 0;
char prevStr[16] = "";

char lcdTarget[16] = "";
char lcdCurrent[16] = "";
char lcdBuff[16] = "";
char msg[16] = "";

extern uint32_t ckTime;

void apInit()
{
	hwInit();

//	setMotorDirection(DIR_CCW);
//	targetFloor = 1;
//	rotateDegrees(1800);
}


void apMain()
{
	lcd_command(CLEAR_DISPLAY);
	HAL_Delay(2);
	while(1)
	{
		LED_Switch();
		IDflag = CheckRFID();
		strcpy(msg, MSG[IDflag]);

		if(strcmp(msg, prevStr) != 0)
		{
			strcpy(prevStr, msg);
			printf("%s \r\n", prevStr);
			lcd_command(CLEAR_DISPLAY);
			HAL_Delay(2);
			move_cursor(0, 0);
			lcd_string(prevStr);
		}

		if(IRflag == 1)
		{
			IRflag = 0;
			OpenDoor();
			HAL_Delay(2000);
		}

//		if(currFloor == prevFloor)
//		{
//			LCD_Write_Floor();
//		}

		if(IDflag != 0)
		{

			uint8_t btn = GetPressedButton();
			BtnFlag = Button(btn);

			if(BtnFlag)
			{
				lcd_command(CLEAR_DISPLAY);
				HAL_Delay(2);
			}
			if(GetStateStep() == 0 && BtnFlag == 0)
			{
				move_cursor(1, 0);
				lcd_string("What floor");
			}
			else
			{
				if(targetFloor != currFloor)
				{
					ckTime = RequestTime;
					prevFloor = currFloor;
					// UP or Down
					int8_t distance = targetFloor - currFloor;
					uint8_t dir = distance > 0 ? DIR_CW : DIR_CCW;
					setMotorDirection(dir);
					lcd_command(CLEAR_DISPLAY);
					HAL_Delay(2);
					sprintf(lcdTarget, "TF : %d  %s", targetFloor, dir ? "DOWN" : "UP");
					sprintf(lcdCurrent, "CF : %d", currFloor);
					move_cursor(0, 0);
					lcd_string(lcdTarget);
					move_cursor(1, 0);
					lcd_string(lcdCurrent);
					while(1)
					{
						rotateDegrees(100);
						if(prevFloor != currFloor)
						{
							prevFloor = currFloor;
							sprintf(lcdCurrent, "CF : %d", currFloor);
							move_cursor(1, 0);
							lcd_string(lcdCurrent);
						}
						if(targetFloor == currFloor)
						{
							break;
						}
					}
					CallBuzzer();
				}
			}
		}
	}
}

uint8_t Button(uint8_t btn)
{
	if(btn != 0)
	{
		if(btn == 4)
		{
			if(!GetStateStep())
			{
				OpenDoor();
			}
		}
		else if(btn == 5)
		{
			if(!GetStateStep() && GetStateDoor() == OPENED)
			{
				CloseDoor();
			}
		}
		else
		{
			if(cnt < 4)
			{
				targetFloor = btn;
			}
		}
		return 1;
	}
	return 0;
}

void FloorCheck()
{
	if(prevFloor != currFloor)
	{
		if(targetFloor == currFloor)
		{
			StopMotor();
		}
	}
}

void LED_Switch()
{
	if(GetStateStep())
	{
		LED_G_OFF();
		LED_R_ON();
	}
	else
	{
		LED_R_OFF();
		LED_G_ON();
	}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == PHOTO_INT1_Pin)
	{
		currFloor = 1;
		FloorCheck();
	}
	else if(GPIO_Pin == PHOTO_INT2_Pin)
	{
		currFloor = 2;
		FloorCheck();
	}
	else if(GPIO_Pin == PHOTO_INT3_Pin)
	{
		currFloor = 3;
		FloorCheck();
	}
	else if(GPIO_Pin == IR_Pin)
	{
		IRflag = 1;
	}
}
