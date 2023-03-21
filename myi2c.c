#include "myi2c.h"

void IIC_Init(void)
{					     
	//GPIO初始化
	SET_SCL;
	SET_SCL;
}
//产生IIC起始信号
void IIC_Start(void)
{
	SET_SDA;
	SET_SCL;
	I2C_Delay_us(4);
	CLR_SDA;
	I2C_Delay_us(4);
	CLR_SCL;
}	  
//产生IIC停止信号
void IIC_Stop(void)
{
	//SCL为高电平，SDA的上升沿为I2C停止信号
	CLR_SCL;
	CLR_SDA;
	I2C_Delay_us(4);
	SET_SCL;
	SET_SDA;	
	I2C_Delay_us(4);					   	
}
//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
uint8_t IIC_Wait_Ack(void)
{
	uint8_t ucErrTime=0;
	SET_SDA;
	I2C_Delay_us(1);	   
	SET_SCL;
	I2C_Delay_us(1);	 
	while(READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop();
			return 1;
		}
	}
	CLR_SCL;//时钟输出0 	   
	return 0;  
} 
//产生ACK应答
void IIC_Ack(void)
{
	CLR_SCL;
	CLR_SDA;
	I2C_Delay_us(2);
	SET_SCL;
	I2C_Delay_us(2);
	CLR_SCL;
}
//不产生ACK应答		    
void IIC_NAck(void)
{
	CLR_SCL;
	SET_SDA;
	I2C_Delay_us(2);
	SET_SCL;
	I2C_Delay_us(2);
	CLR_SCL;
}					 				     
//IIC发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答			  
void IIC_Send_Byte(uint8_t txd)
{                        
  uint8_t t;    	    
	CLR_SCL;//拉低时钟开始数据传输
	for(t=0;t<8;t++)
	{ 
		if(((txd&0x80)>>7)>0) SET_SDA;
		else CLR_SDA;
		txd<<=1; 	  
		I2C_Delay_us(2);
		SET_SCL;
		I2C_Delay_us(2);
		CLR_SCL;	
		I2C_Delay_us(2);
  }	 
} 	    
//读1个字节，ack=1时，发送ACK，ack=0，发送nACK   
uint8_t IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
  for(i=0;i<8;i++ )
	{
    CLR_SCL; 
    I2C_Delay_us(2);
		SET_SCL;
    receive<<=1;
    if(READ_SDA)receive++;   
		I2C_Delay_us(2);
    }					 
    if (!ack)
        IIC_NAck();//发送nACK
    else
        IIC_Ack(); //发送ACK   
    return receive;
}

void I2C_Delay_us(uint8_t us)
{
	uint8_t i = 0;
	
	//通过示波器测量进行校准
	while(us--)
	{
		for(i=0;i<20;i++);
	}
}
