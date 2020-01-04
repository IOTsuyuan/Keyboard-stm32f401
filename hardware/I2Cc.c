	
/******************************************************************************
* File Name          : i2c_fram.c 
* Author             : Appcat 
* Version            : V0.0.1 
* Date               : 07/11/2009 
* Description        : This file provides a set of functions needed to manage the 
*                      communication between I2C peripheral and I2C FM24CL16 FRAM. 
*******************************************************************************/ 

/* Includes ------------------------------------------------------------------*/ 
#include "I2C.h" 
#include "stm32f10x.h"
/*================================= */
    
/* Private typedef -----------------------------------------------------------*/ 
/* Private define ------------------------------------------------------------*/ 
#define I2C_Speed              100000 
#define I2C1_SLAVE_ADDRESS7    0xC0 
#define I2C_PageSize           256 

/* Private macro -------------------------------------------------------------*/ 
/* Private variables ---------------------------------------------------------*/ 
 vu8 FRAM_ADDRESS; 

/* Private function prototypes -----------------------------------------------*/ 

void I2C_GPIO_Initial(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOA, ENABLE);
  GPIO_InitStructure.GPIO_Speed=GPIO_Speed_10MHz;
  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_OD;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
  SDA_H;
  SCL_H; 
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_10MHz;
  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14|GPIO_Pin_15;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_10MHz;//SDB_pin
  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

}
void delay_ms(uint32_t t)
{
	uint8_t tt;
	for(;t>0;t--)
	{
		for(tt=255;tt>0;tt--);
		for(tt=255;tt>0;tt--);
		for(tt=255;tt>0;tt--);
		for(tt=255;tt>0;tt--);
		for(tt=255;tt>0;tt--);
		for(tt=255;tt>0;tt--);
		for(tt=255;tt>0;tt--);
		for(tt=30;tt>0;tt--);
	}
}
void I2C_delay_us(int us)
{	
   while(us--); 
}
/*********************************************************************************************************/
int I2C_Start(void)
{
	SDA_H;
	SCL_H;
	I2C_delay_us(I2C_Delay_Time);
	if(!SDA_read)
	{
		return FALSE1;	//SDA???
	}
	SDA_L;
	I2C_delay_us(I2C_Delay_Time);
	if(SDA_read)
	{
	 return FALSE1;	//SDA?????
	}
	SCL_L;
	I2C_delay_us(I2C_Delay_Time);
	return TRUE1;
}
/*********************************************************************************************************/
void I2C_Stop(void)
{
	SCL_L;
	I2C_delay_us(I2C_Delay_Time);
	SDA_L;
	I2C_delay_us(I2C_Delay_Time);
	SCL_H;
	I2C_delay_us(I2C_Delay_Time);
	SDA_H;
	I2C_delay_us(I2C_Delay_Time);
}
/*********************************************************************************************************/
void I2C_Ack(void)
{	
	SCL_L;
	I2C_delay_us(I2C_Delay_Time);
	SDA_L;
	I2C_delay_us(I2C_Delay_Time);
	SCL_H;
	I2C_delay_us(I2C_Delay_Time);
	SCL_L;
	I2C_delay_us(I2C_Delay_Time);
}
/*********************************************************************************************************/
void I2C_NoAck(void)
{	
	SCL_L;
	I2C_delay_us(I2C_Delay_Time);
	SDA_H;
	I2C_delay_us(I2C_Delay_Time);
	SCL_H;
	I2C_delay_us(I2C_Delay_Time);
	SCL_L;
	I2C_delay_us(I2C_Delay_Time);
}
/*********************************************************************************************************/
int I2C_WaitAck(void) 	 //???=1 ?ack,0??ack
{
	SCL_L;
	I2C_delay_us(2*I2C_Delay_Time);	
	SCL_H;
	I2C_delay_us(I2C_Delay_Time);
	if(SDA_read)
	{		
      SCL_L;
      return FALSE1;
	}	
	I2C_delay_us(I2C_Delay_Time);
	return TRUE1;
}
/*********************************************************************************************************/
void I2C_SendByte(int SendByte) // ??????//
{
    int i=8;
    while(i--)
    {
        SCL_L;
        I2C_delay_us(I2C_Delay_Time);
      if(SendByte&0x80)
			{				
        SDA_H; 
			}				
      else 
			{
        SDA_L;   
			}
        SendByte<<=1;
        I2C_delay_us(I2C_Delay_Time);
	      SCL_H; 
        I2C_delay_us(I2C_Delay_Time2);
    }
    SCL_L;
}
/*********************************************************************************************************/
uint8_t I2C_ReceiveByte(void)  //??????//
{ 
    uint8_t i=8;
    uint8_t ReceiveByte=0;

    SDA_H;				
    while(i--)
    {
      ReceiveByte<<=1;      
      SCL_L;
      I2C_delay_us(I2C_Delay_Time);
	    SCL_H;
      I2C_delay_us(I2C_Delay_Time);	
      if(SDA_read)
      {
        ReceiveByte|=0x01;
      }
    }
    SCL_L;
    return ReceiveByte;
}
/*********************************************************************************************************/
//I2C test

