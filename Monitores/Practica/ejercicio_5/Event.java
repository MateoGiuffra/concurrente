package ejercicio_5;

public class Event {
    private int incidencias;

    public Event(){
        this.incidencias = 0;
    }

    public synchronized void publish(){
        incidencias++;
        notifyAll();
    }

    public synchronized void suscribe() throws InterruptedException {
        int copiaIncidencias = incidencias;
        while (copiaIncidencias == incidencias){
            wait();
        }
    }

}
