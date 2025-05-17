package ejercicio_4;

public class Barrera {
    int cantThreads;
    boolean estaBaja;

    public Barrera(int cantThreads) {
        this.cantThreads = cantThreads;
        this.estaBaja = true;
    }

    public synchronized void esperar() throws InterruptedException {
        if (!estaBaja) return; // si el ambiente es controlado, o sea la cantidad de threads
        // que van a ejecutar esperar() es igual a cantThreads, entonces no hace falta.
        // si puede llegar a pasar un caso en el que no, esto salva de que no se rompa todo
        // y tengamos casos como cantThreads negativos
        cantThreads--;
        while (!(this.soyElUltimo())) {
            wait();
        }
        if (this.soyElUltimo()) { // este if es para evitar notifys de mas. Tambien habia un && estaBaja pero me parece innecesario
            notifyAll();
            this.estaBaja = false;
        }
    }

    private boolean soyElUltimo() { return cantThreads == 0; }

}
