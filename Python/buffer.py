class CircularBuffer:
    def __init__(self, capacity):
        self.capacity = capacity
        self.data = [0] * capacity
        self.read_index = 0
        self.write_index = 0
        self.size = 0
    
    def reset(self):
        self.read_index = 0
        self.write_index = 0
        self.size = 0
        self.data = [0] * self.capacity
    
    def length(self):
        return self.size
    
    def write(self, value):
        if self.size >= self.capacity:
            self.read_index = (self.read_index + 1) % self.capacity
            self.size -= 1
        
        self.data[self.write_index] = value
        self.write_index = (self.write_index + 1) % self.capacity
        self.size += 1
    
    def pop_data(self):
        if self.size == 0:
            return None  # Buffer empty
        
        value = self.data[self.read_index]
        self.read_index = (self.read_index + 1) % self.capacity
        self.size -= 1
        return value


class ClipBuffer:
    def __init__(self, capacity):
        self.capacity = capacity
        self.data = [0] * capacity
        self.size = 0
    
    def reset(self):
        self.data = [0] * self.capacity
        self.size = 0
    

def pop_all_data(circular_buffer, clip_buffer):
    if circular_buffer.size == 0:
        clip_buffer.size = 0
        return 1  # Buffer empty
    
    count = min(circular_buffer.size, clip_buffer.capacity)
    
    for i in range(count):
        clip_buffer.data[i] = circular_buffer.pop_data()
    
    clip_buffer.size = count
    return 0
