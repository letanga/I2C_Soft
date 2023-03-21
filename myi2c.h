#ifndef __I2C_H__
#define __I2C_H__

#include "gpio.h"

#define	SET_SCL	HAL_GPIO_WritePin(SCL_GPIO_Port,SCL_Pin,GPIO_PIN_SET)
#define	CLR_SCL	HAL_GPIO_WritePin(SCL_GPIO_Port,SCL_Pin,GPIO_PIN_RESET)
//置位与清零SDA管脚
#define	SET_SDA	HAL_GPIO_WritePin(SDA_GPIO_Port,SDA_Pin,GPIO_PIN_SET)
#define	CLR_SDA	HAL_GPIO_WritePin(SDA_GPIO_Port,SDA_Pin,GPIO_PIN_RESET)
//读SDA管脚状态
#define READ_SDA	HAL_GPIO_ReadPin(SDA_GPIO_Port,SDA_Pin)

void IIC_Init(void);
void IIC_Start(void);
void IIC_Stop(void);
uint8_t IIC_Wait_Ack(void);
void IIC_Ack(void);
void IIC_NAck(void);
void IIC_Send_Byte(uint8_t txd);
uint8_t IIC_Read_Byte(uint8_t ack);
void I2C_Delay_us(uint8_t us);

#endif
