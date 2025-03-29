/*
 * hw.h
 *
 *  Created on: Mar 25, 2025
 *      Author: USER
 */

#ifndef HW_HW_H_
#define HW_HW_H_

#include "def.h"
#include "Inc/button.h"
#include "Inc/ir.h"
#include "Inc/photo.h"
#include "Inc/rgb.h"
#include "Inc/servo.h"
#include "Inc/stepper.h"
#include "Inc/rc522.h"
#include "Inc/i2c_lcd.h"
#include "usart.h"

#define PUTCHAR_PROTOTYPE int  __io_putchar(int ch)

//const char *MSG1 = "Reading From Card\r\n";
//const char *MSG2 = "Reading From Tag\r\n";
//const char *MSG3 = "Place card to read\r\n";

void hwInit();

#endif /* HW_HW_H_ */