uint8_t I2C_Test(uint8_t DeviceAddress)
{		
	  //I2C_Start();
    if(!I2C_Start())return FALSE1;
    I2C_SendByte(DeviceAddress & 0xFE);//
    if(I2C_WaitAck())
    {I2C_Stop(); return TRUE1;}
    else
		{I2C_Stop(); return FALSE1;}	 
    //Systick_Delay_1ms(10);
}


/*********************************************************************************************************/
//I2C ???byte,????,?????,??

uint8_t I2C_WriteByte(int DeviceAddress, int WriteAddress, int SendByte)
{		
	  //I2C_Start();
    if(!I2C_Start())return FALSE1;
    I2C_SendByte(DeviceAddress & 0xFE);//
    if(!I2C_WaitAck())
    {I2C_Stop(); return FALSE1;}
    I2C_SendByte(WriteAddress);   //
    I2C_WaitAck();	
    I2C_SendByte(SendByte);
    I2C_WaitAck();   
    I2C_Stop(); 
    //Systick_Delay_1ms(10);
    return TRUE1;
}
/*********************************************************************************************************/
//I2C ???
//????,??????????,????????,??????  
uint8_t I2C_BufferWrite(uint8_t* pBuffer, int length, int WriteAddress, int DeviceAddress)
{   
	  //I2C_Start();
    if(!I2C_Start())return FALSE1;
    I2C_SendByte(DeviceAddress & 0xFE);//???? 
    if(!I2C_WaitAck()){I2C_Stop(); return FALSE1;}
    I2C_SendByte(WriteAddress);   //??????????      
	  I2C_WaitAck();	  
		while(length--)
		{
		  I2C_SendByte(*pBuffer);
		  I2C_WaitAck();
          pBuffer++;
		}
	  I2C_Stop();
	  //Systick_Delay_1ms(10);
	  return TRUE1;
}

/*********************************************************************************************************/

// I2C ???byte
uint8_t I2C_ReadByte(int DeviceAddress,int ReadAddress)
{		
    uint8_t rec;
		//I2C_Start();
    if(!I2C_Start())return FALSE1;
    I2C_SendByte(DeviceAddress & 0xFE);// 
    if(!I2C_WaitAck()){I2C_Stop(); return FALSE1;}
    I2C_SendByte(ReadAddress);        //     
    I2C_WaitAck();
    I2C_Stop();                       //selectable
    I2C_Start();                      
    I2C_SendByte(DeviceAddress | 0x01);
    I2C_WaitAck();
    rec=I2C_ReceiveByte();
    I2C_WaitAck();
    I2C_Stop();
    return rec;
}


/*********************************************************************************************************/

// I2C ???????
uint8_t I2C_ReadBuffer(uint8_t* pBuffer,   int length,     int ReadAddress,  int DeviceAddress)
{		
    if(length == 0)
    return FALSE1;
	//	I2C_Start();
    if(!I2C_Start())return FALSE1;
    I2C_SendByte(DeviceAddress & 0xFE);//???? 
    if(!I2C_WaitAck()){I2C_Stop(); return FALSE1;}
    I2C_SendByte(ReadAddress);        //??????????      
    I2C_WaitAck();
    I2C_Stop();                       //selectable
    I2C_Start();                      
    I2C_SendByte(DeviceAddress | 0x01);
    I2C_WaitAck();
    while(length)
    {
      *pBuffer = I2C_ReceiveByte();
      if(length == 1)I2C_NoAck();
      else I2C_Ack(); 
      pBuffer++;
      length--;
    }
    I2C_Stop();
    return TRUE1;
}
