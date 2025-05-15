/*
 * adxl345.h
 *
 *  Created on: May 10, 2025
 *      Author: User
 */

#ifndef HW_INC_ADXL345_H_
#define HW_INC_ADXL345_H_

#include "def.h"
#include "spi.h"
#include "usart.h"
#include "gpio.h"

/* ──────────────────────────────
 *  ID & STATUS
 * ──────────────────────────────*/
#define ADXL_DEVID          0x00    /* Device ID (R)   ― 0xE5 */

#define ADXL_INT_SOURCE     0x30    /* Interrupt Source (R)   */
#define ADXL_FIFO_STATUS    0x39    /* FIFO Status   (R)      */

/* ──────────────────────────────
 *  OFFSET REGISTERS
 * ──────────────────────────────*/
#define ADXL_OFSX           0x1E    /* X-axis Offset (R/W)    */
#define ADXL_OFSY           0x1F    /* Y-axis Offset (R/W)    */
#define ADXL_OFSZ           0x20    /* Z-axis Offset (R/W)    */

/* ──────────────────────────────
 *  TAP / ACTIVITY / FREE-FALL
 * ──────────────────────────────*/
#define ADXL_THRESH_TAP     0x1D    /* Tap Threshold          */
#define ADXL_DUR            0x21    /* Tap Duration           */
#define ADXL_LATENT         0x22    /* Tap Latency            */
#define ADXL_WINDOW         0x23    /* Tap Window             */

#define ADXL_THRESH_ACT     0x24    /* Activity Threshold     */
#define ADXL_THRESH_INACT   0x25    /* Inactivity Threshold   */
#define ADXL_TIME_INACT     0x26    /* Inactivity Time        */
#define ADXL_ACT_INACT_CTL  0x27    /* Axis Enable (Act/Inact)*/

#define ADXL_THRESH_FF      0x28    /* Free-Fall Threshold    */
#define ADXL_TIME_FF        0x29    /* Free-Fall Time         */

#define ADXL_TAP_AXES       0x2A    /* Tap Axis Control       */
#define ADXL_ACT_TAP_STATUS 0x2B    /* Tap/Activity Status (R)*/

/* ──────────────────────────────
 *  DATA RATE / POWER
 * ──────────────────────────────*/
#define ADXL_BW_RATE        0x2C    /* Data Rate & Power Mode */
#define ADXL_POWER_CTL      0x2D    /* Power-Saving Control   */

/* ──────────────────────────────
 *  INTERRUPTS
 * ──────────────────────────────*/
#define ADXL_INT_ENABLE     0x2E    /* Interrupt Enable       */
#define ADXL_INT_MAP        0x2F    /* Interrupt Mapping      */

/* ──────────────────────────────
 *  DATA FORMAT & DATA REGISTERS
 * ──────────────────────────────*/
#define ADXL_DATA_FORMAT    0x31    /* Data Format Control    */

#define ADXL_DATAX0         0x32    /* X-Axis Data 0 (LSB)    */
#define ADXL_DATAX1         0x33    /* X-Axis Data 1 (MSB)    */
#define ADXL_DATAY0         0x34    /* Y-Axis Data 0 (LSB)    */
#define ADXL_DATAY1         0x35    /* Y-Axis Data 1 (MSB)    */
#define ADXL_DATAZ0         0x36    /* Z-Axis Data 0 (LSB)    */
#define ADXL_DATAZ1         0x37    /* Z-Axis Data 1 (MSB)    */

/* ──────────────────────────────
 *  FIFO CONTROL
 * ──────────────────────────────*/
#define ADXL_FIFO_CTL       0x38    /* FIFO Control (R/W)     */

#define ADXL_CS_PORT		GPIOB
#define ADXL_CS_PIN			GPIO_PIN_6

typedef struct {
	uint16_t ax_data;
	uint16_t ay_data;
	uint16_t az_data;
	uint8_t bw_rate;
	uint8_t power_ctl;
	uint8_t data_format;
	uint8_t thresh_act;
	uint8_t thresh_inact;
	uint8_t time_inact;
	uint8_t act_inact_ctl;
	uint8_t fifo_ctl;
} AccelConfig;

typedef struct {
	uint16_t off_ax;
	uint16_t off_ay;
	uint16_t off_az;
} AccelOffset;

typedef struct {
	uint16_t ax;
	uint16_t ay;
	uint16_t az;
} ScaledData;

HAL_StatusTypeDef SPI_Write(uint8_t reg, uint8_t data);
HAL_StatusTypeDef SPI_Read(uint8_t reg, uint8_t *pData, uint8_t len);

void ADXL345_Init();

#endif /* HW_INC_ADXL345_H_ */
