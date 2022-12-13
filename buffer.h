#ifndef BUFFER_H
#define BUFFER_H

#define RING_BUFFER_SIZE 32
struct RingBuffer* buffer;

struct RingBuffer{
    unsigned char buffer[RING_BUFFER_SIZE];
    unsigned char* read;
    unsigned char* write;
};

void ringBufferInit(struct RingBuffer* rb);

int ringBufferAvailable(struct RingBuffer* rb);

unsigned char ringBufferRead(struct RingBuffer* rb);

void ringBufferWrite(struct RingBuffer* rb, unsigned char c);


#endif