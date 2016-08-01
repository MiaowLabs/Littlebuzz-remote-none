/********************************************************************
作者：Songyimiao
建立日期: 20151129
版本：V2.0
喵呜实验室版权所有
/********************************************************************/
#ifndef   _IO_CONFIG_H_ 
#define   _IO_CONFIG_H_

#include "IAP15W4K61S4.h"

/********************************************************************
MCU硬件相关
*********************************************************************/

/******Target CPU相关宏定义******/
#define	DisableInterrupts	EA=0
#define	EnableInterrupts	EA=1

#define DEBUG_UART  0

#define IF_CAR_FALL 0

#define CLK_DIV_1() CLK_DIV |= 0x00 /*主时钟频率/1，不分频，等于内部RC时钟*/
/*
	  CLKS2 CLKS1 CLKS0         分频后CPU实际工作时钟
	    0     0     0        外部晶体时钟或内部R/C振荡时钟
	    0     0     1       (外部晶体时钟或内部R/C振荡时钟)/2
	    0     1     0       (外部晶体时钟或内部R/C振荡时钟)/4
	    0     1     1       (外部晶体时钟或内部R/C振荡时钟)/8
	    1     0     0       (外部晶体时钟或内部R/C振荡时钟)/16
        1     0     1       (外部晶体时钟或内部R/C振荡时钟)/32
        1     1     0       (外部晶体时钟或内部R/C振荡时钟)/64
        1     1     1       (外部晶体时钟或内部R/C振荡时钟)/128	
*/	

//LED
sbit LED1 = P2^4;
sbit LED2 = P2^5;
sbit LED3 = P2^6;
sbit LED4 = P2^7;

//IIC
sbit SCL  = P4^6;			//I2C时钟引脚定义
sbit SDA  = P4^5;			//I2C数据引脚定义

sbit BELL=P1^6;

sbit SW1 = P5^0;
sbit SW2 = P3^4;

sbit SW3 = P3^3;
sbit SW4 = P3^2;
sbit SW5 = P2^3;
sbit SW6 = P2^2;

#endif 