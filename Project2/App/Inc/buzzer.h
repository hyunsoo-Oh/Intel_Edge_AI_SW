
#ifndef INC_BUZZER_H_
#define INC_BUZZER_H_

#include "def.h"
#include "tim.h"

#define Buzzer_Pin TIM2

#define Do  383
#define Mi  304
#define Sol 255
#define qNote 600

void buzzerInit();
void CallBuzzer();

#endif /* INC_BUZZER_H_ */
