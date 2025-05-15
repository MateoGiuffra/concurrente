class Consumidor extends Thread {
    private final Buffer buffer;
    public Consumidor(Buffer buffer){
        this.buffer = buffer;
    }
    public void run(){
        while(true){
            Object o = null;
            try {
                o = buffer.read();
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
            System.out.println("Leido " + o.toString());
        }
    }
}