#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>


#define FOSC 13000000 // Clock Speed
#define BAUD 38400
#define MYUBRR FOSC/16/BAUD-1

#define RING_BUFFER_SIZE 64


struct RingBuffer{
    unsigned char buffer[RING_BUFFER_SIZE];
    unsigned char* read;
    unsigned char* write;
};

struct RingBuffer txRb;
struct RingBuffer rxRb;


void ringBufferInit(struct RingBuffer* rb) {
    rb->read = rb->buffer;
    rb->write = rb->buffer;
}

unsigned char ringBufferRead(struct RingBuffer* rb) {
    unsigned char c = *rb->read;
    rb->read++;
    if (rb->read == rb->buffer + RING_BUFFER_SIZE) {
        rb->read = rb->buffer;
    }
    return c;
}


void ringBufferWrite(struct RingBuffer* rb, unsigned char c) {
    *rb->write = c;
    rb->write++;
    if (rb->write == rb->buffer + RING_BUFFER_SIZE) {
        rb->write = rb->buffer;
    }
}

void uartInit(unsigned int ubrr) {
    UBRR0H = (unsigned char) (ubrr >> 8);
    UBRR0L = (unsigned char) ubrr;
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);
    UCSR0C = (1 << UCSZ00) | (1 << UCSZ01);
}

void uartTransmit(unsigned char data) {
    ringBufferWrite(&txRb, data);
    UCSR0B |= (1 << UDRIE0);
}

void uartTransmitString(unsigned char* data) {
    while (*data != 0) {
        uartTransmit(*data);
        data++;
    }
}



unsigned char uartReceive() {
    return ringBufferRead(&rxRb);
}



int main() {


    uartInit(MYUBRR);
    
    ringBufferInit(&txRb);
    ringBufferInit(&rxRb);
 
    while (1) {
        unsigned char c = uartReceive();
        char buffer[32];

        if (c == 13) {
            sprintf(buffer, "réponse 13 \n");
        } else if (c == 127) {
            sprintf(buffer, "réponse 127");
        } else {
            sprintf(buffer, "%c", c);
        }



        uartTransmitString(buffer);
  
    }
}
