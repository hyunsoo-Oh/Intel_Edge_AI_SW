/*
 * electric_fan.c
 *
 * Created: 2025-02-24 오후 1:22:08
 * Author : USER
 */ 
#include "main.h"

volatile uint8_t fan_state = 0;

void pwm_Init();

int main(void)
{
	FND_Init(&FND_1_DDR);
	FND_Init(&FND_4_DDR);
	FND_C_DDR |= 1 << 0 | 1 << 1 | 1 << 2 | 1 << 3;
	pwm_Init();
	INTn_Init(PINE4);
	
	OCR0 = 0;
	sei();
	/* Replace with your application code */
	while (1)
	{
		FND_A_Display(&FND_1_DDR, fan_state);
		_delay_ms(10);
		FND_4_Display();
	}
}

void pwm_Init()
{
	DDRB |= 1 << PINB4;
	// Fast PWM
	TCCR0 |= 1 << WGM01 | 1 << WGM00 | 1 << COM01;
	// Prescaler 256, 62,500Hz, 16us
	TCCR0 |= 1 << CS02 | 1 << CS01;
	OCR0 = 0;
}
ISR(INT4_vect)
{
	fan_state = STOP;
	OCR0 = 0;
}
ISR(INT5_vect)
{
	fan_state = MID;
	OCR0 = 127;
}
ISR(INT6_vect)
{
	fan_state = FAST;
	OCR0 = 255;
}
