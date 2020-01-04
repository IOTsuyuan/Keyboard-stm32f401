
/*******************************************************************************
*File Name          : 2124_i2c_.h 
*Author             : MCD Application Team 
* Version            : V2.0.1 
* Date               : 06/10/2015
* Description        : Header for i2c_ee.c module 
********************************************************************************/ 
/* Define to prevent recursive inclusion ------------------------------------ */ 
 #ifndef __I2C_H 
 #define __I2C_H 

/* Includes ------------------------------------------------------------------*/ 
#include "stm32f10x.h"
#include "main.h"
/* Exported types ------------------------------------------------------------*/ 
/* Exported constants --------------------------------------------------------*/ 


/* Exported macro ------------------------------------------------------------*/ 
/* Exported functions ------------------------------------------------------- */ 


#define TRUE1	1
#define FALSE1 0
#define FALSE2 2

#define SCL_H         GPIOB->BSRR = GPIO_Pin_6 
#define SCL_L         GPIOB->BRR  = GPIO_Pin_6  
    
#define SDA_H         GPIOB->BSRR = GPIO_Pin_7
#define SDA_L         GPIOB->BRR  = GPIO_Pin_7 

#define SCL_read      GPIOB->IDR  & GPIO_Pin_6 
#define SDA_read      GPIOB->IDR  & GPIO_Pin_7 

//#define LEDG_H         GPIOB->BSRR = GPIO_Pin_14 //???????
//#define LEDG_L        GPIOB->BRR  = GPIO_Pin_14 

#define SDB_H         GPIOB->BSRR = GPIO_Pin_15 
#define SDB_L         GPIOB->BRR = GPIO_Pin_15

#define MISO_H         GPIOA->BSRR = GPIO_Pin_6 
#define MISO_L         GPIOA->BRR = GPIO_Pin_6 
//   I2C  Æ÷¼þµØÖ·
#define Addr_GND_GND  0xA0
#define Addr_GND_SCL  0xA2
#define Addr_GND_SDA  0xA4
#define Addr_GND_VCC  0xA6
#define Addr_SCL_GND  0xA8
#define Addr_SCL_SCL  0xAA
#define Addr_SCL_SDA  0xAC
#define Addr_SCL_VCC  0xAE
#define Addr_SDA_GND  0xB0
#define Addr_SDA_SCL  0xB2
#define Addr_SDA_SDA  0xB4
#define Addr_SDA_VCC  0xB6
#define Addr_VCC_GND  0xB8
#define Addr_VCC_SCL  0xBA
#define Addr_VCC_SDA  0xBC
#define Addr_VCC_VCC  0xAE
#define Addr_GND 0xE8//3731
void I2C_GPIO_Initial(void);
void delay_ms(uint32_t t);
void I2C_delay_us(int us);
uint8_t I2C_WriteByte(int DeviceAddress, int WriteAddress, int SendByte);
uint8_t I2C_ReceiveByte(void);
uint8_t I2C_ReadByte(int DeviceAddress,int ReadAddress);
uint8_t I2C_ReadBuffer(uint8_t* pBuffer, int length,int ReadAddress,int DeviceAddress);
uint8_t I2C_BufferWrite(uint8_t* pBuffer,int length,int WriteAddress,int DeviceAddress);
uint8_t I2C_Test(uint8_t DeviceAddress);
void All_LED_OFF(void);
void PIN_GPIO_Config_MISO(GPIOMode_TypeDef num1);
#endif /* __2124_I2C_H */ 

