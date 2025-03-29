
#ifndef INC_PHOTO_H_
#define INC_PHOTO_H_

#include "def.h"
#include "gpio.h"

#define PHOTO_INT1_Port 	GPIOC
#define PHOTO_INT1_Pin		GPIO_PIN_10
#define PHOTO_INT2_Port 	GPIOC
#define PHOTO_INT2_Pin		GPIO_PIN_11
#define PHOTO_INT3_Port 	GPIOC
#define PHOTO_INT3_Pin		GPIO_PIN_12

typedef struct
{
	GPIO_TypeDef  	*port;
	uint16_t	  	pin;
	GPIO_PinState  	onState;
}PHOTO;

void photoInit();
bool IsINT(uint8_t num);
uint8_t GetFloorINT();

#endif /* INC_PHOTO_H_ */
