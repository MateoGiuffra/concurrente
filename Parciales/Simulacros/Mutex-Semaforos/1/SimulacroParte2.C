// SEMAFOROS
// Entendí cualquier cosa y me invente un ejercicio donde hay una cantidad
// "infinita" de apostadores que van llegando, piden permiso para apostar
// y se quedan esperando hasta que al crupier se le cante arrancar la ronda. 
// Tambien estoy suponiendo que hay UN único crupier. 
// Despues el resto se parece. 
global int valor = null; 
global Semaphore rondaActual = new Semaphore(0); 
global Semaphore noVaMasSemaforo = new Semaphore(0); 
global Semaphore terminoGestionDePago = new Semaphore(0); 
global Semaphore mutexCantApostadores = new Semaphore(1); 
global int cantApostadores = 0; 

thread Apostador (montoInicial) {
    int monto = montoInicial;
    while (monto > 0) {
        rondaActual.acquire(); 
        miApuesta = randint(0,32);
        
        mutexCantApostadores.acquire();
        cantApostadores++;
        mutexCantApostadores.release();
        
        noVaMasSemaforo.acquire(); 

        if (miApuesta == valor){
            print("Gané!");
            monto += valor * 32;  
        } else {
            print("Perdí!")
            monto -= miApuesta; 
            if (monto <= 0){
                print("No, mi casa!");
            }
        }
        gestionDePagoFinalizada.release();
    }
} 

thread Crupier () {
    while (true) {
        sleep(1000ms) // espera a que se unan
        mutexCantApostadores.acquire();

        rondaActual.release(cantApostadores);
        cantApostadores = 0;
        
        mutexCantApostadores.release();

        valor = randint(0, 32); 

        noVaMasSemaforo.release(cantApostadores);

        gestionDePagoFinalizada.acquire(cantApostadores);
        
        mutexCantApostadores.acquire();
        cantApostadores = 0;
        mutexCantApostadores.release();
    }
}

// Ahora si, la version que piden: 
global int valor = null; 
global Semaphore rondaActual = new Semaphore(0); 
global Semaphore noVaMasSemaforo = new Semaphore(0); 
global Semaphore terminoGestionDePago = new Semaphore(0); 


// único thread
thread Apostador (montoInicial) {
    int monto = montoInicial;
    while (monto > 0) {
        rondaActual.acquire(); 
        miApuesta = randint(0,32);
        
        noVaMasSemaforo.acquire(); 

        if (miApuesta == valor){
            print("Gané!");
            monto = valor * 32;  
        } else {
            print("Perdí!")
            monto -= miApuesta; 
            if (monto <= 0){
                print("No, mi casa!");
            }
        }
        gestionDePagoFinalizada.release();
    }
}

thread Crupier () {
    while (true) {
        rondaActual.release();
        
        valor = randint(0, 32); 

        noVaMasSemaforo.release();

        gestionDePagoFinalizada.acquire();
    }
}

// b
// Mi interpretacion: Cada jugador tiene su propia ronda con el crupier,
// aunque me parece raro. 
global int valor = null; 
global Semaphore[] rondas = new Semaphore[N];  // todos en 0
global Semaphore[] noVaMasSemaforos = new Semaphore[N];  // todos en 0
global Semaphore[] gestionesDePagoFinalizada = new Semaphore[N];  // todos en 0

// único thread
thread Apostador (id, montoInicial) {
    int monto = montoInicial;
    while (monto > 0) {
        rondas[id].acquire(); 
        miApuesta = randint(0,32);
        
        noVaMasSemaforo[id].acquire(); 

        if (miApuesta == valor){
            print("Gané!");
            monto = valor * 32;  
        } else {
            print("Perdí!")
            monto -= miApuesta; 
            if (monto <= 0){
                print("No, mi casa!");
            }
        }
        gestionesDePagoFinalizada[id].release();
    }
}

thread Crupier () {
    while (true) {
        for i in range(N){
            rondas[i].release();

            valor = randint(0,32); 

            noVaMasSemaforos[i].release();

            gestionesDePagoFinalizada[i].acquire();
        }
    }
}