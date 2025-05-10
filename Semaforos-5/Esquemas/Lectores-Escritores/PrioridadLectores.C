global Semaphore mutexL   = new Semaphore(1); //mutex para evitar perdidas de sumas o restas
global Semaphore mutexP   = new Semaphore(1); //semaforo para encolar a escritores con tal de darle MAS prioridad a los lectores
global Semaphore permisoE = new Semaphore(1); //permiso de escritores: para que haya SOLO uno escribiendo 
global int lectores = 0; // contador para saber si soy el primero o el ultimo


thread Lector {
    mutexL.acquire();
    contador++;
    if lectores == 1 
        permisoE.acquire();
    mutexL.release();

    leer();
    
    mutexL.acquire();
    contador--;
    if lectores == 0 
        permisoE.release();
    mutexL.release();
}

thread Escritor {
    mutexP.acquire();
    mutexE.acquire();
    escribir();
    mutexE.release();
    mutexP.release();
}