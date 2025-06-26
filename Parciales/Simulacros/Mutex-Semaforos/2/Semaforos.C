Semaphore[] estaciones = new Semaphore[(1,1,1,1,1), true]; 

thread Vehiculo () {
    for i in range(5){
        estaciones[i].acquire(); 
        serLavado();
        if (i != 5){
            estaciones[i+1].acquire()
            irProxEstacion();
        }
        estaciones[i].release(); 
    }
}

