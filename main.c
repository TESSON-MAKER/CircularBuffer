#include <stdio.h>
#include "buffer.h"

#define BUFFER_CAPACITY 10

int main() 
{
    // Declaration of an array to simulate the memory for the buffer and the clip
    uint8_t bufferArray[BUFFER_CAPACITY];
    uint8_t clipArray[BUFFER_CAPACITY];

    // Declaration of structures for the circular buffer and the clip
    CircularBufferTypeDef buffer;
    ClipBufferTypeDef clip;
    
    // Initialize the circular buffer with the array, capacity, and a pointer to the data
    BUFFER_CircularInit(&buffer, bufferArray, BUFFER_CAPACITY);
    BUFFER_ClipInit(&clip, clipArray, BUFFER_CAPACITY);
    
    // Push some data into the buffer (1)
    BUFFER_Push(&buffer, 1);

    // Pop all remaining data from the buffer and store it in the clip
    BUFFER_PopAllData(&buffer, &clip);

    // Push another piece of data into the buffer (9)
    BUFFER_Push(&buffer, 9);

    // Pop all remaining data from the buffer and store it in the clip
    BUFFER_PopAllData(&buffer, &clip);

    return 0; // End of the program execution
}
