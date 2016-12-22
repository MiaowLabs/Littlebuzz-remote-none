/********************************************************************
作者：Songyimiao
建立日期: 20151129
版本：V2.0
喵呜实验室版权所有
/********************************************************************/
#include "includes.h"

/***************************************************************
** 作　  者: Songyimiao
** 官    网：http://www.miaowlabs.com
** 淘    宝：http://miaowlabs.taobao.com
** 日　  期: 2015年11月29日
** 函数名称: Timer1_Update
** 功能描述: 125hz中断服务函数            
** 输　  入:   
** 输　  出:   
** 备    注: 
********************喵呜实验室版权所有**************************
***************************************************************/
unsigned short SoftTimer[5]={0,0,0,0,0};

void Timer1_Update(void) interrupt  3		//125hz
{ 
	if(SoftTimer[0])SoftTimer[0]--;
	if(SoftTimer[1])SoftTimer[1]--;
	if(SoftTimer[2])SoftTimer[2]--;
	if(SoftTimer[3])SoftTimer[3]--;
	if(SoftTimer[4])SoftTimer[4]--;
}


				 