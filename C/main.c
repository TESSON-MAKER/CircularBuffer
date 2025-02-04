#include <stdio.h>
#include "buffer.h"

#define BUFFER_CAPACITY 6

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
    
    // Write some data into the buffer
    BUFFER_Write(&buffer, 1);
    BUFFER_Write(&buffer, 2);
    BUFFER_Write(&buffer, 3);
    BUFFER_Write(&buffer, 4);
    BUFFER_Write(&buffer, 5);
    BUFFER_Write(&buffer, 6);
    BUFFER_Write(&buffer, 7);
    BUFFER_Write(&buffer, 8);

    BUFFER_PopAllData(&buffer, &clip);

    // Write another piece of data into the buffer
    BUFFER_Write(&buffer, 9);
    
    BUFFER_PopAllData(&buffer, &clip);

    return 0; // End of the program execution
}
