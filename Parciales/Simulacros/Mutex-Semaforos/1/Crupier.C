global Semaphore permisoApostar = new Semaphore(0);
global Semaphore valorObtenido = new Semaphore(0);
global Pair<int, int> apuesta;//(numApostado, monto) 
global int valor; 

thread Apostador (int capitalInicial) {
    int miMonto = capitalInicial; 
    while (miMonto > 0) {
        permisoApostar.acquire();
        int num = elegirNumero();

        montoApostado = miMonto; 
        apuesta = (num, montoApostado); 
        miMonto = 0;

        apuestaHecha.release();
        valorObtenido.acquire();
        if (num == valor){
            miMonto += montoApostado * 36;
            print("Gané!")
        } else {
            print("Perdí!")
            if (miMonto <= 0){
                print("No, mi casa!")
            }
        }
    }
}

thread Crupier () {
    while (true) {
        permisoApostar.release();
        apuestaHecha.acquire();
        print("no va más")
        valor = girarRuleta();
        valorObtenido.release();

    }
}