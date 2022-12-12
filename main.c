#include <avr/io.h>
#include <util/delay.h>
#include "effet_Hall.h"
#include "com_blue.h"
#include <avr/interrupt.h>

struct RingBuffer buffer;

void main() {
    DDRB = 0x01;
	
	TCCR1B = (1 << WGM12);
	OCR1A = 19531;
	TIMSK1 = (1 << OCIE1A);
	
	sei();
	
	TCCR1B |= (1 << CS12) | (1 << CS10);
	
    while(1)
    {
        //code d'application
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
    }
}

ISR(TIMER1_COMPA_vect)
{
	PORTB ^= (1 << PORTB0);
}