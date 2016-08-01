#ifndef __STC15W4KxxS4_ADC_H__
#define __STC15W4KxxS4_ADC_H__
// ==================================================================


// ����ͷ�ļ�
// ==================================================================
#include	"stc15w4kxxs4.h"

// ==================================================================





#ifdef __STC15W4KxxS4_ADC_C__

// �������룬����ͷ�ļ���Ӧ��.C�ļ�����ʱ�����ã������ļ�����ʱΪ����
// -------------------------------------------------------------
#define	global 				// �Լ���.C�ļ�����ʱ��global �൱�ڿա�
#else						// ������.C����
#define	global extern		// �ڴ�����Ϊ�ⲿ����
#endif
// -------------------------------------------------------------

 
// ��ʼ����ȫ�ֱ���
// ==================================================================



// �궨�壬���¸����������ݾ����ʹ�������д
// ==================================================================


// ADC��ʼ��������Կ���
#define	TEST_ADC	1		// ������Կ��أ�	0:�����ԣ�1:���в���


// ADCͨ��ʹ�ÿ���
#define USE_ADC0	0		// ADCͨ��0		0:��ʹ�ã�1:ʹ��
#define USE_ADC1	0		// ADCͨ��1		0:��ʹ�ã�1:ʹ��
#define USE_ADC2	1		// ADCͨ��2		0:��ʹ�ã�1:ʹ��
#define USE_ADC3	1		// ADCͨ��3		0:��ʹ�ã�1:ʹ��
#define USE_ADC4	1		// ADCͨ��4		0:��ʹ�ã�1:ʹ��
#define USE_ADC5	1		// ADCͨ��5		0:��ʹ�ã�1:ʹ��
#define USE_ADC6	1		// ADCͨ��6		0:��ʹ�ã�1:ʹ��
#define USE_ADC7	1		// ADCͨ��7		0:��ʹ�ã�1:ʹ��


// ���±������������Զ����㣬����Ҫ�ֹ�����
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


#define ADC_NUMBER	(ADC_NM0 + ADC_NM1 + ADC_NM2 + ADC_NM3 + ADC_NM4 + ADC_NM5 + ADC_NM6 + ADC_NM7)	// ���빤����ADC��ͨ����1~8
#define ADC_PASSAGE	(ADC_PG0 | ADC_PG1 | ADC_PG2 | ADC_PG3 | ADC_PG4 | ADC_PG5 | ADC_PG6 | ADC_PG7)	// ���빤����ADC��ͨ
#define USE_ADC		ADC_NUMBER

#define ADC_BUF_SIZE (ADC_NUMBER*3+3)


// ==================================================================


// PWMCFG B6: CBTADC	PWM����������ʱ(CBIF==1ʱ)����ADCת����1:PWM����������ʱ�Զ�����ADCת����(ע:ǰ��������PWM��ADC���뱻ʹ�ܣ���ENPWM==1����ADCON==1)
// PWMCFG B5: C7INI		����PWM7����˿ڵĳ�ʼ��ƽΪ�͵�ƽ��0:��ʼ��ƽΪ�͵�ƽ��1:��ʼ��ƽΪ�ߵ�ƽ��
// PWMCFG B4: C6INI		����PWM6����˿ڵĳ�ʼ��ƽΪ�͵�ƽ��0:��ʼ��ƽΪ�͵�ƽ��1:��ʼ��ƽΪ�ߵ�ƽ��
// PWMCFG B3: C5INI		����PWM5����˿ڵĳ�ʼ��ƽΪ�͵�ƽ��0:��ʼ��ƽΪ�͵�ƽ��1:��ʼ��ƽΪ�ߵ�ƽ��
// PWMCFG B2: C4INI		����PWM4����˿ڵĳ�ʼ��ƽΪ�͵�ƽ��0:��ʼ��ƽΪ�͵�ƽ��1:��ʼ��ƽΪ�ߵ�ƽ��
// PWMCFG B1: C3INI		����PWM3����˿ڵĳ�ʼ��ƽΪ�͵�ƽ��0:��ʼ��ƽΪ�͵�ƽ��1:��ʼ��ƽΪ�ߵ�ƽ��
// PWMCFG B0: C2INI		����PWM2����˿ڵĳ�ʼ��ƽΪ�͵�ƽ��0:��ʼ��ƽΪ�͵�ƽ��1:��ʼ��ƽΪ�ߵ�ƽ��

