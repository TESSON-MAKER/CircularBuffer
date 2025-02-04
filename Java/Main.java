public class Main {
    private static final int BUFFER_CAPACITY = 6;

    public static void main(String[] args) {
        byte[] bufferArray = new byte[BUFFER_CAPACITY];
        byte[] clipArray = new byte[BUFFER_CAPACITY];

        Buffer.CircularBuffer buffer = new Buffer.CircularBuffer(BUFFER_CAPACITY);
        Buffer.ClipBuffer clip = new Buffer.ClipBuffer(BUFFER_CAPACITY);

        buffer.init(bufferArray);
        clip.init(clipArray);

        buffer.write((byte) 1);
        buffer.write((byte) 2);
        buffer.write((byte) 3);
        buffer.write((byte) 4);
        buffer.write((byte) 5);
        buffer.write((byte) 6);
        buffer.write((byte) 7);
        buffer.write((byte) 8);

        buffer.popAllData(clip);
        System.out.println("Clip buffer size after first pop: " + clip.getSize());

        buffer.write((byte) 9);

        buffer.popAllData(clip);
        System.out.println("Clip buffer size after second pop: " + clip.getSize());
    }
}
