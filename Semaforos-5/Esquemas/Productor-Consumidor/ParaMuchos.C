//Esta solucion sirve si hay mas de un productor y consumidor.
// El mutex va donde la cantidad es mayor a 1
Object[] buffer = new Object(N); 
Semaphore vacio = new Semaphore(N);
Semaphore lleno = new Semaphore(0);
Semaphore mutexProducir = new Semaphore(1);
Semaphore mutexConsumir = new Semaphore(1);
global int inicio = 0;
global int fin = 0;

producir() {
     return new Object()  //otro buffer
}

consumir( buffer ) { 
    print("Consumiendo el buffer")
}
thread Productor {
    while(true){
        vacio.acquire()
        mutexProducir().acquire();//esta es la diferencia
        buffer[inicio] = producir();
        fin = ( fin + 1 ) % N;
        mutexProducir().release();//esta es la diferencia
        lleno.release()
    }
}
thread Consumidor {
    while(true){
        // inicialmente no hay nada para consumir, por lo tanto tengo que esperar a que me avisen
        lleno.acquire();
        mutexConsumir.acquire(); //esta es la diferencia
        consumir(buffer[fin]);
        fin = ( fin + 1 ) % N;
        mutexConsumir.release(); //esta es la diferencia
        vacio.release(); 
    }
}