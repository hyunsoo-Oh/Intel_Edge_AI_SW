
#include "buzzer.h"

void buzzerInit()
{
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
}

void CallBuzzer()
{
	HAL_Delay(50);
	Buzzer_Pin->PSC = Mi; // mi
	Buzzer_Pin->CCR1 = 500;
	HAL_Delay(qNote);
	Buzzer_Pin->CCR1 = 0;
	HAL_Delay(10);

	Buzzer_Pin->PSC = Do; // Do
	Buzzer_Pin->CCR1 = 500;
	HAL_Delay(qNote);
	Buzzer_Pin->CCR1 = 0;

	Buzzer_Pin->PSC = 0;
	Buzzer_Pin->CCR1 = 0;
}
