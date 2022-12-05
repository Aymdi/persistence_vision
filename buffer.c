#include "buffer.h"

void ringBufferInit(struct RingBuffer* rb){
    rb->read = rb->buffer;
    rb->write= rb->buffer;
}

int ringBufferAvailable(struct RingBuffer* rb){
    return rb->read != rb->write;
}

unsigned char ringBufferRead(struct RingBuffer* rb){
    unsigned char c = *rb->read;
    rb->read++;
    if (rb->read >= rb->buffer + RING_BUFFER_SIZE){
        rb->read = rb->buffer;
    }
    return c;
}

void ringBufferWrite(struct RingBuffer* rb, unsigned char c){
    *rb->write = c;
    rb->write++;
    if (rb->write >= rb->buffer + RING_BUFFER_SIZE){
        rb->write = rb->buffer;
    }
}


//problème: le reader peut rattraper le writer, comment éviter cela ?