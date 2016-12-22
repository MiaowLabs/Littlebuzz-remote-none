#include "includes.h"

static char LittleBuzzLowPowerAlarm=0;


float RemoteBatteryChecker(void)
{
	float fValue;
	fValue = GetADCResult(1);	 				//�ο���ѹ5.02V ���max4.3V min3.0V
	fValue = fValue / 256.0 * 5.02 ;	 			
	return fValue;
}

extern char RxBuf[];
								 
/*
	���������������澯��־��1
	1��������⵽10�ε�ѹ����3.1V��
	2��NRF���ݴ��������Լ�ң��������

	����������� 500ms
*/
extern unsigned char NRFConnectStat;
extern unsigned char g_Lock;
void LittleBuzzBatteryChecker(void)
{
	char  volt = 0;
	static unsigned char Cnt=0;
	
	volt = RxBuf[0];	// LittleBuzz battery voltage  x10

	if (volt < 31){
		Cnt++;
		if((Cnt>=10)&&(NRFConnectStat == 1)&&(g_Lock == 0))
			LittleBuzzLowPowerAlarm = 1;
	}
	else{
		Cnt = 0;
	}
}

/*
	ң����������nrf���ݴ���ֹͣ2�����Ͻ�ֹͣ��ѹ�澯
	
	����������� 250ms
*/
void LittleBuzzLowPowerBell(void)
{
	if(g_Lock == 1)
		LittleBuzzLowPowerAlarm = 0;
	if(NRFConnectStat == 0)
		LittleBuzzLowPowerAlarm = 0;
	
	if(LittleBuzzLowPowerAlarm == 1){
		BELL = ~BELL;
	}
	else{
		BELL = 0;
	}
}

int IsLittleBuzzLowPowerAlarm(void)
{
	return LittleBuzzLowPowerAlarm;
}