// ADC_RES			ADRJ=0ʱ:ADC�����8λ�Ĵ�����ADRJ=1ʱ:ADC�����2λ�Ĵ���
// ADC_RESL			ADRJ=0ʱ:ADC�����2λ�Ĵ�����ADRJ=1ʱ:ADC�����8λ�Ĵ���

// ADC_CONTR B7:ADC_POWER	ADC��Դ����λ��0:�ر�ADC��Դ��1:��A/Dת������Դ������������ģʽ�͵���ģʽǰ����ADC��Դ�رգ���ADC_POWER=0���ɽ��͹��ġ�����A/Dת��ǰһ��Ҫȷ��A/D��Դ�Ѵ򿪣�A/Dת��������ر�A/D��Դ�ɽ��͹��ģ�Ҳ�ɲ��رա����δ��ڲ�A/Dת��ģ���Դ�����ʵ���ʱ�����ڲ�ģ���Դ�ȶ���������A/Dת����������A/Dת������A/Dת������֮ǰ�����ı��κ�I/O�ڵ�״̬�������ڸ߾���A/Dת�������ܽ���ʱ��/����/�ж�ϵͳ�رո��á�
// ADC_CONTR B6:SPEED1		ģ��ת����ת���ٶȿ���λ1��
// ADC_CONTR B5:SPEED0		ģ��ת����ת���ٶȿ���λ0��
// ADC_CONTR B4:ADC_FLAG	ģ��ת����ת��������־λ����A/Dת����ɺ�ADC_FLAG=1��Ҫ�������0.������A/Dת����ɺ��ɸ�λ��������жϣ������������ѯ�ñ�־λA/Dת���Ƿ��������A/Dת����ɺ�ADC_FLAG=1��һ��Ҫ�����0��
// ADC_CONTR B3:ADC_START	ģ��ת����(ADC)ת����������λ������Ϊ��1��ʱ����ʼת����ת��������Ϊ0��
// ADC_CONTR B2:CHS2		ģ������ͨ��ѡ��λ2��
// ADC_CONTR B1:CHS1		ģ������ͨ��ѡ��λ1��
// ADC_CONTR B0:CHS0		ģ������ͨ��ѡ��λ0��

// IP B5: PADC		A/Dת���ж����ȼ�����λ��

// IE B5: EADC		A/Dת���ж�����λ��

// CLK_DIV B5: ADRJ		ADCת�����������0:ADC_RES[7:0]��Ÿ�8λADC�����ADC_RESL[1:0]��ŵ�2λADC�����1:ADC_RES[1:0]��Ÿ�2λADC�����ADC_RESL[7:0]��ŵ�8λADC�����


// �����ʼ�������Ĳ���
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
#define DISABL		0		// �ر�(ʧЧ) ADC����ģʽΪ��ѯ��ʽ
#endif 
// -----------------
#ifndef ENABLE
#define ENABLE		1		// ʹ�� ADC����ģʽΪ�жϷ�ʽ
#endif
// ---------------------------------------
#ifndef PRIORITY_L
#define PRIORITY_L	0		// �ж����ȵȼ���
#endif
// -----------------
#ifndef PRIORITY_H
#define PRIORITY_H	1		// �ж����ȵȼ���
#endif
// ---------------------------------------
#ifndef GPIO_PullUp
#define GPIO_PullUp	0		// 00����׼˫���
#endif
// -----------------
#ifndef GPIO_OUT_PP
#define GPIO_OUT_PP	1		// 01�������
#endif
// -----------------
#ifndef GPIO_HighZ
#define GPIO_HighZ	2		// 10��������
#endif
// -----------------
#ifndef GPIO_OUT_OD
#define GPIO_OUT_OD	3 		// 11��©���
#endif
// ---------------------------------------
#ifndef HIGH_8B
#define HIGH_8B		0		// ADC���:[ADC_RES,ADC_RESL]=xxxx,xxxx,xx00,0000
#endif
// -----------------
#ifndef HIGH_2B
#define HIGH_2B		1		// ADC���:[ADC_RES,ADC_RESL]=0000,00xx,xxxx,xxxx
#endif
// ---------------------------------------


