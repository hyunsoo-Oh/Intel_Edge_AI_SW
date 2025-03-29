#ifndef INC_STEPPER_H_
#define INC_STEPPER_H_

#include "def.h"
#include "tim.h"
#include "gpio.h"
#include "buzzer.h"
#include "i2c_lcd.h"

// 회전 관련 설정
#define STEPS_PER_REVOLUTION 4096
#define DIR_CW 0     // 시계방향
#define DIR_CCW 1    // 반시계 방향

// 모터 제어 핀 정의
#define IN1_Port 	GPIOC
#define IN1_Pin 	GPIO_PIN_0

#define IN2_Port 	GPIOC
#define IN2_Pin 	GPIO_PIN_1

#define IN3_Port 	GPIOC
#define IN3_Pin		GPIO_PIN_2

#define IN4_Port 	GPIOC
#define IN4_Pin 	GPIO_PIN_3

#define Stepper_Pin TIM10

// 스태퍼모터 동작 방향
#define DIR_CW            0
#define DIR_CCW           1

// 총 사용 스탭수
#define DRIVE_RESOLUTION  4096

#define SPEED_TABLE_SIZE (sizeof(speedTable) / sizeof(speedTable[0]))

static const uint16_t speedTable[] = {1000, 800, 600, 400, 200}; // 속도 테이블 (Hz 단위)

// Floor
typedef enum
{
	FIRST, SECOND, THIRD
}FLOOR;

// 8단계 HALF_STEP_SEQ 배열 (모터 제어 순서)
static const uint8_t HALF_STEP_SEQ[8][4] = {
    {1, 0, 0, 0},
    {1, 1, 0, 0},
    {0, 1, 0, 0},
    {0, 1, 1, 0},
    {0, 0, 1, 0},
    {0, 0, 1, 1},
    {0, 0, 0, 1},
    {1, 0, 0, 1}
};

// 모터 제어 함수 선언
void stepperInit(TIM_HandleTypeDef *htim, uint8_t speedLevel);
void stepMotor(uint8_t step);
void stepperSpeed(uint8_t speedLevel);
void setMotorDirection(uint8_t direction);
void rotateDegrees(uint16_t degrees);
//void rotateSteps(uint16_t steps, uint8_t direction);
//void rotateDegrees(uint16_t degrees, uint8_t direction);

uint8_t GetStateStep();
void StopMotor();

// 모터 상태 변수 (외부에서 사용할 수 있도록 선언)
//extern volatile uint8_t motorRunning; // 0: 멈춤, 1: 작동

#endif /* INC_STEPPER_H_ */
