
#include "adc.h"
#include "delay.h"
#include "intrins.h"

void ADCInit()
{
	P1ASF|=0x3C;	  //设置P1.2-P1.5为AD口
	ADC_RES=0;	  //清除结果寄存器
	ADC_CONTR = ADC_POWER | ADC_SPEEDLL;	//20M/540=37kHz转换速度

	Delaynms(10); //适当延时
}

/*----------------------------
读取ADC结果
----------------------------*/
unsigned char GetADCResult(unsigned char ch)
{
    ADC_CONTR = ADC_POWER | ADC_SPEEDLL | ch | ADC_START;
    _nop_();                        //等待4个NOP
    _nop_();
    _nop_();
    _nop_();
    while (!(ADC_CONTR & ADC_FLAG));//等待ADC转换完成
    ADC_CONTR &= ~ADC_FLAG;         //Close ADC

    return ADC_RES;                 //返回ADC结果
}




