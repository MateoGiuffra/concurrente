package ejercicio_2;

public class Semaphore {
    int permisos;
    int esperando;

    public Semaphore(int permisos) {
        this.permisos = permisos;
        this.esperando = 0;
    }

    public synchronized void acquiere() throws InterruptedException {
        while (this.permisos == 0) {
            esperando++;
            wait();
        }

        permisos--;
    }

    public synchronized void release() {
        if (esperando == 0) {
            permisos++;
        } else {
            notify();
            esperando--;
        }
    }

}
