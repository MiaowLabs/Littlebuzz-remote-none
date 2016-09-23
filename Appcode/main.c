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
unsigned char temp1,temp2;

//unsigned char idata TxBuf[32]={0};
//unsigned char idata RxBuf[32]={0};

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

	//CLK_DIV_1();	  //设置MCU工作频率为内部RC时钟
	DriversInit();
	BELL=1;
	Delaynms(100);
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
	
	Delaynms(10);
	ON_LED1	;
	
	while(1)
	{  
		TxBuf[0]++;
		g_Leftx= GetADCResult(2); //yaw				
		Delaynms(10);
		g_Lefty= GetADCResult(3); //油门 				
		Delaynms(10);								
		g_Righty=GetADCResult(5);			
    	Delaynms(10);
		g_Rightx=GetADCResult(4);   			
		Delaynms(10);
		
		//Delaynms(200);
		//BELL=1;
		//Delaynms(200);
	//失控：TxBuf[0]
	//油门：TxBuf[1]
    //俯仰：TxBuf[2]
    //横滚：TxBuf[3]
	 //Yaw：TxBuf[4]
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
//		g_Lefty=0.5*g_Lefty_Last+0.5*g_Lefty;
//		g_Lefty_Last= g_Lefty;
		TxBuf[1]=g_Lefty;  //油门通道不需处理，直接发送AD检测的8位数据

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
		
	  	nRF24L01_TxPacket(TxBuf);//发射数据

		Delaynms(50);
		check();
	
			 
#if 0//DEBUG_UART  //调试启用 预编译命令

   	OutData[0] = GetADCResult(2);	 
   	OutData[1] = GetADCResult(3);	 
   	OutData[2] = GetADCResult(4);	
   	OutData[3] = GetADCResult(5);  	
   	OutPut_Data();		
		 	  
#endif	 		
					
	}
}
