package ejercicio_1;
// Esta es una segunda version propuesta por los profes para usar una condition variable
public class ContadorV2 {
    private int contador;

    public ContadorV2() {
        this.contador = 0;
    }

    public synchronized int sumar(){
        this.contador++;
        notify();
        return this.contador;
    }

    public synchronized int restar() throws InterruptedException {
        while (this.contador == 0){
            wait();
        }
        this.contador--;
        return this.contador;
    }

}
