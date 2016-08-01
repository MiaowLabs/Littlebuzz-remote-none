#ifndef __STC15W4KxxS4_ADC_H__
#define __STC15W4KxxS4_ADC_H__
// ==================================================================


// 包涵头文件
// ==================================================================
#include	"stc15w4kxxs4.h"

// ==================================================================





#ifdef __STC15W4KxxS4_ADC_C__

// 条件编译，当本头文件相应的.C文件调用时起作用，其它文件调用时为声明
// -------------------------------------------------------------
#define	global 				// 自己的.C文件调用时，global 相当于空。
#else						// 其它的.C调用
#define	global extern		// 在此声明为外部引用
#endif
// -------------------------------------------------------------

 
// 开始定义全局变量
// ==================================================================



// 宏定义，以下各组参数请根据具体的使用情况填写
// ==================================================================


// ADC初始化程序测试开关
#define	TEST_ADC	1		// 程序测试开关，	0:不测试，1:进行测试


// ADC通道使用开关
#define USE_ADC0	0		// ADC通道0		0:不使用，1:使用
#define USE_ADC1	0		// ADC通道1		0:不使用，1:使用
#define USE_ADC2	1		// ADC通道2		0:不使用，1:使用
#define USE_ADC3	1		// ADC通道3		0:不使用，1:使用
#define USE_ADC4	1		// ADC通道4		0:不使用，1:使用
#define USE_ADC5	1		// ADC通道5		0:不使用，1:使用
#define USE_ADC6	1		// ADC通道6		0:不使用，1:使用
#define USE_ADC7	1		// ADC通道7		0:不使用，1:使用


// 以下变量编译器会自动计算，不需要手工更改
// ==================================================================

// ---------------------------------------
#if (USE_ADC0)
	#define ADC_NM0	1
	#define ADC_PG0	(0x01)
#else
	#define ADC_NM0	0
	#define ADC_PG0	0
#endif
// ---------------------------------------
#if (USE_ADC1)
	#define ADC_NM1	1
	#define ADC_PG1	(0x02)
#else
	#define ADC_NM1	0
	#define ADC_PG1	0
#endif
// ---------------------------------------
#if (USE_ADC2)
	#define ADC_NM2	1
	#define ADC_PG2	(0x04)
#else
	#define ADC_NM2	0
	#define ADC_PG2	0
#endif
// ---------------------------------------
#if (USE_ADC3)
	#define ADC_NM3	1
	#define ADC_PG3	(0x08)
#else
	#define ADC_NM3	0
	#define ADC_PG3	0
#endif
// ---------------------------------------
#if (USE_ADC4)
	#define ADC_NM4	1
	#define ADC_PG4	(0x10)
#else
	#define ADC_NM4	0
	#define ADC_PG4	0
#endif
// ---------------------------------------
#if (USE_ADC5)
	#define ADC_NM5	1
	#define ADC_PG5	(0x20)
#else
	#define ADC_NM5	0
	#define ADC_PG5	0
#endif
// ---------------------------------------
#if (USE_ADC6)
	#define ADC_NM6	1
	#define ADC_PG6	(0x40)
#else
	#define ADC_NM6	0
	#define ADC_PG6	0
#endif
// ---------------------------------------
#if (USE_ADC7)
	#define ADC_NM7	1
	#define ADC_PG7	(0x80)
#else
	#define ADC_NM7	0
	#define ADC_PG7	0
#endif
// ---------------------------------------


#define ADC_NUMBER	(ADC_NM0 + ADC_NM1 + ADC_NM2 + ADC_NM3 + ADC_NM4 + ADC_NM5 + ADC_NM6 + ADC_NM7)	// 参与工作的ADC道通数量1~8
#define ADC_PASSAGE	(ADC_PG0 | ADC_PG1 | ADC_PG2 | ADC_PG3 | ADC_PG4 | ADC_PG5 | ADC_PG6 | ADC_PG7)	// 参与工作的ADC道通
#define USE_ADC		ADC_NUMBER

#define ADC_BUF_SIZE (ADC_NUMBER*3+3)


// ==================================================================


