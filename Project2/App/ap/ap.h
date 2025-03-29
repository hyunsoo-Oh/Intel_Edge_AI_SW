
#ifndef AP_AP_H_
#define AP_AP_H_

#include "hw.h"

void apInit();
void apMain();

void RFID();
uint8_t Button(uint8_t btn);
void FloorCheck();
void LED_Switch();

#endif /* AP_AP_H_ */
