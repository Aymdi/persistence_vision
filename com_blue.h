#ifndef COM_BLUE_H
#define COM_BLUE_H


extern char USART_buffer[100];
extern int current_index_buff;

void USART_init(void);
void USART_Transmit(unsigned char data);
unsigned char USART_Receive(void);
void bl_reset_buffer();

#endif