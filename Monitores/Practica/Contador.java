// Esta es la version que piden en el PDF.

public class Contador {
    private int contador;

    public Contador() {
        this.contador = 0;
    }

    public synchronized int sumar(){
        this.contador++;
        return this.contador;
    }

    public synchronized int restar(){
        this.contador--;
        return this.contador;
    }

}

// Esta es una segunda version propuesta por los profes para usar una condition variable
/*
public class Contador {
    private int contador;

    public Contador() {
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
*/