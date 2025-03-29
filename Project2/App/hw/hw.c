
#include "hw.h"
#include "tim.h"

void hwInit()
{
	buzzerInit();
	photoInit();
	servoInit();
	stepperInit(&htim10, 0);
	MFRC522_Init();
	i2c_lcd_init();

}



PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the USART2 and Loop
     until the end of transmission */
  if(ch == '\n')
    HAL_UART_Transmit(&huart2, (uint8_t*) "\r", 1, 0xFFFF);
    HAL_UART_Transmit(&huart2, (uint8_t*) &ch, 1, 0xFFFF);
}
