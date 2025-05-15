/*
 * auto_car.c
 *
 *  Created on: May 15, 2025
 *      Author: User
 */

#include "auto_car.h"

CarState_t mode = Passive_mode;

extern MotorState motor;
extern UltraData uData[3];

void AUTO_Drive()
{
    uint32_t distL = uData[0].distance_cm;
    uint32_t distR = uData[1].distance_cm;
    uint32_t distC = uData[2].distance_cm;

    if (distC > 60)
    {
    	// 충분히 전방이 넓으면 빠르게 직진
        motor.left_direction  = DIR_FORWARD;
        motor.right_direction = DIR_FORWARD;
        motor.left_speed      = AUTO_CAR_MAX_SPEED;
        motor.right_speed     = AUTO_CAR_MAX_SPEED;
        MOTOR_SetMotor(motor);
    }
    else if (distC > 30)
    {
    	// 보통 속도로 직진
        motor.left_direction  = DIR_FORWARD;
        motor.right_direction = DIR_FORWARD;
        motor.left_speed      = AUTO_CAR_MID_SPEED;
        motor.right_speed     = AUTO_CAR_MID_SPEED;
        MOTOR_SetMotor(motor);
    }
    else
    {
        // 장애물 가까이 → 회피 판단
        if (distR < 20 && distL < 20)
        {
            // 좌·우 모두 좁으면 뒤로 돌기
            motor.left_direction  = DIR_BACKWARD;
            motor.right_direction = DIR_BACKWARD;
            motor.left_speed      = AUTO_CAR_MIN_SPEED;
            motor.right_speed     = AUTO_CAR_MIN_SPEED;
            MOTOR_SetMotor(motor);
        }
        else if (distR >= distL)
        {
            // 오른쪽이 더 넓으면 제자리 우회전
            MOTOR_Rotate(ROTATE_RIGHT);
        }
        else
        {
            // 왼쪽이 더 넓으면 제자리 좌회전
            MOTOR_Rotate(ROTATE_LEFT);
        }
        // 회전 후 잠깐 멈춤
        motor.left_direction  = DIR_STOP;
        motor.right_direction = DIR_STOP;
        motor.left_speed      = 0;
        motor.right_speed     = 0;
        MOTOR_SetMotor(motor);
    }
}
