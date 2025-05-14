//Esta solucion sirve si solo hay un solo productor y consumidor
Object[] buffer = new Object(N); 
Semaphore vacio = new Semaphore(N);
Semaphore lleno = new Semaphore(0);
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
        buffer[inicio] = producir();
        fin = ( fin + 1 ) % N;
        lleno.release()
    }
}
thread Consumidor {
    while(true){
        // inicialmente no hay nada para consumir, por lo tanto tengo que esperar a que me avisen
        lleno.acquire();
        consumir(buffer[fin]);
        fin = ( fin + 1 ) % N;
        vacio.release(); 
    }
}