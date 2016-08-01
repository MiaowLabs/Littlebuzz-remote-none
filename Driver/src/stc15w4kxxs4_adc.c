#define __STC15W4KxxS4_ADC_C__
// ==================================================================


// 包涵头文件
// ==================================================================
#include	"stc15w4kxxs4.h"
// ==================================================================


// ======================================================================================================================
// ======================================================================================================================



#if (TEST_ADC && USE_ADC)
/********************************************************************************
* 函数名:	TestAdc
* 描  述:	ADC测试程序
* 参  数:	无
* 返回值:	无
* 版  本:	V1.0
* 日  期:	2015-09-11
* 作  者:	zenghouyun
* 备  注:	测试ADC，在主程序中调用
********************************************************************************/
void TestAdc(void)
{
	uchar *_pAdcTestBuf;
	uchar _Error, _AdcChannel;	
	sADC_InitTypeDef * _spAdcStruct;
	
	_AdcChannel	= ADC_2|ADC_3|ADC_4|ADC_5|ADC_6|ADC_7;	// 需要工作的ADC通道，B0~B7共8位，可同时选择多位。ADC_0/ADC_1/ADC_2/ADC_3/ADC_4/ADC_5/ADC_6/ADC_7。

	_spAdcStruct->ADC_ResultAdj	= HIGH_8B;		// ADC转换值调整方式，HIGH_8B(高8位 低2位)/HIGH_2B(高2位 低8位)。
	_spAdcStruct->ADC_Interrupt	= ENABLE;		// ADC中断使能，	DISABL(关闭)/ENABLE(使能)。
	_spAdcStruct->ADC_Priority	= PRIORITY_L;	// ADC中断优先级, PRIORITY_L(低)/PRIORITY_H(高)。
	_spAdcStruct->ADC_SlewRate	= SPEED_FAST;	// ADC转换的速度，0~3共四档。SPEED_LOW(最慢)/SPEED_SLOW(慢)/SPEED_FAST(快)/SPEED_SOON(最快)。
	
	_Error = InitializeADC(_AdcChannel,_spAdcStruct);	// 初始化ADC模块
	if (_Error)
	{
		// 出错报警处理
		_Error = 0;
	}
	
	_pAdcTestBuf = &sAdcValue.ResultBuf;				// 赋地缓冲器的址指针值
	
	_Error = GetAdcValue(_pAdcTestBuf, 2);				// 人工查询ADC	
	if (_Error)
	{
		// 出错报警处理
		_Error = 0;
	}
	
	AdcRunControl(0);		// 控制ADC模块运行状态
	AdcPowerControl(0);		// 控制ADC模块电源开关	
}
#endif