// �����ʼ�������Ĳ���
// ==================================================================

// ADCͨ��ID��
// ---------------------------------------
#define ADC_0	0x01		// ADCͨ��0
#define ADC_1	0x02		// ADCͨ��1
#define ADC_2	0x04		// ADCͨ��2
#define ADC_3	0x08		// ADCͨ��3
#define ADC_4	0x10		// ADCͨ��4
#define ADC_5	0x20		// ADCͨ��5
#define ADC_6	0x40		// ADCͨ��6
#define ADC_7	0x80		// ADCͨ��7
// ---------------------------------------


// ADCת���ٶ�
typedef enum
{
	SPEED_LOW	= 0x00,		// ADC 540��ʱ������ת��һ�Σ�CPU����Ƶ��/540������
	SPEED_SLOW	= 0x20,		// ADC 360��ʱ������ת��һ�Σ�CPU����Ƶ��/360����
	SPEED_FAST	= 0x40,		// ADC 180��ʱ������ת��һ�Σ�CPU����Ƶ��/180����
	SPEED_SOON	= 0x60		// ADC  90��ʱ������ת��һ�Σ�CPU����Ƶ��/ 90�����
}eSlewRate;


// ��ʼ��ADC�����Ľṹ��
typedef struct
{
	uchar		ADC_ResultAdj :1;	// ADCת��ֵ������ʽ��HIGH_8B(��8λ ��2λ)/HIGH_2B(��2λ ��8λ)��
	uchar 		ADC_Interrupt :1;	// ADC�ж�ʹ�ܣ�	DISABL(�ر�)/ENABLE(ʹ��)��
	uchar 		ADC_Priority :1;	// ADC�ж����ȼ�, PRIORITY_L(��)/PRIORITY_H(��)
	eSlewRate	ADC_SlewRate;		// ADCת�����ٶȣ�0~3���ĵ���SPEED_LOW(����)/SPEED_SLOW(��)/SPEED_FAST(��)/SPEED_SOON(���)��
}sADC_InitTypeDef;


// �����ʼ��ADC�Ĳ���ֵ
typedef struct
{
	uchar	InitChannel;	// ADC��ʼ��������Ҫת����ͨ��
	uchar	ConvertSpeed;	// ADCת���ٶȡ�
	uchar	ResultBuf[ADC_BUF_SIZE];	// ADCÿ��ͨ��(3Bytes)�ɼ���ֵ
}sADC_VALUE;


#if (USE_ADC)
global sADC_VALUE volatile xdata	sAdcValue;
#endif

// ��������
// ==================================================================


#if (TEST_ADC && USE_ADC)
void TestAdc(void);							// ADC���Գ���
#endif

#if (USE_ADC)
uchar InitializeADC(uchar, sADC_InitTypeDef *);	// ��ʼ��ADC
uchar GetAdcValue(uchar *, uchar);				// ��ѯ��ʽ��ȡADC���
void AdcPowerControl(uchar);					// ADCģ���Դ���ؿ���
void AdcRunControl(uchar);						// ADCģ������״̬����
void DelayAdc(uint);							// ADC��ʼ���������ʱ
#endif

// ==================================================================
#undef 	global
#endif			// __STC15W4KxxS4_ADC_H__
// ==================================================================