// PWMCFG B6: CBTADC	PWM计数器归零时(CBIF==1时)触发ADC转换。1:PWM计数器归零时自动触发ADC转换。(注:前提条件是PWM和ADC必须被使能，即ENPWM==1，且ADCON==1)
// PWMCFG B5: C7INI		设置PWM7输出端口的初始电平为低电平。0:初始电平为低电平，1:初始电平为高电平。
// PWMCFG B4: C6INI		设置PWM6输出端口的初始电平为低电平。0:初始电平为低电平，1:初始电平为高电平。
// PWMCFG B3: C5INI		设置PWM5输出端口的初始电平为低电平。0:初始电平为低电平，1:初始电平为高电平。
// PWMCFG B2: C4INI		设置PWM4输出端口的初始电平为低电平。0:初始电平为低电平，1:初始电平为高电平。
// PWMCFG B1: C3INI		设置PWM3输出端口的初始电平为低电平。0:初始电平为低电平，1:初始电平为高电平。
// PWMCFG B0: C2INI		设置PWM2输出端口的初始电平为低电平。0:初始电平为低电平，1:初始电平为高电平。

// ADC_RES			ADRJ=0时:ADC结果高8位寄存器，ADRJ=1时:ADC结果低2位寄存器
// ADC_RESL			ADRJ=0时:ADC结果高2位寄存器，ADRJ=1时:ADC结果低8位寄存器

// ADC_CONTR B7:ADC_POWER	ADC电源控制位。0:关闭ADC电源。1:打开A/D转换器电源。建议进入空闲模式和掉电模式前，将ADC电源关闭，即ADC_POWER=0，可降低功耗。启动A/D转换前一定要确认A/D电源已打开，A/D转换结束后关闭A/D电源可降低功耗，也可不关闭。初次打开内部A/D转换模拟电源，需适当延时，等内部模拟电源稳定后，再启运A/D转换。建议启A/D转换后，在A/D转换结束之前，不改变任何I/O口的状态，有利于高精度A/D转换，如能将定时器/串口/中断系统关闭更好。
// ADC_CONTR B6:SPEED1		模数转换器转换速度控制位1。
// ADC_CONTR B5:SPEED0		模数转换器转换速度控制位0。
// ADC_CONTR B4:ADC_FLAG	模数转换器转换结束标志位，当A/D转换完成后，ADC_FLAG=1，要由软件清0.不管是A/D转换完成后由该位申请产生中断，还是由软件查询该标志位A/D转换是否结束，当A/D转换完成后，ADC_FLAG=1，一定要软件清0。
// ADC_CONTR B3:ADC_START	模数转换器(ADC)转换启动控制位，设置为“1”时，开始转换，转换结束后为0。
// ADC_CONTR B2:CHS2		模拟输入通道选择位2。
// ADC_CONTR B1:CHS1		模拟输入通道选择位1。
// ADC_CONTR B0:CHS0		模拟输入通道选择位0。

// IP B5: PADC		A/D转换中断优先级控制位。

// IE B5: EADC		A/D转换中断允许位。

// CLK_DIV B5: ADRJ		ADC转换结果调整。0:ADC_RES[7:0]存放高8位ADC结果，ADC_RESL[1:0]存放低2位ADC结果。1:ADC_RES[1:0]存放高2位ADC结果，ADC_RESL[7:0]存放低8位ADC结果。


// 定义初始化函数的参数
// ==================================================================

