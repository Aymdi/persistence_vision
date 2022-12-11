#include <avr/io.h>
#include <util/delay.h>
#include "effet_Hall.h"
#include "com_blue.h"

void main() {
    struct RingBuffer buffer;
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