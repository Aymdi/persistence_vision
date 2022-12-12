#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include "buffer.h"

#define F_CPU 13000000UL // Clock Speed
#define BAUD 38400
#define MYUBRR F_CPU/16/BAUD-1

/*char data;
struct RingBuffer buffer;
*/

char USART_buffer[100]= "INIT";
int index_buffer = 0;

/*void USART_Init(unsigned int ubrr)
{
    /* Set baud rate */
    UBRR0H = (unsigned char)(ubrr>>8);
    UBRR0L = (unsigned char)(ubrr);
    
    /* Enable receiver and transmitter */
    UCSR0B = (1<<RXEN0)|(1<<TXEN0);
    
    /* Set frame format: 8data, 2stop bit */
    /*UCSR0C = (1<<USBS0)|(3<<UCSZ00);
}
*/

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

char USART_Receive(void)
{
    /* Wait for data to be received */
    while ( !(UCSR0A & (1<<RXC0)) );
    /* Get and return received data from buffer */
    return UDR0;
}

void USART_Transmit(char data)
{
    /* Wait for empty transmit buffer */
    while ( !( UCSR0A & (1<<UDRE0)) );
    /* Put data into buffer, sends the data */
    UDR0 = data;
}


ISR(USART_RX_vect)
{

  unsigned char c =  UDR0; 

  if( c=='\n' ){  
    USART_buffer[index_buffer] =  '\0';
    index_buffer = 0;
    return;
  }
  USART_buffer[index_buffer] = c;  
  index_buffer++;
  if (index_buffer >= 100 - 1)
  {
    index_buffer = 0;
  }
}


void bl_reset_buffer()
{
  USART_buffer[0] = '\0';
}

//version sans interruption
/*int main(void)
{
    
    DDRB  = 0b00000001;
    PORTB = 0b00000000;
    USART_Init(MYUBRR);
    ringBufferInit(&buffer);
    while (1) {
        ringBufferWrite(&buffer, USART_Receive());
        if (ringBufferAvailable(&buffer)){
            USART_Transmit(ringBufferRead(&buffer));
        }
    }
}*/