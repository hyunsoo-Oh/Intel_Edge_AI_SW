#include "Inc/rgb.h"

static RGB rgb[3] = {
  		{R_Port, R_Pin, SET, RESET},
  		{G_Port, G_Pin, SET, RESET},
  		{B_Port, B_Pin, SET, RESET}
  };

void LED_ON(uint8_t num){
	HAL_GPIO_WritePin(rgb[num].port, rgb[num].pin, rgb[num].onState);
}

void LED_OFF(uint8_t num){
	HAL_GPIO_WritePin(rgb[num].port, rgb[num].pin, rgb[num].offState);
}

void LED_TOGGLE(uint8_t num){
	HAL_GPIO_TogglePin(rgb[num].port, rgb[num].pin);
}

void LED_R_ON()
{
	LED_OFF(G);
	LED_OFF(B);
	LED_ON(R);
}

void LED_G_ON()
{
	LED_OFF(R);
	LED_ON(G);
	LED_OFF(B);
}

void LED_B_ON()
{
	LED_OFF(R);
	LED_OFF(G);
	LED_ON(B);
}
