package ejercicio_1;
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

