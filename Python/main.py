import sys
from buffer import CircularBuffer, ClipBuffer, pop_all_data

BUFFER_CAPACITY = 6

def main():
    # Initialize buffers
    buffer = CircularBuffer(BUFFER_CAPACITY)
    clip = ClipBuffer(BUFFER_CAPACITY)
    
    # Write some data into the buffer
    buffer.write(1)
    buffer.write(2)
    buffer.write(3)
    buffer.write(4)
    buffer.write(5)
    buffer.write(6)
    buffer.write(7)
    buffer.write(8)
    
    pop_all_data(buffer, clip)
    
    # Write another piece of data into the buffer
    buffer.write(9)
    
    pop_all_data(buffer, clip)
    
    return 0

if __name__ == "__main__":
    sys.exit(main())