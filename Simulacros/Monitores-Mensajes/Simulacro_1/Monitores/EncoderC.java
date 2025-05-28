import java.util.ArrayList;

//c
public class EncoderC {
    private int maximo;
    private ArrayList<String> savedFrames;
    private ArrayList<String> processedFrames;
    private int threadsDoingEncode;
    private int K;
    public EncoderC(int maximo, int p, int k){
        this.maximo = maximo;
        this.processedFrames = new ArrayList<>();
        this.threadsDoingEncode = 0;
        this.K = k;
    }

    public synchronized void putRawFrame(String frame) throws InterruptedException {
        while (processedFrames.size() == maximo){
            wait();
        }
        processedFrames.add(frame);
        notifyAll();
    }

    public synchronized ArrayList<String> getPack(int p) throws InterruptedException {
        while (processedFrames.size() < p || threadsDoingEncode == K){
            wait();
        }
        threadsDoingEncode++;
        ArrayList<String> list = getNFrames(p);
        notifyAll();
        return list;
    }
    public synchronized void putEncodedPack(ArrayList<String> newFrames){
        //Esto se ejecuto despues de un getPack
        this.getNFrames(newFrames.size());
        threadsDoingEncode--;
        notifyAll();
    }

    public ArrayList<String> getNFrames(int n){
        ArrayList<String> list = new ArrayList<String>();
        for (int i = 0; i < n; i++) {
            String c = this.processedFrames.get(i);
            this.processedFrames.remove(i);
            list.add(c);
        }
        return list;
    }
}
