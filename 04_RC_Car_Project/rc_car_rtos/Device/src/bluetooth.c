/*
 * bluetooth.c
 *
 *  Created on: May 9, 2025
 *      Author: USER
 */

#include "bluetooth.h"

static uint8_t dmaBuff[DMA_BUF_SIZE];
static uint8_t cmdData[COMMAND_MAX + 1];
static uint8_t cmdLength;
static volatile uint8_t btFlag = 0;

volatile uint8_t rxFlag = 0;
volatile uint8_t txFlag = 0;

volatile uint8_t rxFlag;
uint8_t rxData;
uint8_t txData[16];

extern CarState_t mode;

void BLUETOOTH_Init(void)
{
	HAL_UARTEx_ReceiveToIdle_DMA(&huart1, dmaBuff, DMA_BUF_SIZE);
	__HAL_DMA_DISABLE_IT(huart1.hdmarx, DMA_IT_HT);
	__HAL_UART_ENABLE_IT(&huart1, UART_IT_IDLE);
}

static int16_t STR_TO_Integer(char *s)
{
	int16_t val = 0;
	while (*s >= '0' && *s <= '9')
	{
		val = val * 10 + (*s - '0');
		s++;
	}
	return val;
}

static void MODE_Change(const uint8_t *cmdData, uint8_t len)
{
    if (cmdData[0] == 'Z')
    {
        mode = (mode == Active_mode) ? Passive_mode : Active_mode;
    }
}

void BLUETOOTH_Parsing(MotorState *motor)
{
	if (btFlag == 1)
	{
		btFlag = 0;
		MODE_Change(cmdData, cmdLength);
	}

	if (mode == Passive_mode) return;

	char front_buff[2] = { cmdData[1], cmdData[2] };
	char side_buff[2]  = { cmdData[4], cmdData[5] };

	motor->front_direction = (MotorDir_t)(cmdData[0]);
	motor->side_direction  = (MotorDir_t)(cmdData[3]);
	motor->base_speed      = STR_TO_Integer(front_buff);
	motor->dir_speed       = STR_TO_Integer(side_buff);
}

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
    if (huart == &huart1)
    {
        for (uint16_t i = 0; i < Size; i++)
        {
            char c = (char)dmaBuff[i];

            if (c != '\n' && cmdLength < COMMAND_MAX)
            {
            	cmdData[cmdLength++] = c;
            }
            else if (c == '\n')
            {
            	cmdData[cmdLength] = '\0';
				btFlag = 1;
				cmdLength = 0;
            }
        }
    }
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART2)
    {
        txFlag = 1;
    }
}
