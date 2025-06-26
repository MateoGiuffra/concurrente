global Semaphore serAtendido = new Sempahore(4, true);
global Semaphore revistas = new Sempahore(10);
global Semaphore mutexCantRevistas = new Sempahore(1);
global Semaphore mutexCantCamillas = new Sempahore(1);

global int camillas = 4;
global int revistas = 10;

thread Donante () {
    if (camillas == 0) {
        if (revistas < 0) {
             mirarTv();
        }
        revistas.acquire();
        mutexCantRevistas.acquire();
        revistas--;
        mutexCantRevistas.release();

        serAtendido.acquire();
        
        mutexCantRevistas.acquire();
        revistas++;
        mutexCantRevistas.release();
        revistas.release();

        donarSangre();
    } else {
        serAtendido.acquire();
        donarSangre();
    }
}


void donarSangre() {
    mutexCantCamillas.acquire();
    camillas--;
    mutexCantCamillas.release();
    // sacar sangre
    mutexCantCamillas.acquire();
    camillas++;
    mutexCantCamillas.release();
}
