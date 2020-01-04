/**
  ******************************************************************************
  * @file    main.c
  * $Author: wdluo $
  * $Revision: 67 $
  * $Date:: 2012-08-15 19:00:29 +0800 #$
  * @brief   ������.
  ******************************************************************************
  * @attention
  *
  *<h3><center>&copy; Copyright 2009-2012, ViewTool</center>
  *<center><a href="http:\\www.viewtool.com">http://www.viewtool.com</a></center>
  *<center>All Rights Reserved</center></h3>
  * 
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include <stm32f10x.h>
#include "main.h"
#include "exti.h"
#include "adc.h"
#include "SysTick.h"
#include "Time_test.h"
#include "usb_lib.h"
#include "hw_config.h"
#include "usbio.h"
#include "I2C.h"
//�޸����صĳ���ʱֻ��Ҫ��main.h�����޸ľͿ���
extern uint8_t USB_Received_Flag;  
uint8_t G_Demo_NO,Key_Bit,I2C_DATA [64],data[64];
typedef enum MsgFlags {None,Write,Read,I2C,SPI,Environment,ReadAll,LoadDiag,Reset,MuteAll,HizAll,PlayAll,Channel,Fsw,Custom_Write,Custom_Read}MsgFlags;
MsgFlags msgFlags;
int main(void)
{
	SysTick_Init();
	I2C_GPIO_Initial();//
	USB_Interrupts_Config();//	
	Set_USBClock();// 
	USB_Init();//
	SDB_H;
	EXTI_PB0_Config();
	#if  VERSION==1    //choose IC
	IS31FL3733_Init();
	#elif VERSION==2
	IS31FL3736_Init();
	#elif VERSION==3
	IS31FL3737_Init();
	#elif VERSION==4
	IS31FL3731_Init();
	#elif VERSION==5
	IS31FL3732_Init();
	#endif
	TIM2_NVIC_Configuration();
	TIM2_Configuration();
	STOP_TIME;
	Key_Bit=1;
  G_Demo_NO=1;
	while(1)	{	
	  	if(USB_Received_Flag)
				{
			    USB_Received_Flag=0;
					Key_Bit=0;
          USB_GetData(data,sizeof(data));	
					#if  VERSION==1
			    handle_IS31FL3733();
					data[1]=1;
					#elif VERSION==2
			    handle_IS31FL3736();
					data[1]=2;
					#elif VERSION==3
			    handle_IS31FL3737();
					data[1]=4;
					#elif VERSION==4
          handle_IS31FL3731();
					data[1]=5;
					#elif VERSION==5
          handle_IS31FL3732();
					data[1]=6;
					#endif
          USB_SendData(data,sizeof(data));	
         }	
 				 
			if(Key_Bit==1)//play demo mode
			{
				 START_TIME;
					#if  VERSION==1
			    Play_IS31FL3733_Demo_mode();
					#elif VERSION==2
			    Play_IS31FL3736_Demo_mode();
					#elif VERSION==3
  		    Play_IS31FL3737_Demo_mode();
					#elif VERSION==4
  		    Play_IS31FL3731_Demo_mode();
					#elif VERSION==5
  		    Play_IS31FL3732_Demo_mode();
					#endif
				 STOP_TIME;
			}
 }
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  �����ڼ�������������ʱ��Դ�ļ����ʹ�������
  * @param  file Դ�ļ���
  * @param  line ������������ 
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
    /* �û����������Լ��Ĵ������ڱ��������ļ�������������,
       ���磺printf("�������ֵ: �ļ��� %s �� %d��\r\n", file, line) */

    /* ����ѭ�� */
    while (1)
    {
			
    }
}
#endif

/*********************************END OF FILE**********************************/
