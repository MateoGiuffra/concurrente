/*
* ROLES:
* productor de cuadros de video crudos
* consumidor de paquetes de cuadros para realizar el proceso de encoding.
* PROBLEMA
* Como los cuadros de video crudo son pesados, se desea que en ningun momento se almacenen mas de
* M cuadros en el monitor
* SE PIDE QUE:
* a) Implementar Encoder con los methods:
* - putRawFram(frame) (invocado por el productor)
* - getPack() -> CC[] (incovaco por los consumidores) la lista es menor o igual a M.
* La ejecucion de getPack debe bloquear hasta que haya P cuadros disponibles.
*
* */


import java.util.ArrayList;
//a
public class EncoderA {
    private int maximo;
    private int P;
    private ArrayList<String> frames;

    public EncoderA(int maximo, int p){
        this.maximo = maximo;
        this.P = Math.min(maximo, p);
        this.frames = new ArrayList<>();
    }

    public synchronized void putRawFrame(String frame) throws InterruptedException {
        while (frames.size() == this.maximo){
            wait();
        }
        frames.add(frame);
        if (this.frames.size() >= this.P){
            notifyAll();
        }
    }

    public synchronized ArrayList<String> getPack() throws InterruptedException {
        while (frames.size() < this.P){
            wait();
        }
        ArrayList<String> list = new ArrayList<String>();
        for (int i = 0; i < this.P ; i++) {
            String c = this.frames.get(i);
            this.frames.remove(i);
            list.add(c);
        }
        notifyAll();
        return list;
    }
}
