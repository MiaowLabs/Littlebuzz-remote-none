#ifndef __NRF24L0102_H
#define __NRF24L0102_H
typedef unsigned char uchar;
typedef unsigned char uint;	
sbit	CE	  =P3^6;
sbit	CSN		=P4^2;
sbit	SCK	  =P3^5;
sbit 	MOSI	=P4^1;
sbit 	MISO	=P5^1;
sbit	IRQ		=P3^7;

extern uchar TxBuf[20];
void Delay(unsigned int s);
void inerDelay_us(unsigned char n);
void init_NRF24L01(void);
void init_NRF24L012(void);
uint SPI_RW(uint uchar);
uchar SPI_Read(uchar reg);
void SetRX_Mode(void);
uint SPI_RW_Reg(uchar reg, uchar value);
uint SPI_Read_Buf(uchar reg, uchar *pBuf, uchar uchars);
uint SPI_Write_Buf(uchar reg, uchar *pBuf, uchar uchars);
void nRF24L01_RxPacket(unsigned char* rx_buf);
void nRF24L01_TxPacket(unsigned char * tx_buf);
 unsigned char NRF24L01_Check(void);
void check();



#endif  