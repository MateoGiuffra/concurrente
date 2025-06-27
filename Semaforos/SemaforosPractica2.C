global int impar = N;  
global int N = impar; 
global int suma = 0
global int i = 0

ciclo = new Semaphore(1)
updateImpar = new Semaphore(0)
updateSuma = new Semaphore(0)
permisoPrint =  new Semaphore(0)

thread generador () {
    for (i < N;){
        ciclo.acquiere()
        i++
        updateSuma.acquiere()
        
        impar += 2
        updateImpar.release()

        ciclo.release()
    }
    permisoPrint.acquire()
    print(suma)
}

thread acumulador() {
    repeat(N){
        updateImpar.acquire()
        suma += impar
        updateSuma.release()
    }
    permisoPrint.release()
}

// 2
personasABordo = new Semaphore(1, true)
hayPersonaLista = new Semaphore(0)
seBajoLaPersona = new Semaphore(0)
estaBoteEnOrigen = new Semaphore(1)

thread transbordador{
    while (true) {
        //esta en origen
        estoyEnOrigen.release()
        hayPersonaLista.acquire()
        //llega a destino y espera a que se baje
        seBajoLaPersona.acquiere()
        // vuelve
        estaBoteEnOrigen.release()
    }
   
}

thread persona {
    personasABordo.acquiere()
    estaBoteEnOrigen.acquire()
    // se acomoda
    hayPersonaLista.release()
    // viajan
    seBajoLaPersona.release()
    // se baja y lo indica
    personasABordo.release()
}

// 10
global Semaphore puente = new Semaphore(1);
global JSON cantAutos = {
    "izq": 0,
    "der": 0
};
a a a ====b=b=b= b b b   
// dir: "izq" | "der"
thread Auto (dir) { 
    mutex.acquire();

    cantAutos[dir]++;
    if (cantAutos[dir] == 1){
        permisoPuente.acquire();
    }
    mutex.release();
    
    // cruzo puente

    mutex.acquire();
    cantAutos[dir]--;
    if (cantAutos[dir] == 0){
        permisoPuente.release();
    }
    mutex.release();
}

//b
global Semaphore puente = new Semaphore(1);
global JSON cantAutos = {
    "izq": 0,
    "der": 0
};
global Semaphore semAutosIzq = new Semaphore(3);
global Semaphore semAutosDer = new Semaphore(3);

global JSON semaforos = {
    "izq": semAutosIzq,
    "der": semAutosDer
};

// dir: "izq" | "der"
thread Auto (dir) { 
    semaforos[dir].acquire();
    
    mutex.acquire();
    cantAutos[dir]++;
    if (cantAutos[dir] == 1){
        permisoPuente.acquire();
    }
    mutex.release();
    
    // cruzo puente

    mutex.acquire();
    cantAutos[dir]--;
    if (cantAutos[dir] == 0){
        permisoPuente.release();
    }
    mutex.release();

    semaforos[dir].release();
}

// 8
global int cantOficinistas = 0; 
global Semaphore permisoToiletes = new Semaphore(8);
global Semaphore personalDeLimpieza = new Semaphore(1);
global Semaphore mutex = new Semaphore(1);

thread Oficinista () {
    mutex.acquiere();
    cantOficinistas++;
    if cantOficinistas == 1: 
        personalDeLimpieza.acquire();
    mutex.release();

    permisoToiletes.acquire();
    // ir al baño
    mutex.acquiere();
    cantOficinistas--;
    if cantOficinistas == 0: 
        personalDeLimpieza.release();
    mutex.release();
    
    permisoToiletes.release();
}

thread Personal () {
    personalDeLimpieza.acquire();
    permisoToiletes.acquire();
    // limpio
    personalDeLimpieza.release();
    permisoToiletes.release();
}
// 9
Semaphore cargarCombustible = new Semaphore(6, true);
Semaphore descargarCombustible = new Semaphore(1);
Semaphore mutex = new Semaphore(1);
Semaphore mutexCamion = new Semaphore(1);
global int camiones = 0;

thread Vehiculo () {
    cargarCombustible.acquiere();
    if (camiones >= 1) {
        mutex.acquire();
        cantVehiculosEsperando++;
        mutex.release();
        combustibleDescargado.acquire();
        
        mutex.acquire();
        cantVehiculosEsperando--;
        mutex.release();
    }
    cargarCombustible.release();
}

thread Camion () {
    descargarCombustible.acquire();

    mutexCamion.acquire();
    camiones++;
    mutexCamion.release();
    // dejar combustible
    mutexCamion.acquire();
    camiones--;
    mutexCamion.release();
    combustibleDescargado.release(cantVehiculosEsperando);
    
    descargarCombustible.release();
}