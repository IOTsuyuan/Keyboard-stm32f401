/**
  ******************************************************************************
  * @file    main.h
  * $Author: wdluo $
  * $Revision: 67 $
  * $Date:: 2012-08-15 19:00:29 +0800 #$
  * @brief   主函数包含的头文件.
  ******************************************************************************
  * @attention
  *
  *<h3><center>&copy; Copyright 2009-2012, ViewTool</center>
  *<center><a href="http:\\www.viewtool.com">http://www.viewtool.com</a></center>
  *<center>All Rights Reserved</center></h3>
  * 
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_conf.h"

/*choose I2C buand Rate*/
//#define I2C_Delay_Time 3 //920K
#define I2C_Delay_Time 7  //370K
//#define I2C_Delay_Time 10   //224K
#define I2C_Delay_Time2 I2C_Delay_Time*2
/*choose IC promgram*/
#define VERSION 5

#if  VERSION==1
#include "IS31FL3733.h"
#elif VERSION==2
#include "IS31FL3736.h"
#elif VERSION==3
#include "IS31FL3737.h"
#elif VERSION==4
#include "IS31FL3731.h"
#elif VERSION==5
#include "IS31FL3732.h"
#endif
#endif/* __MAIN_H */

/*********************************END OF FILE**********************************/
