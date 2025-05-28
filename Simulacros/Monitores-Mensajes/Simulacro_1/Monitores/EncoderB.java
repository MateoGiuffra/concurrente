import java.util.ArrayList;
import java.util.List;

//b
public class EncoderB {
    private int maximo;
    private ArrayList<String> frames;

    public EncoderB(int maximo, int p){
        this.maximo = maximo;
        this.frames = new ArrayList<>();
    }

    public synchronized void putRawFrame(String frame) throws InterruptedException {
        while (frames.size() == this.maximo){
            wait();
        }
        frames.add(frame);
        notifyAll();
    }

    public synchronized ArrayList<String> getPack(int p) throws InterruptedException {
        while (frames.size() < p){
            wait();
        }
        ArrayList<String> list = new ArrayList<String>();
        for (int i = 0; i < p; i++) {
            String c = this.frames.get(i);
            this.frames.remove(i);
            list.add(c);
        }
        notifyAll();
        return list;
    }
}
