/********************************************************************
作者：Songyimiao
建立日期: 20151129
版本：V2.0
喵呜实验室版权所有
/********************************************************************/
#include "includes.h"
int g_Rightx;g_Righty,g_Lefty,g_Leftx;
int g_RxOffset,g_RyOffset,g_LxOffset;
int g_Rx,g_Ry;g_Ly;

unsigned char g_Lock = 1;
unsigned char g_LockAction=0;

unsigned char NRFConnectStat = 0; // 0:nrf disconnected ,1:nrf connected
static unsigned char NRFConnectCnt = 0;
	
extern unsigned short SoftTimer[];
/***************************************************************
** 作　  者: Songyimiao
** 官    网：http://www.miaowlabs.com
** 淘    宝：http://miaowlabs.taobao.com
** 日　  期: 2015年11月29日
** 函数名称: main()
** 功能描述: 主函数            
** 输　  入:   
** 输　  出:   
** 备    注: 
********************喵呜实验室版权所有**************************
***************************************************************/
void main()
{

	DisableInterrupts;//禁止总中断

	GPIOInit();
  	Timer1Init();
	Uart1Init();
	
	OLED_Init();			//初始化OLED  
	OLED_Clear(); 
	ShowLOGO();
	Delaynms(10);

	BELL=0;	
	ADCInit();				
	SW1=SW2=SW3=SW4=SW5=SW6=SW10=SW11=1;
	Delaynms(10);
	g_RxOffset=GetADCResult(5)-128;  //0-255
    	Delaynms(10);
	g_RyOffset=GetADCResult(4)-128;  //记录上电时摇杆的数据作为中位修正，因为摇杆中位要为128即256/2      
	Delaynms(10);
	g_LxOffset=GetADCResult(2)-128;	 
	Delaynms(10);
	while(NRF24L01_Check())//检测不到24L01
	{
		Delaynms(500);
		ON_LED1;;  
		Delaynms(500);
		OFF_LED1;; 
	}
	init_NRF24L01();	 //初始化nRF24L01
	Delaynms(500);
	ShowHomePageInit();
	
	ON_LED1	;

	EnableInterrupts;

	while(1)
	{  
		g_Leftx= GetADCResult(2); //yaw				
		Delaynms(1);
		g_Lefty= GetADCResult(3); //油门 				
		Delaynms(1);								
		g_Righty=GetADCResult(5);			
    		Delaynms(1);
		g_Rightx=GetADCResult(4);   			
		Delaynms(1);
	
		g_Rightx=255-g_Rightx;	   //左右纠正
		if((g_Rightx-g_RxOffset)>=255){TxBuf[2]=255;}
		else if((g_Rightx-g_RxOffset)<=0){TxBuf[2]=0;}
		else{TxBuf[2]=g_Rightx-g_RxOffset;}
		
		if((g_Righty-g_RyOffset)>=255){TxBuf[3]=255;}
		else if((g_Righty-g_RyOffset)<=0){TxBuf[3]=0;}
		else{TxBuf[3]=g_Righty-g_RyOffset;}

		if((g_Leftx-g_LxOffset)>=255){TxBuf[4]=255;}
		else if((g_Leftx-g_LxOffset)<=0){TxBuf[4]=0;}
		else{TxBuf[4]=g_Leftx-g_LxOffset;}


		/*******************遥控器开锁和解锁*******************/
		if((g_Lefty>0xEB)&&(TxBuf[2]<0x20))
		{// lock
			if(!g_LockAction){
				g_LockAction = 1;
				SoftTimer[1] = 100;
			}
			else{
				if((!SoftTimer[1])&&(g_Lock==0)){
					g_Lock = 1;
					BELL = 1;
					Delaynms(100);	
					BELL = 0;	  
				}
			}
		}
		else  if((g_Lefty>0xEB)&&(TxBuf[2]>0xD0))
		  {// unlock
		  	if(!g_LockAction){
				g_LockAction = 1;
				SoftTimer[1] = 100;
			}
			else{
				if((!SoftTimer[1])&&(g_Lock==1)){
					g_Lock=0;
					BELL = 1;
					Delaynms(100);	
					BELL = 0;
				}
			}
		  }
		else
			g_LockAction = 0;
			
		if(g_Lock==0)
			TxBuf[1]=g_Lefty;  //油门通道不需处理，直接发送AD检测的8位数据
		else
			TxBuf[1] = 0xff;

		if(SW1==0){
			TxBuf[5]=1;}
			else{
			TxBuf[5]=0;}	 //按键TxBuf[5]
		if(SW2==0){		
			TxBuf[6]=1;}
			else{
			TxBuf[6]=0;}	 //按键TxBuf[6]
		if(SW3==0){
			TxBuf[7]=1;}	
			else{
			TxBuf[7]=0;}	 //按键TxBuf[7]
		if(SW4==0){
			TxBuf[8]=1;}
			else{
			TxBuf[8]=0;}	 //按键TxBuf[8]
		if(SW5==0){
			TxBuf[9]=1;}
			else{
			TxBuf[9]=0;}	 //按键TxBuf[9]
		if(SW6==0){
			TxBuf[10]=1;}
			else{
			TxBuf[10]=0;}	 //按键TxBuf[10]
		if(SW10==0){
			TxBuf[11]=1;}
			else{
			TxBuf[11]=0;}	 //按键TxBuf[11]
		if(SW11==0){
			TxBuf[12]=1;}
			else{
			TxBuf[13]=0;}	 //按键TxBuf[10]

		if(!SoftTimer[0]){
			SoftTimer[0] = 10;
			TxBuf[0]++;
			SetTX_Mode();
			nRF24L01_TxPacket(TxBuf); 
			Delaynms(5);
			SetRX_Mode();
	 	}
		
		if(nRF24L01_RxPacket(RxBuf))
		{
			NRFConnectCnt = 0;
			NRFConnectStat  = 1;
		}

	    /******************* 0.05s 定时任务 *******************/
		if(SoftTimer[2]==0){
			SoftTimer[2] = 5;
			ShowHomePage();
			if (NRFConnectCnt < 40) NRFConnectCnt++;
			else{
				NRFConnectStat = 0;
			}
	    }

		/****************** 0.25s 定时任务 *******************/
		if(SoftTimer[3]==0){
			SoftTimer[3] = 25;

			if(g_Lock==1)
				LED1 = ~LED1;
			else
			    LED1 = 0;
			
			LittleBuzzLowPowerBell();
		}
		
	    /******************** 0.5s 定时任务 *******************/
		if(SoftTimer[4]==0){
			SoftTimer[4] = 50;
			LittleBuzzBatteryChecker();
	    }
	}
}

