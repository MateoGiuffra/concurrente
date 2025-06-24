// Esta solucion sirve para N producciones 
// Y si hay mas de un productor y consumidor.
Object[] buffer = new Object[N]; 
Semaphore vacio = new Semaphore(N);// este es para los N espacion disponibles que hay inicialmente
Semaphore lleno = new Semaphore(0);// este es para los consumidor, primero no pueden consumir porque esta vacia 
Semaphore mutexProducir = new Semaphore(1); // mutex para que un productor no produzca en el mismo lugar que otro 
Semaphore mutexConsumir = new Semaphore(1); // mutex para que dos consumidores no quieran consumir en el mismo lugar 
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
        mutexProducir().acquire();
        buffer[inicio] = producir();
        inicio = ( inicio + 1 ) % N;
        mutexProducir().release();
        lleno.release()
    }
}
thread Consumidor {
    while(true){
        // inicialmente no hay nada para consumir, por lo tanto tengo que esperar a que me avisen
        lleno.acquire();
        mutexConsumir.acquire(); 
        consumir(buffer[fin]);
        fin = ( fin + 1 ) % N;
        mutexConsumir.release(); 
        vacio.release(); 
    }
}