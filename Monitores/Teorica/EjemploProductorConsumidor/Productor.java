class Productor extends Thread {
    private final Buffer buffer;

    public Productor(Buffer buffer){
        this.buffer = buffer;
    }

    public void run(){
        int  i = 0;
        while (true){
            try {
                buffer.write(i);
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
            i++;
        }
    }
}