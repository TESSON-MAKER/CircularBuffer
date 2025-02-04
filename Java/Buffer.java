public class Buffer {

    // Circular buffer class
    public static class CircularBuffer {
        private byte[] data;
        private int capacity;
        private int size;
        private int readIndex;
        private int writeIndex;

        public CircularBuffer(int capacity) {
            this.capacity = capacity;
            this.data = new byte[capacity];
            this.size = 0;
            this.readIndex = 0;
            this.writeIndex = 0;
        }

        public void init(byte[] bufferArray) {
            this.data = bufferArray;
            this.capacity = bufferArray.length;
            reset();
        }

        public void reset() {
            this.readIndex = 0;
            this.writeIndex = 0;
            this.size = 0;
            java.util.Arrays.fill(data, (byte) 0);
        }

        public int length() {
            return size;
        }

        public void write(byte data) {
            if (size >= capacity) {
                readIndex = (readIndex + 1) % capacity;
                size--;
            }
            this.data[writeIndex] = data;
            writeIndex = (writeIndex + 1) % capacity;
            size++;
        }

        public boolean popAllData(ClipBuffer clip) {
            if (size == 0) {
                clip.setSize(0);
                return true;
            }

            int count = Math.min(size, clip.getCapacity());
            for (int i = 0; i < count; i++) {
                clip.getData()[i] = this.data[readIndex];
                readIndex = (readIndex + 1) % capacity;
            }

            size -= count;
            clip.setSize(count);
            return false;
        }
    }

    // Clip buffer class
    public static class ClipBuffer {
        private byte[] data;
        private int capacity;
        private int size;

        public ClipBuffer(int capacity) {
            this.capacity = capacity;
            this.data = new byte[capacity];
            this.size = 0;
        }

        public void init(byte[] clipArray) {
            this.data = clipArray;
            this.capacity = clipArray.length;
            reset();
        }

        public void reset() {
            java.util.Arrays.fill(data, (byte) 0);
            size = 0;
        }

        public int getSize() {
            return size;
        }

        public void setSize(int size) {
            this.size = size;
        }

        public int getCapacity() {
            return capacity;
        }

        public byte[] getData() {
            return data;
        }
    }
}
