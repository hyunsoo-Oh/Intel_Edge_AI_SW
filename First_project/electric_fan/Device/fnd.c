/*
 * fnd.c
 *
 * Created: 2025-02-24 오전 10:46:35
 *  Author: USER
 */ 
#include "fnd.h"

uint8_t FND_Num[] = {
	0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x27, 0x7F, 0x67
};

void FND_Init(volatile uint8_t *ddr)
{
	*ddr = 0xff;
	*(ddr + 1) = 0x00;
}
void FND_A_Display(volatile uint8_t *ddr, uint16_t num)
{
	*(ddr + 1) = ~FND_Num[num];
}
void FND_C_Display(volatile uint8_t *ddr, uint16_t str)
{
	*(ddr + 1) = str;
}
void FND_4_Display()
{
	static uint8_t position = 0;
	if (fan_state == 0)
	{
		switch (position)
		{
			case 1:
			FND_C_PORT &= ~(1 << 1);
			FND_C_PORT |= 1 << 0 | 1 << 2 | 1 << 3;
			FND_C_Display(&FND_4_DDR, STR_O);
			break;
			case 2:
			FND_C_PORT &= ~(1 << 2);
			FND_C_PORT |= 1 << 0 | 1 << 1 | 1 << 3;
			FND_C_Display(&FND_4_DDR, STR_F);
			break;
			case 3:
			FND_C_PORT &= ~(1 << 3);
			FND_C_PORT |= 1 << 1 | 1 << 2 | 1 << 0;
			FND_C_Display(&FND_4_DDR, STR_F);
			break;
		}
	}
	else
	{
		switch (position)
		{
			case 2:
			FND_C_PORT &= ~(1 << 2);
			FND_C_PORT |= 1 << 0 | 1 << 1 | 1 << 3;
			FND_C_Display(&FND_4_DDR, STR_O);
			break;
			case 3:
			FND_C_PORT &= ~(1 << 3);
			FND_C_PORT |= 1 << 1 | 1 << 2 | 1 << 0;
			FND_C_Display(&FND_4_DDR, STR_N);
			break;
		}
	}
	position = (position + 1) % 4;
}