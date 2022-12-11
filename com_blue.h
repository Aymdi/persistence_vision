#ifndef COM_BLUE
#define COM_BLUE

#define F_CPU 13000000UL // Clock Speed
#define BAUD 38400
#define MYUBRR F_CPU/16/BAUD-1

#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include "buffer.h"

void USART_Init(unsigned int ubrr);

char USART_Receive(void);

void USART_Transmit(char data);


#endif