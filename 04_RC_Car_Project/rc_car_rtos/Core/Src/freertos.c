/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "motor.h"
#include "auto_car.h"
#include "bluetooth.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
extern MotorState motor;
extern CarState_t mode;
/* USER CODE END Variables */
/* Definitions for MotorControlTas */
osThreadId_t MotorControlTasHandle;
const osThreadAttr_t MotorControlTas_attributes = {
  .name = "MotorControlTas",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for UltrasonicTask */
osThreadId_t UltrasonicTaskHandle;
const osThreadAttr_t UltrasonicTask_attributes = {
  .name = "UltrasonicTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for BluetoothTask */
osThreadId_t BluetoothTaskHandle;
const osThreadAttr_t BluetoothTask_attributes = {
  .name = "BluetoothTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for btSemHandler */
osSemaphoreId_t btSemHandlerHandle;
const osSemaphoreAttr_t btSemHandler_attributes = {
  .name = "btSemHandler"
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void Task_MotorControl(void *argument);
void Task_Ultrasonic(void *argument);
void Task_Bluetooth(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
  ULTRASONIC_Init();
  MOTER_DRIVE_Init();
  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* Create the semaphores(s) */
  /* creation of btSemHandler */
  btSemHandlerHandle = osSemaphoreNew(10, 0, &btSemHandler_attributes);

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  BLUETOOTH_Init();
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of MotorControlTas */
  MotorControlTasHandle = osThreadNew(Task_MotorControl, NULL, &MotorControlTas_attributes);

  /* creation of UltrasonicTask */
  UltrasonicTaskHandle = osThreadNew(Task_Ultrasonic, NULL, &UltrasonicTask_attributes);

  /* creation of BluetoothTask */
  BluetoothTaskHandle = osThreadNew(Task_Bluetooth, NULL, &BluetoothTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_Task_MotorControl */
/**
  * @brief  Function implementing the MotorControlTas thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_Task_MotorControl */
void Task_MotorControl(void *argument)
{
  /* USER CODE BEGIN Task_MotorControl */
  /* Infinite loop */
	for(;;)
	{
		BLUETOOTH_Parsing(&motor);

		switch (mode)
		{
			case Active_mode:
				MOTOR_SetMotor(motor);
				break;
			case Passive_mode:
				AUTO_Drive();
				break;
		}
		osDelay(1);
	}
  /* USER CODE END Task_MotorControl */
}

/* USER CODE BEGIN Header_Task_Ultrasonic */
/**
* @brief Function implementing the UltrasonicTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Task_Ultrasonic */
void Task_Ultrasonic(void *argument)
{
  /* USER CODE BEGIN Task_Ultrasonic */
  const TickType_t period = pdMS_TO_TICKS(30);
  TickType_t lastWake     = xTaskGetTickCount();
  uint8_t idx = 0;
  /* Infinite loop */
  for(;;)
  {
	  ULTRASONIC_TRIG_On(idx);
	  delay_us(10);
	  ULTRASONIC_TRIG_Off(idx);
	  idx = (idx + 1) % SENSOR_COUNT;

	  vTaskDelayUntil(&lastWake, period);
  }
  /* USER CODE END Task_Ultrasonic */
}

/* USER CODE BEGIN Header_Task_Bluetooth */
/**
* @brief Function implementing the BluetoothTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Task_Bluetooth */
void Task_Bluetooth(void *argument)
{
  /* USER CODE BEGIN Task_Bluetooth */
    const TickType_t period = pdMS_TO_TICKS(100);
    TickType_t lastWake    = xTaskGetTickCount();
    uint16_t dist[3];
    uint8_t txData[32];
    uint8_t txLen;
  /* Infinite loop */
  for(;;)
  {
	  ULTRASONIC_GetData(dist);
	  txLen = snprintf((char*)txData, sizeof(txData),
	  				"L:%2d R:%2d C:%2d\n", dist[0], dist[1], dist[2]);

	  HAL_UART_Transmit_DMA(&huart2, txData, txLen);
	  HAL_UART_Transmit_DMA(&huart1, txData, txLen);

	  vTaskDelayUntil(&lastWake, period);
  }
  /* USER CODE END Task_Bluetooth */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