// ---------------------------------------
#ifndef BIT0
#define BIT0 0x01
#endif 
// -----------------
#ifndef BIT1
#define BIT1 0x02
#endif 
// -----------------
#ifndef BIT2
#define BIT2 0x04
#endif 
// -----------------
#ifndef BIT3
#define BIT3 0x08
#endif 
// -----------------
#ifndef BIT4
#define BIT4 0x10
#endif 
// -----------------
#ifndef BIT5
#define BIT5 0x20
#endif 
// -----------------
#ifndef BIT6
#define BIT6 0x40
#endif 
// -----------------
#ifndef BIT7
#define BIT7 0x80
#endif 
// ---------------------------------------
#ifndef DISABL
#define DISABL		0		// 关闭(失效) ADC工作模式为查询方式
#endif 
// -----------------
#ifndef ENABLE
#define ENABLE		1		// 使能 ADC工作模式为中断方式
#endif
// ---------------------------------------
#ifndef PRIORITY_L
#define PRIORITY_L	0		// 中断优先等级低
#endif
// -----------------
#ifndef PRIORITY_H
#define PRIORITY_H	1		// 中断优先等级高
#endif
// ---------------------------------------
#ifndef GPIO_PullUp
#define GPIO_PullUp	0		// 00上拉准双向口
#endif
// -----------------
#ifndef GPIO_OUT_PP
#define GPIO_OUT_PP	1		// 01推挽输出
#endif
// -----------------
#ifndef GPIO_HighZ
#define GPIO_HighZ	2		// 10浮空输入
#endif
// -----------------
#ifndef GPIO_OUT_OD
#define GPIO_OUT_OD	3 		// 11开漏输出
#endif
// ---------------------------------------
#ifndef HIGH_8B
#define HIGH_8B		0		// ADC结果:[ADC_RES,ADC_RESL]=xxxx,xxxx,xx00,0000
#endif
// -----------------
#ifndef HIGH_2B
#define HIGH_2B		1		// ADC结果:[ADC_RES,ADC_RESL]=0000,00xx,xxxx,xxxx
#endif
// ---------------------------------------


// 定义初始化函数的参数
// ==================================================================

// ADC通道ID号
// ---------------------------------------
#define ADC_0	0x01		// ADC通道0
#define ADC_1	0x02		// ADC通道1
#define ADC_2	0x04		// ADC通道2
#define ADC_3	0x08		// ADC通道3
#define ADC_4	0x10		// ADC通道4
#define ADC_5	0x20		// ADC通道5
#define ADC_6	0x40		// ADC通道6
#define ADC_7	0x80		// ADC通道7
// ---------------------------------------


// ADC转换速度
typedef enum
{
	SPEED_LOW	= 0x00,		// ADC 540个时钟周期转换一次，CPU工作频率/540，最慢
	SPEED_SLOW	= 0x20,		// ADC 360个时钟周期转换一次，CPU工作频率/360，慢
	SPEED_FAST	= 0x40,		// ADC 180个时钟周期转换一次，CPU工作频率/180，快
	SPEED_SOON	= 0x60		// ADC  90个时钟周期转换一次，CPU工作频率/ 90，最快
}eSlewRate;


// 初始化ADC参数的结构体
typedef struct
{
	uchar		ADC_ResultAdj :1;	// ADC转换值调整方式，HIGH_8B(高8位 低2位)/HIGH_2B(高2位 低8位)。
	uchar 		ADC_Interrupt :1;	// ADC中断使能，	DISABL(关闭)/ENABLE(使能)。
	uchar 		ADC_Priority :1;	// ADC中断优先级, PRIORITY_L(低)/PRIORITY_H(高)
	eSlewRate	ADC_SlewRate;		// ADC转换的速度，0~3共四档。SPEED_LOW(最慢)/SPEED_SLOW(慢)/SPEED_FAST(快)/SPEED_SOON(最快)。
}sADC_InitTypeDef;


// 保存初始化ADC的参数值
typedef struct
{
	uchar	InitChannel;	// ADC初始化所有需要转换的通道
	uchar	ConvertSpeed;	// ADC转换速度。
	uchar	ResultBuf[ADC_BUF_SIZE];	// ADC每个通道(3Bytes)采集的值
}sADC_VALUE;


#if (USE_ADC)
global sADC_VALUE volatile xdata	sAdcValue;
#endif

// 声明函数
// ==================================================================


#if (TEST_ADC && USE_ADC)
void TestAdc(void);							// ADC测试程序
#endif

#if (USE_ADC)
uchar InitializeADC(uchar, sADC_InitTypeDef *);	// 初始化ADC
uchar GetAdcValue(uchar *, uchar);				// 查询方式读取ADC结果
void AdcPowerControl(uchar);					// ADC模块电源开关控制
void AdcRunControl(uchar);						// ADC模块运行状态控制
void DelayAdc(uint);							// ADC初始化用软件延时
#endif

// ==================================================================
#undef 	global
#endif			// __STC15W4KxxS4_ADC_H__
// ==================================================================