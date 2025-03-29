
#include "ir.h"

void IRInit()
{
	HAL_GPIO_EXTI_IRQHandler(IR_Pin);
}

bool IRSensor(){
	return HAL_GPIO_ReadPin(IR_Port, IR_Pin);

//	if(isBody)
//	{
//	  uint8_t rxData[] = "Detected by HC_SR501\r\n";
//	  HAL_UART_Transmit(&huart2, rxData, sizeof(rxData), 100);
//	isBody =
//	}
//	else
//	{
//	  uint8_t rxData[] = "Not Detected by HC_SR501\r\n";
//	  HAL_UART_Transmit(&huart2, rxData, sizeof(rxData), 100);
//	}
}
