#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "buffer.h"
#include "com_blue.h"

#define F_CPU 13000000UL // Clock Speed
#define BAUD 38400
#define MYUBRR F_CPU/16/BAUD-1

//version interruption
void USART_init(void){
    UBRR0H = (MYUBRR >> 8);
    UBRR0L = MYUBRR;
    UCSR0A &= ~_BV(U2X0);//disable arduino's auto-double async mode
    UCSR0B |= _BV(RXCIE0);//enable reciever interrupt
    UCSR0B |= _BV(RXEN0) | _BV(TXEN0);//enable RX and TX
    UCSR0C |= _BV(UCSZ01) | _BV(UCSZ00);//set frame: 8data, 1stop
    sei();//global interrupt enable flaag set
}

unsigned char USART_Receive(void)
{
    /* Wait for data to be received */
    while ( !(UCSR0A & (1<<RXC0)) );
    /* Get and return received data from buffer */
    return UDR0;
}

void USART_Transmit(unsigned char data)
{
    /* Wait for empty transmit buffer */
    while ( !( UCSR0A & (1<<UDRE0)) );
    /* Put data into buffer, sends the data */
    UDR0 = data;
}

ISR(USART_RX_vect)
{
  unsigned char c = UDR0;
  if (c == 'a'){
    ringBufferWrite(buffer, c);
    ringBufferInit(buffer);
    USART_Transmit(c);
    return;
  }
  
  ringBufferWrite(buffer, c);
  USART_Transmit(c);
}

