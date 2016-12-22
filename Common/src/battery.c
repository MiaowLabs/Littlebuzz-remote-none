#include "includes.h"

static char LittleBuzzLowPowerAlarm=0;


float RemoteBatteryChecker(void)
{
	float fValue;
	fValue = GetADCResult(1);	 				//参考电压5.02V 检测max4.3V min3.0V
	fValue = fValue / 256.0 * 5.02 ;	 			
	return fValue;
}

extern char RxBuf[];
								 
/*
	满足以下条件即告警标志置1
	1、连续检测到10次电压低于3.1V，
	2、NRF数据传输正常以及遥控器解锁

	建议调用周期 500ms
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
	遥控器上锁或nrf数据传输停止2秒以上将停止低压告警
	
	建议调用周期 250ms
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


