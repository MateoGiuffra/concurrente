package ejercicio_4;

public class Main {
    public static void main (String [] args){
        Barrera barrera = new Barrera(5);
        ThreadPaciente a = new ThreadPaciente("a", 1, barrera);
        ThreadPaciente b = new ThreadPaciente("b", 2, barrera);
        ThreadPaciente c = new ThreadPaciente("c", 3, barrera);
        ThreadPaciente d = new ThreadPaciente("d", 4, barrera);
        ThreadPaciente e = new ThreadPaciente("e", 5, barrera);
        a.start();
        b.start();
        c.start();
        d.start();
        e.start();
    }
}