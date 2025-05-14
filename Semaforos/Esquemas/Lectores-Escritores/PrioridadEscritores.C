// La idea de este es que si un escritor quiere escribir, se pone en la cola hasta que llegue su turno. No espera a que no haya nadie leyendo

// ahora el PRIMER escritor le roba el permiso de lectura a los lectores justamente
// y el ultimo escritor lo libera para que los lectores puedan seguir leyendo 

global Semaphore mutexL   = new Semaphore(1); //mutex para evitar perdidas de sumas o restas de lectores
global Semaphore mutexE   = new Semaphore(1); //mutex para evitar perdidas de sumas o restas de escritores
global Semaphore mutexP   = new Semaphore(1); //semaforo para encolar a lectores con tal de darle MAS prioridad a los escritores
global Semaphore permisoE = new Semaphore(1); //permiso de escritores: para que haya SOLO uno escribiendo 
global Semaphore permisoL = new Semaphore(1); //permiso de lectores: para que el escritor se los pueda robar 
global int lectores = 0; // contador para saber si soy el primero o el ultimo
global int escritores = 0;

thread Escritor {
    mutexE.acquire()
    escritores++; 
    if escritores == 1
        permisoL.acquire();
    mutexE.release()

    mutexE.acquire();
    escribir();
    mutexE.release();
    
    mutexE.acquire()
    escritores--; 
    if escritores == 0
        permisoL.release();
    mutexE.release()
    
}

thread Lector {
    mutexP.acquire();
    permisoL.acquire();
    mutexL.acquire();
    contador++;
    if lectores == 1 
    permisoE.acquire();
    mutexL.release();
    permisoL.release();
    mutexP.release();
    
    leer();
    
    mutexL.acquire();
    contador--;
    if lectores == 0 
        permisoE.release();
    mutexL.release();
}
