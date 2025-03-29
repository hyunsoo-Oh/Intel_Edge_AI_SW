/*
 * hw.h
 *
 *  Created on: Mar 25, 2025
 *      Author: USER
 */

#ifndef HW_HW_H_
#define HW_HW_H_

#include "def.h"
#include "button.h"
#include "ir.h"
#include "photo.h"
#include "rgb.h"
#include "servo.h"
#include "stepper.h"
#include "rc522.h"
#include "i2c_lcd.h"
#include "usart.h"

#define PUTCHAR_PROTOTYPE int  __io_putchar(int ch)

//const char *MSG1 = "Reading From Card\r\n";
//const char *MSG2 = "Reading From Tag\r\n";
//const char *MSG3 = "Place card to read\r\n";

void hwInit();

#endif /* HW_HW_H_ */
