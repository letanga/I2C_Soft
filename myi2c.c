#include "myi2c.h"

void IIC_Init(void)
{					     
	//GPIO��ʼ��
	SET_SCL;
	SET_SCL;
}
//����IIC��ʼ�ź�
void IIC_Start(void)
{
	SET_SDA;
	SET_SCL;
	I2C_Delay_us(4);
	CLR_SDA;
	I2C_Delay_us(4);
	CLR_SCL;
}	  
//����IICֹͣ�ź�
void IIC_Stop(void)
{
	//SCLΪ�ߵ�ƽ��SDA��������ΪI2Cֹͣ�ź�
	CLR_SCL;
	CLR_SDA;
	I2C_Delay_us(4);
	SET_SCL;
	SET_SDA;	
	I2C_Delay_us(4);					   	
}
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
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
	CLR_SCL;//ʱ�����0 	   
	return 0;  
} 
//����ACKӦ��
void IIC_Ack(void)
{
	CLR_SCL;
	CLR_SDA;
	I2C_Delay_us(2);
	SET_SCL;
	I2C_Delay_us(2);
	CLR_SCL;
}
//������ACKӦ��		    
void IIC_NAck(void)
{
	CLR_SCL;
	SET_SDA;
	I2C_Delay_us(2);
	SET_SCL;
	I2C_Delay_us(2);
	CLR_SCL;
}					 				     
//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��			  
void IIC_Send_Byte(uint8_t txd)
{                        
  uint8_t t;    	    
	CLR_SCL;//����ʱ�ӿ�ʼ���ݴ���
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
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
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
        IIC_NAck();//����nACK
    else
        IIC_Ack(); //����ACK   
    return receive;
}

void I2C_Delay_us(uint8_t us)
{
	uint8_t i = 0;
	
	//ͨ��ʾ������������У׼
	while(us--)
	{
		for(i=0;i<20;i++);
	}
}
