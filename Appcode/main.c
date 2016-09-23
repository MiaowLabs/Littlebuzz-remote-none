/********************************************************************
���ߣ�Songyimiao
��������: 20151129
�汾��V2.0
����ʵ���Ұ�Ȩ����
/********************************************************************/
#include "includes.h"
int g_Rightx;g_Righty,g_Lefty,g_Leftx;
int g_RxOffset,g_RyOffset,g_LxOffset;
int g_Rx,g_Ry;g_Ly;
unsigned char temp1,temp2;

//unsigned char idata TxBuf[32]={0};
//unsigned char idata RxBuf[32]={0};

/***************************************************************
** ����  ��: Songyimiao
** ��    ����http://www.miaowlabs.com
** ��    ����http://miaowlabs.taobao.com
** �ա�  ��: 2015��11��29��
** ��������: main()
** ��������: ������            
** �䡡  ��:   
** �䡡  ��:   
** ��    ע: 
********************����ʵ���Ұ�Ȩ����**************************
***************************************************************/
void main()
{
	DisableInterrupts;//��ֹ���ж�

	//CLK_DIV_1();	  //����MCU����Ƶ��Ϊ�ڲ�RCʱ��
	DriversInit();
	BELL=1;
	Delaynms(100);
	BELL=0;		
	ADCInit();				
	SW1=SW2=SW3=SW4=SW5=SW6=SW10=SW11=1;
	Delaynms(10);
	g_RxOffset=GetADCResult(5)-128;  //0-255
    Delaynms(10);
	g_RyOffset=GetADCResult(4)-128;  //��¼�ϵ�ʱҡ�˵�������Ϊ��λ��������Ϊҡ����λҪΪ128��256/2      
	Delaynms(10);
	g_LxOffset=GetADCResult(2)-128;	 
	Delaynms(10);
	while(NRF24L01_Check())//��ⲻ��24L01
	{
		Delaynms(500);
		ON_LED1;;  
		Delaynms(500);
		OFF_LED1;; 
	}
	init_NRF24L01();	 //��ʼ��nRF24L01
	
	Delaynms(10);
	ON_LED1	;
	
	while(1)
	{  
		TxBuf[0]++;
		g_Leftx= GetADCResult(2); //yaw				
		Delaynms(10);
		g_Lefty= GetADCResult(3); //���� 				
		Delaynms(10);								
		g_Righty=GetADCResult(5);			
    	Delaynms(10);
		g_Rightx=GetADCResult(4);   			
		Delaynms(10);
		
		//Delaynms(200);
		//BELL=1;
		//Delaynms(200);
	//ʧ�أ�TxBuf[0]
	//���ţ�TxBuf[1]
    //������TxBuf[2]
    //�����TxBuf[3]
	 //Yaw��TxBuf[4]
		g_Rightx=255-g_Rightx;	   //���Ҿ���
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
		TxBuf[1]=g_Lefty;  //����ͨ�����账��ֱ�ӷ���AD����8λ����

		if(SW1==0){
			TxBuf[5]=1;}
			else{
			TxBuf[5]=0;}	 //����TxBuf[5]
		if(SW2==0){		
			TxBuf[6]=1;}
			else{
			TxBuf[6]=0;}	 //����TxBuf[6]
		if(SW3==0){
			TxBuf[7]=1;}	
			else{
			TxBuf[7]=0;}	 //����TxBuf[7]
		if(SW4==0){
			TxBuf[8]=1;}
			else{
			TxBuf[8]=0;}	 //����TxBuf[8]
		if(SW5==0){
			TxBuf[9]=1;}
			else{
			TxBuf[9]=0;}	 //����TxBuf[9]
		if(SW6==0){
			TxBuf[10]=1;}
			else{
			TxBuf[10]=0;}	 //����TxBuf[10]
		if(SW10==0){
			TxBuf[11]=1;}
			else{
			TxBuf[11]=0;}	 //����TxBuf[11]
		if(SW11==0){
			TxBuf[12]=1;}
			else{
			TxBuf[13]=0;}	 //����TxBuf[10]
		
	  	nRF24L01_TxPacket(TxBuf);//��������

		Delaynms(50);
		check();
	
			 
#if 0//DEBUG_UART  //�������� Ԥ��������

   	OutData[0] = GetADCResult(2);	 
   	OutData[1] = GetADCResult(3);	 
   	OutData[2] = GetADCResult(4);	
   	OutData[3] = GetADCResult(5);  	
   	OutPut_Data();		
		 	  
#endif	 		
					
	}
}
