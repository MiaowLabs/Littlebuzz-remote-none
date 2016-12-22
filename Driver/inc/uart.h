
#ifndef _UART_H_  
#define _UART_H_  
 
#include "IAP15W4K61S4.h"

void Uart1Init(void);
unsigned char UART1ReceiveByte(void);
void UART1SendByte(unsigned char TxD1); 

#endif  