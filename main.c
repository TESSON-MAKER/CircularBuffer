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
    
    // Write some data into the buffer
    BUFFER_Write(&buffer, 1);
    BUFFER_Write(&buffer, 2);
    BUFFER_Write(&buffer, 3);

    printf("Buffer size after writing 3 elements: %d\n", BUFFER_Length(&buffer));

    // Pop all remaining data from the buffer and store it in the clip
    if (BUFFER_PopAllData(&buffer, &clip)) {
        printf("Data extracted to clip: ");
        for (int i = 0; i < clip.size; i++) {
            printf("%d ", clip.data[i]);
        }
        printf("\n");
    } else {
        printf("Buffer was empty, nothing extracted.\n");
    }

    // Write another piece of data into the buffer
    BUFFER_Write(&buffer, 9);
    
    printf("Buffer size after writing one more element: %d\n", BUFFER_Length(&buffer));

    // Pop all remaining data from the buffer and store it in the clip
    if (BUFFER_PopAllData(&buffer, &clip)) {
        printf("Data extracted to clip: ");
        for (int i = 0; i < clip.size; i++) {
            printf("%d ", clip.data[i]);
        }
        printf("\n");
    } else {
        printf("Buffer was empty, nothing extracted.\n");
    }

    return 0; // End of the program execution
}
