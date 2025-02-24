/*
 * btn.c
 *
 * Created: 2025-02-24 오전 10:47:13
 *  Author: USER
 */ 
#include "btn.h"

void INTn_Init(uint8_t n)
{
	BTN_INT_C &= ~(1 << BTN_STOP) & ~(1 << BTN_FAST) & ~(1 << BTN_MID);
	EICRB |= 1 << ISC41 | 1 << ISC51 | 1 << ISC61;
	EIMSK |= 1 << INT4 | 1 << INT5 | 1 << INT6;
}