// archivo que muesta la estructura de split mutex en el contexto de productor-consumidor

Object buffer = new Object(); 
Semaphore vacio = new Semaphore(1);
Semaphore lleno = new Semaphore(0);

producir() {
    return new Object()  //otro buffer
}

consumir( buffer ) { 
    print("Consumiendo el buffer")
}
thread Productor {
    while(true){
        vacio.acquire()
        buffer = producir()
        lleno.release()
    }
}
thread Consumidor {
    while(true){
        // inicialmente no hay nada para consumir, por lo tanto tengo que esperar a que me avisen
        lleno.acquire()
        consumir(buffer)
        vacio.release()
    }
}