#if (USE_ADC)
/********************************************************************************
* 函数名:	InitializeADC
* 描  述:	初始化ADC
* 参  数:	ADC_Channel						需要工作的ADC通道，B0~B7共8位，可同时选择多位。	ADC_0/ADC_1/ADC_2/ADC_3/ADC_4/ADC_5/ADC_6/ADC_7。
*			__spAdcStruct->ADC_ResultAdj	ADC转换值调整方式，	HIGH_8B(高8位 低2位)/HIGH_2B(高2位 低8位)。
*			__spAdcStruct->ADC_Interrupt	ADC中断使能，	DISABL(关闭)/ENABLE(使能)。
*			__spAdcStruct->ADC_Priority		ADC中断优先级, 	PRIORITY_L(低)/PRIORITY_H(高)。
*			__spAdcStruct->ADC_SlewRate		ADC转换的速度，	0~3共四档。SPEED_LOW(最慢)/SPEED_SLOW(慢)/SPEED_FAST(快)/SPEED_SOON(最快)。
* 返回值:	0:初始化成功，1:ADC通道号错误，2:参数错误
* 版  本:	V1.0
* 日  期:	2015-09-10
* 作  者:	zenghouyun
* 备  注:	程序中参考了STC的资料及代码
********************************************************************************/
uchar InitializeADC(uchar __AdcChannel, sADC_InitTypeDef *__spAdcStruct)
{
	uchar _AdcSpeed;
	
	// 检查设置的通道号有没有错误
	if (__AdcChannel != 0)
	{
		if (__AdcChannel & (~ADC_PASSAGE))		return 1;	// 使用了未开通的通道，返回错误代码1
	}
	if (__spAdcStruct->ADC_SlewRate & ~0x60)	return 2;	// ADC转换的速度设置错误
	
	P1ASF = __AdcChannel;						// 设置P1口(P1.0~P1.7)为ADC输入端口
	sAdcValue.InitChannel = __AdcChannel;		// ADC所有需要转换的通道，1为需要转换的通道，0为不转换通道
	// ------------------------------------------

	if (__AdcChannel & BIT0)	{ P0M1 |=  0x01;	P0M0 &= ~BIT0; }	// 设置端口为(10)浮空输入模式
	if (__AdcChannel & BIT1)	{ P0M1 |=  0x02;	P0M0 &= ~BIT1; }
	if (__AdcChannel & BIT2)	{ P0M1 |=  0x04;	P0M0 &= ~BIT2; }
	if (__AdcChannel & BIT3)	{ P0M1 |=  0x08;	P0M0 &= ~BIT3; }
	if (__AdcChannel & BIT4)	{ P0M1 |=  0x10;	P0M0 &= ~BIT4; }
	if (__AdcChannel & BIT5)	{ P0M1 |=  0x20;	P0M0 &= ~BIT5; }
	if (__AdcChannel & BIT6)	{ P0M1 |=  0x40;	P0M0 &= ~BIT6; }
	if (__AdcChannel & BIT7)	{ P0M1 |=  0x80;	P0M0 &= ~BIT7; }
	
	_AdcSpeed = __spAdcStruct->ADC_SlewRate;	// ADC转换速度
	sAdcValue.ConvertSpeed = _AdcSpeed;
	
	// ------------------------------------------
	if (__spAdcStruct->ADC_ResultAdj)	CLK_DIV |=  ADRJ;		// 1:ADC_RES[1:0]存放高2位值，ADC_RESL[7:0]存放低8位值
	else								CLK_DIV &= ~ADRJ;		// 0:ADC_RES[7:0]存放高8位值，ADC_RESL[1:0]存放低2位值
	
    ADC_RES = 0;	// 清除ADC结果寄存器，高字节
	ADC_RESL = 0;	// 清除ADC结果寄存器，低字节
	ADC_CONTR = 0;	// 清除ADC控制寄存器的设置
	
	if (__AdcChannel == 0x00)				// 测内部BandGap参考电压
	{
		EADC = 0;							// 关闭ADC中断
		ADC_CONTR = ADC_POWER | _AdcSpeed;	// ADC电源，转换频率
	}
	else
	{
		if (__spAdcStruct->ADC_Interrupt)	// ADC中断方式
		{
			if (__spAdcStruct->ADC_Priority)	PADC = 1;	// 高中断优先级
			else								PADC = 0;	// 低中断优先级
			ADC_CONTR = ADC_POWER | _AdcSpeed | \
						ADC_START | __AdcChannel;			// ADC电源，转换频率，A/DC开始转换，转换的道号(0~7)
		}
		else									// ADC查询方式
		{
			EADC = 0;							// 关闭ADC中断
			ADC_CONTR = ADC_POWER | _AdcSpeed;	// ADC电源，转换频率
		}
	}	
    DelayAdc(2);                      			// ADC上电并延时
	
	if (__spAdcStruct->ADC_Interrupt) EADC = 1;	// 使能ADC中断
		
	return 0;
}
#endif



#if (USE_ADC)
/********************************************************************************
* 函数名:	GetAdcValue
* 描  述:	查询方式读取ADC结果
* 参  数:	*__pResultBuf	保存ADC结果的数组地址的指针，存储的地址自动计算，每个使用的通道占三个字节长度(通道号，结果高字节，结果低字节)
* 			__Channel		通道号,0-7:测ADC端口(0-7)，8:测内部BandGap参考电压
* 返回值:	错误代码 0:无错误，1:输入的通道号错误，2:此通道没有开通ADC功能。
* 版  本:	V1.0
* 日  期:	2015-09-16
* 作  者:	zenghouyun
* 备  注:	程序中参考了STC的资料及代码
********************************************************************************/
uchar GetAdcValue(uchar *__pResultBuf, uchar __Channel)
{
    uchar _Eadc;
	uchar _ChPosition = 0x01;
	uchar _CurrentCh = 0;
	
	if (__Channel > 8)							return 1;	// 输入的通道号参数错误
	if (_ChPosition & ~sAdcValue.InitChannel)	return 2;	// 此通道在ADC初始化时没有被开通ADC功能
	
	_Eadc = EADC;				// 暂存ADC中断状态
	EADC = 0;					// 关闭ADC中断

	if (__Channel < 8)			// 需要采集的ADC通道号0~7
	{
		// 每一个通道占三个字节，开通的通道会自动计算存储地址。可以根据情况注释掉此段代码。
		// -------------------------------------------------------------------------
		if (_CurrentCh < __Channel)		// 存储单元的地址移到相对应的位置
		{
			_CurrentCh++;
			_ChPosition <<= 1;
			if (_ChPosition & sAdcValue.InitChannel)
				__pResultBuf += 3;					// 如果此通道，存储单元的地址向后移3个单元
		}
		// -------------------------------------------------------------------------
		ADC_CONTR = ADC_POWER | ADC_START | (sAdcValue.ConvertSpeed & 0x60) | __Channel;	// ADC电源，A/DC开始转换，转换频率，转换的道号(0~7)
	}
	else							// 检测第9通道，内部BandGap参考电压
	{
		// 每一个通道占三个字节，开通的通道会自动计算存储地址。可以根据情况注释掉此段代码。
		// -------------------------------------------------------------------------
		if (_CurrentCh < 7)			// 存储单元的地址移到最后的3个单元位置
		{
			_CurrentCh++;
			_ChPosition <<= 1;
			if (_ChPosition & sAdcValue.InitChannel)
				__pResultBuf += 3;					// 如果此通道，存储单元的地址向后移3个单元
		}
		// -------------------------------------------------------------------------
		P1ASF = 0;
		ADC_CONTR = ADC_POWER | ADC_START | (sAdcValue.ConvertSpeed & 0x60);	// ADC电源，A/DC开始转换，转换频率
	}
	
	NOP(8);								// 等待4个NOP@11.0592MHz
	while (!(ADC_CONTR & ADC_FLAG));	// 等待ADC转换完成
	ADC_CONTR &= ~ADC_FLAG;				// 清除ADC中断标志
	
	*__pResultBuf++ = __Channel;		// 保存ADC通道号
	*__pResultBuf++ = ADC_RES;			// 读取ADC结果寄存器，高字节
	*__pResultBuf++ = ADC_RESL;			// 读取ADC结果寄存器，低字节
	
	if (__Channel == 8) P1ASF = sAdcValue.InitChannel;
	
	EADC = _Eadc;		// 恢复ADC中断状态
    return 0;			// 无错
}
#endif



