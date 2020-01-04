#ifndef __IS31FL3732_H 
#define __IS31FL3732_H 

#include "main.h"

#define Addr_GND_GND  0xA0

void IS31FL3732_Init(void);
void Test_Led(void);
void IS31FL3732_Global_Current(uint8_t dat);
void Play_IS31FL3732_Demo_mode(void);
void IS31FL3732_PWM_ALL_ON(void);
void IS31FL3732_PWM_ALL_OFF(void);
void IS31FL3732_Reset_Pwm_Value(void);
void IS31FL3732_Brightness_Level(uint8_t dat);
void IS31FL3732_Audio_Frame_Play_Mode(uint8_t dat);
void IS31FL3732_Audio_Synchronization_(uint8_t dat);
void IS31FL3732_Audio_AGC_Enable(uint8_t dat);
void IS31FL3732_Audio_AGC_FastMode(uint8_t dat);
void IS31FL3732_Audio_AGC_Gain(uint8_t dat);
void IS31FL3732_Audio_ADC_Rate(uint8_t dat);
void Play_IS31FL3732_Demo_mode(void);
void handle_IS31FL3732(void);
void IS31FL3732_Audio_mode(void);
#endif 
