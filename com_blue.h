#ifndef COM_BLUE_H
#define COM_BLUE_H

unsigned char c;


void USART_init(void);
void USART_Transmit(unsigned char data);
unsigned char USART_Receive(void);

#endif