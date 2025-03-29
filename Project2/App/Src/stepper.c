
#include "stepper.h"

static TIM_HandleTypeDef *tim;
static volatile uint8_t currentStep = 0; // 현재 스텝 위치
static volatile uint8_t motorDirection = DIR_CCW; // 초기 방향
volatile uint16_t remainingSteps = 0;  // 남은 스텝 수

// 모터 상태 변수 (모터가 작동 중인지 여부를 나타냄)
static volatile uint8_t motorRunning = 0; // 0: 멈춤, 1: 작동

void stepperInit(TIM_HandleTypeDef *htim, uint8_t speedLevel)
{
	tim = htim;
	stepperSpeed(speedLevel);
}

// 모터 1스텝 회전 함수
void stepMotor(uint8_t step) {
    HAL_GPIO_WritePin(IN1_Port, IN1_Pin, HALF_STEP_SEQ[step][0]);
    HAL_GPIO_WritePin(IN2_Port, IN2_Pin, HALF_STEP_SEQ[step][1]);
    HAL_GPIO_WritePin(IN3_Port, IN3_Pin, HALF_STEP_SEQ[step][2]);
    HAL_GPIO_WritePin(IN4_Port, IN4_Pin, HALF_STEP_SEQ[step][3]);
}

// 지정된 스텝만큼 회전하는 함수
//void rotateSteps(uint16_t steps, uint8_t direction) {
//    for (uint16_t i = 0; i < steps; i++) {
//        uint8_t step;
//        if (direction == DIR_CW) {
//            step = i % 8; // 시계방향
//        } else {
//            step = 7 - (i % 8); // 반시계방향
//        }
//        stepMotor(step);
//    }
//}

//void rotateSteps(uint16_t step) {
//	if (motorDirection == DIR_CW) {
//		step = (step + 1) % 8; // 시계방향
//	} else {
//		step = 7 - (i % 8); // 반시계방향
//	}
//	stepMotor(step);
//}

//// 각도에 맞는 스텝수로 회전하는 함수
//void rotateDegrees(uint16_t degrees, uint8_t direction)
//{
//    uint16_t steps = (uint16_t)((uint32_t)(degrees * STEPS_PER_REVOLUTION) / 360);
//    rotateSteps(steps, direction);  // 지정된 방향으로 회전
//}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	printf("into callback \r\n");
    if (htim->Instance == Stepper_Pin) // TIM10 인터럽트 확인
    {
        if (remainingSteps > 0)
        {
            // 방향에 따라 스텝 계산
            if (motorDirection == DIR_CW)
            {
                currentStep = (currentStep + 1) % 8; // 시계 방향
            }
            else
            {
                currentStep = (currentStep == 0) ? 7 : currentStep - 1; // 반시계 방향
            }

            // 모터 스텝 출력
            stepMotor(currentStep);
//            HAL_GPIO_WritePin(IN1_PORT, IN1_PIN, HALF_STEP_SEQ[currentStep][0]);
//            HAL_GPIO_WritePin(IN2_PORT, IN2_PIN, HALF_STEP_SEQ[currentStep][1]);
//            HAL_GPIO_WritePin(IN3_PORT, IN3_PIN, HALF_STEP_SEQ[currentStep][2]);
//            HAL_GPIO_WritePin(IN4_PORT, IN4_PIN, HALF_STEP_SEQ[currentStep][3]);

            // 남은 스텝 감소
            remainingSteps--;
            printf("%d \r\n", remainingSteps);
        }
        if(remainingSteps <= 0)
        {
        	printf("motor stop \r\n");
            // 회전 완료되었으면 타이머 정지
        	motorRunning = 0;
            HAL_TIM_Base_Stop_IT(htim);
        }
    }
}

// 속도 설정 (타이머 주파수 조정)
void stepperSpeed(uint8_t speedLevel)
{
    if (tim->Instance == Stepper_Pin)
    {
        if (speedLevel >= SPEED_TABLE_SIZE) return;

        uint16_t frequency = speedTable[speedLevel]; // 속도 선택
        uint16_t arr = (1000000 / frequency) - 1;    // ARR 계산 (PSC = 99 고정)
        Stepper_Pin->PSC = 100-1;
        Stepper_Pin->ARR = arr;                  // ARR 설정
        __HAL_TIM_SET_COUNTER(tim, 0);             // 타이머 초기화
    }
}

// 방향 설정 (시계방향 또는 반시계방향)
void setMotorDirection(uint8_t direction)
{
    motorDirection = direction;
}

void rotateDegrees(uint16_t degrees)
{
    // 1도 당 몇 스텝인지 계산 (28BYJ-48의 경우 4096 스텝으로 360도 회전)
    uint16_t steps = (uint16_t)((uint32_t)degrees * DRIVE_RESOLUTION / 360);

    // 남은 스텝 수를 초기화
    remainingSteps = steps;

    // 모터 스테이트 전환
    motorRunning = 1;

    // 타이머 인터럽트 시작
    HAL_TIM_Base_Start_IT(tim); // 타이머 인터럽트 시작
}

uint8_t GetStateStep()
{
	return motorRunning;
}

void StopMotor()
{
	remainingSteps = 5;
}
