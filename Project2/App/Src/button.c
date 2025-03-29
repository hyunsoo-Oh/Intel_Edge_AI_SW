
#include "button.h"

static BUTTON button[5]={
		{Btn1_Port, Btn1_Pin, 0, 0},
		{Btn2_Port, Btn2_Pin, 0, 0},
		{Btn3_Port, Btn3_Pin, 0, 0},
		{Btn4_Port, Btn4_Pin, 0, 0},
		{Btn5_Port, Btn5_Pin, 0, 0}
};

bool IsButtonPress(uint8_t num)
{
	bool result = false;

	if(button[num].prevTime == 0)
	{
		button[num].prevTime = HAL_GetTick();
	}

	if(HAL_GPIO_ReadPin(button[num].port, button[num].pinNumber) == button[num].onState)
	{
		uint32_t currTime = HAL_GetTick();
		if(currTime - button[num].prevTime > DEBOUNCE_DELAY)
		{
			if(HAL_GPIO_ReadPin(button[num].port, button[num].pinNumber) == button[num].onState)
			{
				result = true;
			}
			button[num].prevTime = currTime;
		}
	}

	return result;
}

uint8_t GetPressedButton()
{
	uint8_t num = 0;
	if(IsButtonPress(0)) num = 1;
	if(IsButtonPress(1)) num = 2;
	if(IsButtonPress(2)) num = 3;
	if(IsButtonPress(3)) num = 4;
	if(IsButtonPress(4)) num = 5;
	return num;
}
