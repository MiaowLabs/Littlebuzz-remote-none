
#include "adc.h"
#include "delay.h"
#include "intrins.h"

void ADCInit()
{
	P1ASF|=0x3C;	  //����P1.2-P1.5ΪAD��
	ADC_RES=0;	  //�������Ĵ���
	ADC_CONTR = ADC_POWER | ADC_SPEEDLL;	//20M/540=37kHzת���ٶ�

	Delaynms(10); //�ʵ���ʱ
}

/*----------------------------
��ȡADC���
----------------------------*/
unsigned char GetADCResult(unsigned char ch)
{
    ADC_CONTR = ADC_POWER | ADC_SPEEDLL | ch | ADC_START;
    _nop_();                        //�ȴ�4��NOP
    _nop_();
    _nop_();
    _nop_();
    while (!(ADC_CONTR & ADC_FLAG));//�ȴ�ADCת�����
    ADC_CONTR &= ~ADC_FLAG;         //Close ADC

    return ADC_RES;                 //����ADC���
}




