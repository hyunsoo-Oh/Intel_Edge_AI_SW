///*
// * imu.c
// *
// *  Created on: May 10, 2025
// *      Author: User
// */
//
//#include <imu.h>
//
//uint8_t test;
//
//static AccelConfig cfg = {
//	.ax_data = 0,
//	.ay_data = 0,
//	.az_data = 0,
//	.bw_rate = 0x0D,		/* 	400 Hz 			*/
//	.power_ctl = 0x08,		/* 	Measure			*/
//	.data_format = 0,		/* 	FULL_RES ±16g	*/
//	.thresh_act = 0,
//	.thresh_inact = 0,
//	.time_inact = 0,
//	.act_inact_ctl = 0,
//	.fifo_ctl = 0
//};
//
//AccelOffset offset = { 0, 0, 0 };
//ScaledData data = { 0, 0, 0 };
//
//static inline void SPI_CS_LOW()
//{
//	HAL_GPIO_WritePin(ADXL_CS_PORT, ADXL_CS_PIN, RESET);
//}
//static inline void SPI_CS_HIGH()
//{
//	HAL_GPIO_WritePin(ADXL_CS_PORT, ADXL_CS_PIN, SET);
//}
//
//HAL_StatusTypeDef SPI_Write(uint8_t reg, uint8_t data)
//{
//	uint8_t tx[2];
//	tx[0] = reg & 0x3F;
//	tx[1] = data;
//
//	SPI_CS_LOW();
//	HAL_StatusTypeDef status = HAL_SPI_Transmit(&hspi1, tx, 2, 100);
//	SPI_CS_HIGH();
//
//	return status;
//}
//
//HAL_StatusTypeDef SPI_Read(uint8_t reg, uint8_t *pData, uint8_t len)
//{
//    uint8_t tx;
//    if (len > 1)	tx = 0xC0 | (reg & 0x3F);
//    else 			tx = 0x80 | (reg & 0x3F);
//
//    SPI_CS_LOW();
//    HAL_StatusTypeDef status = HAL_SPI_Transmit(&hspi1, &tx, 1, 100);
//    if (status != HAL_OK) { SPI_CS_HIGH(); return status; }
//
//    status = HAL_SPI_Receive(&hspi1, pData, len, 100);
//    SPI_CS_HIGH();
//
//    return status;
//}
//
//void ADXL345_Init()
//{
//	uint8_t device_id;
//	uint8_t response = SPI_Read(ADXL_DEVID, &device_id, 1);
//	if (response == HAL_OK) HAL_UART_Transmit(&huart2, (uint8_t *)"ACK\r\n", 5, 100);
//	test = device_id;
//	if (device_id != 0xE5)	HAL_UART_Transmit(&huart2, (uint8_t *)"Device NO\r\n", 11, 100);
//	else					HAL_UART_Transmit(&huart2, (uint8_t *)"Device OK\r\n", 11, 100);
//}
