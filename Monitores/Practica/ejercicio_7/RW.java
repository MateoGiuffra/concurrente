package ejercicio_7;
import java.io.Serializable;
public class RW {
    private Serializable serializable;
    private int readers;
    private int writers;

    public synchronized void beginRead() throws InterruptedException {
        while(writers != 0){
            wait();
        }
        readers++;
    }
    public  synchronized void endRead(){
        readers--;
        notifyAll();
    }

    public synchronized void beginWrite(Serializable serializable) throws InterruptedException {
        writers++;
        while (readers > 0 || !(writers == 1)){
            wait();
        }
        this.serializable = serializable;
    }
    public synchronized void endWrite(){
        writers--;
        notifyAll();
    }

}
//TODO b,c,d y e
