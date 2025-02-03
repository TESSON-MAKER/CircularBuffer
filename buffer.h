#ifndef BUFFER_H
#define BUFFER_H

#include <stdint.h>
#include <stddef.h>

// Circular buffer structure
typedef struct {
    uint8_t* data;          // Pointer to buffer memory (array of bytes)
    uint16_t capacity;      // Maximum capacity of the buffer (number of elements it can hold)
    uint16_t readIndex;     // Index of the element to be read
    uint16_t writeIndex;    // Index of the element to be written
} CircularBufferTypeDef;

// Structure to store extracted data from the buffer
typedef struct {
    uint8_t* data;          // Pointer to the extracted data (array of bytes)
    uint8_t capacity;       // Maximum capacity of the buffer (number of elements it can hold)
    uint8_t length;         // Current number of elements stored
} ClipBufferTypeDef;

// Function prototypes
void BUFFER_ResetCircular(CircularBufferTypeDef* buff);
void BUFFER_ResetClip(ClipBufferTypeDef* clip);
uint16_t BUFFER_Length(CircularBufferTypeDef* buff);
uint8_t BUFFER_Push(CircularBufferTypeDef* buff, uint8_t data);
uint8_t BUFFER_PopData(CircularBufferTypeDef* buff, uint8_t* data);
uint8_t BUFFER_PopAllData(CircularBufferTypeDef* buff, ClipBufferTypeDef* clip);

#endif
