#include "includes.h"
#include "bmp.h"


extern unsigned char g_Lock;

void ShowLOGO(void)
{
	OLED_DrawBMP(0,0,128,8,LOGO);  //图片显示
}

void ShowBattery(void)
{
	float batVolt=0;

	batVolt =  RemoteBatteryChecker();
	if (batVolt > 3.0)
		OLED_DrawConvertBMP(112, 0, 128, 2, BAT_100_BMP);
	else if (batVolt > 2.8)		
		OLED_DrawConvertBMP(112, 0, 128, 2, BAT_80_BMP);
	else if (batVolt > 2.6)
		OLED_DrawConvertBMP(112, 0, 128, 2, BAT_60_BMP);
	else if (batVolt > 2.4)
		OLED_DrawConvertBMP(112, 0, 128, 2, BAT_40_BMP);
	else if (batVolt > 2.2)
		OLED_DrawConvertBMP(112, 0, 128, 2, BAT_20_BMP);
	else
		OLED_DrawConvertBMP(112, 0, 128, 2, BAT_00_BMP);
}


void ShowLockStat(void)
{
	if(g_Lock == 0){
		OLED_DrawConvertBMP(112, 2, 128, 4, UNLOCK_BMP);
	}
	else 
		OLED_DrawConvertBMP(112, 2, 128, 4, LOCK_BMP);
}

void ShowRuning(void)
{
	static char i = 0;
	
	OLED_DrawConvertBMP(112, 4, 128, 6, RUN_BMP[i]);

	i++;
	if (i >= 4) i = 0;
}

void ShowHomePageInit(void)
{
	OLED_ShowString(0, 0, "Roll:  0.0    ");
	OLED_ShowString(0, 2, "Pitch: 0.0    ");
	OLED_ShowString(0, 4, "Yaw:   0.0    ");
	OLED_ShowString(0, 6, "Power: 0.0V   ");
	ShowBattery();
	ShowLockStat();
	ShowRuning();
	OLED_DrawBMP(112, 6, 128, 8, BLACK_FILL_BMP);
}

extern char RxBuf[];
void ShowHomePage(void)
{
	float ftemp = 0;
	char buff[16];
	static unsigned char  AlarmCnt = 0;
	static char step = 0;

	step++;
	if(step >= 4)step = 0;

	//分步执行，缩短单次刷屏时间
	if(step == 0){
		ftemp = (float)RxBuf[1]/1.0; // Roll
		sprintf(buff, "Roll:  %.1f    ", ftemp);
		buff[14] = '\0';
		OLED_ShowString(0, 0, buff);

		ShowBattery();
	}

	if(step == 1){
		ftemp= (float)RxBuf[2]/1.0;	//	Pitch
		sprintf(buff, "Pitch: %.1f    ",ftemp);
		buff[14] = '\0';
		OLED_ShowString(0, 2, buff);

		ShowLockStat();
	}

	if(step == 2){
		ftemp=(float)RxBuf[0]/10.0;	// Power
		sprintf(buff, "Power: %.1fV    ",ftemp);
		buff[14] = '\0';

		if (IsLittleBuzzLowPowerAlarm())
		{
			AlarmCnt++;
			if (AlarmCnt >= 5 ){
				if (AlarmCnt >= 10)AlarmCnt = 0;
				OLED_ShowString(0, 6, "Power:        ");
			}
			else
				OLED_ShowString(0, 6, buff);	
		}
		else
			OLED_ShowString(0, 6, buff);
		
	}
	
	if(step == 3){
		OLED_ShowString(0, 4, "Yaw:   0.0    ");
		OLED_DrawBMP(112, 6, 128, 8, BLACK_FILL_BMP);
	}

	ShowRuning();

}


