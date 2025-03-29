
#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "def.h"
#include "gpio.h"

// BUTTONS
#define Btn1_Port 	GPIOB
#define Btn1_Pin	GPIO_PIN_5
#define Btn2_Port 	GPIOB
#define Btn2_Pin	GPIO_PIN_10
#define Btn3_Port 	GPIOB
#define Btn3_Pin	GPIO_PIN_13
#define Btn4_Port 	GPIOB
#define Btn4_Pin	GPIO_PIN_14
#define Btn5_Port 	GPIOB
#define Btn5_Pin	GPIO_PIN_15

#define DEBOUNCE_DELAY 50

typedef struct
{
	GPIO_TypeDef  	*port;
	uint16_t	  	pinNumber;
	GPIO_PinState  	onState;
	uint32_t  		prevTime;
}BUTTON;

bool IsButtonPress(uint8_t num);
uint8_t GetPressedButton();

#endif /* INC_BUTTON_H_ */
