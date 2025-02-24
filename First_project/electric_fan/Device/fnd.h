/*
 * fnd.h
 *
 * Created: 2025-02-24 오전 10:46:47
 *  Author: USER
 */ 


#ifndef FND_H_
#define FND_H_

#include "../main.h"

#define FND_1_DDR	DDRA
#define FND_4_DDR	DDRC
#define FND_C_DDR	DDRB
#define FND_C_PORT	PORTB

#define STR_O		0x3F
#define STR_N		0x37
#define STR_F		0x71

extern uint8_t FND_Num[];

void FND_Init(volatile uint8_t *ddr);
void FND_A_Display(volatile uint8_t *ddr, uint16_t num);
void FND_C_Display(volatile uint8_t *ddr, uint16_t num);
void FND_4_Display();

#endif /* FND_H_ */