#if (USE_ADC)
/********************************************************************************
* 函数名:	AdcPowerControl
* 描  述:	ADC模块电源开关控制
* 参  数:	__Switch	0:关闭ADC模块电源，1:打开ADC模块电源
* 返回值:	无
* 版  本:	V1.0
* 日  期:	2015-09-16
* 作  者:	zenghouyun
* 备  注:	无
********************************************************************************/
void AdcPowerControl(uchar __Switch)
{
	if (__Switch)	ADC_CONTR |=  ADC_POWER;	// 打开ADC模块电源
	else			ADC_CONTR &= ~ADC_POWER;	// 关闭ADC模块电源
}
#endif



#if (USE_ADC)
/********************************************************************************
* 函数名:	AdcRunCountrol
* 描  述:	ADC模块运行状态控制
* 参  数:	__RunSate	0:ADC停止转换，1:开始运行，启动ADC转换
* 返回值:	无
* 版  本:	V1.0
* 日  期:	2015-09-16
* 作  者:	zenghouyun
* 备  注:	无
********************************************************************************/
void AdcRunControl(uchar __Switch)
{
	if (__Switch)	ADC_CONTR |=  ADC_START;	// ADC模块开始运行
	else			ADC_CONTR &= ~ADC_START;	// ADC模块停止运行
}
#endif



#if (USE_ADC)
/********************************************************************************
* 函数名:	ADC_Routine
* 描  述:	ADC中断服务程序
* 参  数:	无
* 返回值:	无
* 版  本:	V1.0
* 日  期:	2015-09-10
* 作  者:	zenghouyun
* 备  注:	程序中参考了STC的资料及代码
********************************************************************************/
void ADC_Routine(void)			interrupt ADC_VECTOR		// 查询次序: 05	中断向量地址: 002BH	中断源: ADC(模转数)
{
	static uchar _ChPosition=0x01;		// 前前ADC通道号的位置(0x01~0x80)
	static uchar _ChNumber=0;			// 当前的ADC通道号(0~7)
	static uchar *_pResultBuf;

	ADC_CONTR &= ~ADC_FLAG;				// 清除ADC中断标志
    
	if (_ChNumber > 7)
	{
		_ChNumber = 0;							// 切换到第一个通道
		_ChPosition = 0x01;						// 前前ADC通道号的位置(0x01~0x80)
		_pResultBuf = &sAdcValue.ResultBuf;		// 赋地缓冲器的址指针值
	}
	
	for (_ChNumber=0; _ChNumber<7; _ChNumber++)
	{
		if (_ChPosition & sAdcValue.InitChannel)	// 通道有开通ADC功能
		{
			*_pResultBuf++ = _ChNumber;		// 读取当前的ADC通道号
			*_pResultBuf++ = ADC_RES;		// 读取ADC结果寄存器，高字节
			*_pResultBuf++ = ADC_RESL;		// 显示ADC结果寄存器，低字节
			
			ADC_CONTR = ADC_POWER | ADC_START | sAdcValue.ConvertSpeed | _ChNumber;	// ADC电源，A/DC开始转换，转换频率，转换的道号(0~7)
		}
		_ChPosition<<=1;					// 没开通ADC功能转到下一个通道
	}
}
#endif



#if (USE_ADC)
/********************************************************************************
* 函数名:	DelayAdc
* 描  述:	初初化ADC用软件延时程序
* 参  数:	__Count		延时时间值
* 返回值:	无
* 版  本:	V1.0
* 日  期:	2015-09-10
* 作  者:	zenghouyun
* 备  注:	程序中参考了STC的资料及代码
********************************************************************************/
void DelayAdc(uint __Count)
{
    uint i;

    while (__Count--)
    {
        i = 5000;			// i=5000@11.0592MHz
        while (i--);
    }
}
#endif
