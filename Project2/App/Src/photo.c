
#include "photo.h"

static PHOTO photo[3] = {
		{PHOTO_INT1_Port, PHOTO_INT1_Pin, 1},
		{PHOTO_INT2_Port, PHOTO_INT1_Pin, 1},
		{PHOTO_INT3_Port, PHOTO_INT1_Pin, 1}
};

void photoInit()
{
//	HAL_GPIO_EXTI_IRQHandler(PHOTO_INT1_Pin);
//	HAL_GPIO_EXTI_IRQHandler(PHOTO_INT2_Pin);
//	HAL_GPIO_EXTI_IRQHandler(PHOTO_INT3_Pin);
}

bool IsINT(uint8_t num){
	bool result = false;
	if(HAL_GPIO_ReadPin(photo[num].port, photo[num].pin))
	{
		result = true;
	}
	return result;
}

uint8_t GetFloorINT(){
	uint8_t num = 0;
	if(IsINT(0)) num = 1;
	if(IsINT(1)) num = 2;
	if(IsINT(2)) num = 3;

	return num;
}

