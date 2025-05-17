package ejercicio_4;

public class ThreadPaciente extends Thread {
    String letra;
    int numero;
    Barrera miBarrera;
    public ThreadPaciente(String letra, int numero, Barrera miBarrera) {
        this.letra = letra;
        this.numero = numero;
        this.miBarrera = miBarrera;
    }

    public void run() {
        System.out.println(this.letra);
        try {
            miBarrera.esperar();
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }
        System.out.println(this.numero);
    }
}
