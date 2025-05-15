public class Main {
    public static void main (String [] args){
       Buffer buffer = new Buffer(2);
        Productor p = new Productor(buffer);
        Consumidor c = new Consumidor(buffer);
        p.start();
        c.start();
    }
}