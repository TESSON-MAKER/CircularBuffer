#include <string.h>
#include "buffer.h"

/***********************************************************************************************
 * @name       : BUFFER_ResetCircular
 * @function   : Resets the circular buffer by setting the read and write indices to 0
 *               and clearing its content. 
 * @parameters : CircularBufferTypeDef* buff - Pointer to the circular buffer structure.
 * @retvalue   : None
 ***********************************************************************************************/
void BUFFER_ResetCircular(CircularBufferTypeDef* buff)
{
    buff->readIndex = 0;
    buff->writeIndex = 0;
    memset(buff->data, 0, buff->capacity);
}

/***********************************************************************************************
 * @name       : BUFFER_ResetClip
 * @function   : Clears all data in a clip buffer.
 * @parameters : ClipBufferTypeDef* clip - Pointer to the clip buffer structure.
 * @retvalue   : None
 ***********************************************************************************************/
void BUFFER_ResetClip(ClipBufferTypeDef* clip)
{
    memset(clip->data, 0, clip->capacity);
}

/***********************************************************************************************
 * @name       : BUFFER_CircularInit
 * @function   : Initializes the circular buffer with a data array and a given capacity.
 * @parameters : CircularBufferTypeDef* buff - Pointer to the circular buffer structure.
 *               uint8_t* bufferArray - Pointer to the data array used by the buffer.
 *               uint16_t capacity - Maximum capacity of the buffer.
 * @retvalue   : None
 ***********************************************************************************************/
void BUFFER_CircularInit(CircularBufferTypeDef* buff, uint8_t* bufferArray, uint16_t capacity)
{
    buff->data = bufferArray;
    buff->capacity = capacity;
    BUFFER_ResetCircular(buff); // Resets the indices and clears the buffer
}

/***********************************************************************************************
 * @name       : BUFFER_ClipInit
 * @function   : Initializes the clip buffer with a data array and a given capacity.
 * @parameters : ClipBufferTypeDef* clip - Pointer to the clip buffer structure.
 *               uint8_t* clipArray - Pointer to the data array used by the clip buffer.
 *               uint16_t capacity - Maximum capacity of the clip buffer.
 * @retvalue   : None
 ***********************************************************************************************/
void BUFFER_ClipInit(ClipBufferTypeDef* clip, uint8_t* clipArray, uint16_t capacity)
{
    clip->data = clipArray;
    clip->capacity = capacity;
    BUFFER_ResetClip(clip);
}

/***********************************************************************************************
 * @name       : BUFFER_GetLength
 * @function   : Computes the number of elements currently stored in the circular buffer.
 * @parameters : CircularBufferTypeDef* buff - Pointer to the circular buffer structure.
 * @retvalue   : uint16_t - Number of elements in the buffer.
 ***********************************************************************************************/
uint16_t BUFFER_GetLength(CircularBufferTypeDef* buff)
{
    if (buff->writeIndex >= buff->readIndex) 
    {
        // No wrap-around case
        return buff->writeIndex - buff->readIndex;
    } 
    else 
    {
        // Wrap-around case
        return (buff->capacity - buff->readIndex) + buff->writeIndex; 
    }
}

/***********************************************************************************************
 * @name       : BUFFER_Push
 * @function   : Adds a new data element to the circular buffer.
 * @parameters : CircularBufferTypeDef* buff - Pointer to the circular buffer structure.
 *               uint8_t data - The byte to be pushed into the buffer.
 * @retvalue   : uint8_t - Returns 1 if the buffer is full (data not added), 0 if successful.
 ***********************************************************************************************/
uint8_t BUFFER_Push(CircularBufferTypeDef* buff, uint8_t data)
{
    // Store the data at the current write index
    buff->data[buff->writeIndex] = data;

    // Move the write index forward with circular behavior
    buff->writeIndex = (buff->writeIndex + 1) % buff->capacity;

    // Check if the buffer is full (write index overlaps read index)
    if (buff->writeIndex == buff->readIndex) 
    {
        return 1; // Buffer full
    }
    return 0; // Success
}

/***********************************************************************************************
 * @name       : BUFFER_PopData
 * @function   : Removes and retrieves a single data element from the buffer.
 * @parameters : CircularBufferTypeDef* buff - Pointer to the circular buffer structure.
 *               uint8_t* data - Pointer where the retrieved data will be stored.
 * @retvalue   : uint8_t - Returns 0 if successful, 1 if the buffer is empty.
 ***********************************************************************************************/
uint8_t BUFFER_PopData(CircularBufferTypeDef* buff, uint8_t* data)
{
    if (buff->readIndex == buff->writeIndex) 
    {
        return 1; // Failure: buffer is empty
    }
    
    // Retrieve data from read index
    *data = buff->data[buff->readIndex];

    // Move the read index forward with circular behavior
    buff->readIndex = (buff->readIndex + 1) % buff->capacity;
    
    return 0; // Success
}

/***********************************************************************************************
 * @name       : BUFFER_PopAllData
 * @function   : Extracts all available data from the buffer and stores it in a clip.
 * @parameters : CircularBufferTypeDef* buff - Pointer to the circular buffer structure.
 *               ClipBufferTypeDef* clip - Pointer to the clip structure where extracted data will be stored.
 * @retvalue   : uint8_t - Returns 0 if at least one element was extracted, 1 if the buffer was empty.
 ***********************************************************************************************/
uint8_t BUFFER_PopAllData(CircularBufferTypeDef* buff, ClipBufferTypeDef* clip)
{
    BUFFER_ResetClip(clip);
    
    if (buff->readIndex == buff->writeIndex) 
    {
        return 1; // Buffer is empty
    }
    
    int i = 0;
    while (buff->readIndex != buff->writeIndex && i < clip->capacity) 
    {
        clip->data[i++] = buff->data[buff->readIndex];
        buff->readIndex = (buff->readIndex + 1) % buff->capacity;
    }
    
    int state = (i > 0) ? 0 : 1;
    return state; // Return 0 if data was extracted, otherwise return 1
}
