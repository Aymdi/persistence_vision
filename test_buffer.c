#include <stdio.h>
#include "buffer.h"

void main(){
    struct RingBuffer buffer;
    ringBufferInit(&buffer);
    printf("Initialization\n");
    printf("buffer available : %d\n", ringBufferAvailable(&buffer));
    printf("ringBufferWrite\n");
    printf("writing ... 6\n");
    ringBufferWrite(&buffer,6);
    printf("buffer available : %d\n", ringBufferAvailable(&buffer));
    printf("ringBufferRead\n");
    printf("reading ... %d\n", ringBufferRead(&buffer));
    printf("buffer available : %d\n", ringBufferAvailable(&buffer));
}