
#ifndef INC_IR_H_
#define INC_IR_H_

#include "def.h"
#include "gpio.h"

// IR SENSOR
#define IR_Port GPIOC
#define IR_Pin 	GPIO_PIN_13

bool IRSensor();

#endif /* INC_IR_H_ */
