/*
 * btn.h
 *
 * Created: 2025-02-24 오전 10:47:38
 *  Author: USER
 */ 


#ifndef BTN_H_
#define BTN_H_

#include "../main.h"

#define BTN_INT_C	PORTE
#define BTN_STOP	4
#define BTN_MID		5
#define BTN_FAST	6

enum{STOP, MID, FAST};
	
extern volatile uint8_t fan_state;

void INTn_Init(uint8_t n);

#endif /* BTN_H_ */