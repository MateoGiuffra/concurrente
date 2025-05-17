package ejercicio_6;
//MONITOR: Tengo que settear un valor y devolverlo
public class Promise implements Future{
    Object object;
    public synchronized void set(Object o){
        //hacer algo
        this.object = 0;
        notify();
    }
    public synchronized Object await() throws InterruptedException {
        while (object == null){
            wait();
        }
        Object localObj = this.object;
        this.object = null;
        return localObj;
    }
}
