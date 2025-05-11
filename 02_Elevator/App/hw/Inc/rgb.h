
#ifndef INC_RGB_H_
#define INC_RGB_H_

#include "def.h"
#include "gpio.h"

// RGB
#define R_Port 	GPIOC
#define R_Pin	GPIO_PIN_5
#define G_Port 	GPIOC
#define G_Pin	GPIO_PIN_6
#define B_Port 	GPIOC
#define B_Pin	GPIO_PIN_8

typedef struct
{
	GPIO_TypeDef  *port;
	uint16_t	   pin;
	GPIO_PinState  onState;
	GPIO_PinState  offState;
}RGB;

enum
{
	R, G, B
};

void LED_ON(uint8_t num);
void LED_OFF(uint8_t num);
void LED_TOGGLE(uint8_t num);

void LED_R_ON();
void LED_G_ON();
void LED_B_ON();

#endif /* INC_RGB_H_ */
