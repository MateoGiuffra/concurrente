// es mi solución y esta verificada por un profe, asi que confia
// a
Semaphore permisoAprendiz = new Semaphore(2, True)
Semaphore lleno = new Semaphore(0)

Semaphore permisoReseniar = new Semaphore(1)

Semaphore resenias = new Semaphore(1)
Semaphore sushis = new Semaphore(1)

global int cantSushis = 0
global int cantResenias = 0

thread Aprendiz () { 
    while (true) {
        permisoAprendiz.acquire()
        // hago sushi
        permisoAprendiz.release()
        
        // lo dejo en la mesa
        sushis.acquiere()
        sushis++; 
        sushis.release()

        if cantResenias >= 3: 
            resenias.acquire()
            cantResenias -= 3;
            resenias.release()

        lleno.release();
    }    
}

thread SushiMan() {
    while (true) {
        lleno.acquiere();
        permisoReseniar.acquiere(); 
        // come sushi 
        sushis.acquiere()
        cantSushis--;
        sushis.release()
        // deja reseña
        resenias.acquiere()
        resenias++
        resenias.release()

        permisoReseniar.release();
    }
}

// b
Semaphore permisoAprendiz = new Semaphore(2, True);
Semaphore haySushiEnMesa = new Semaphore(0);
Semaphore mutex = new Semaphore(1);

Semaphore permisoReseniar = new Semaphore(1);

Semaphore resenias = new Semaphore(1);
Semaphore sushis = new Semaphore(1);

global int cantSushis = 0
global int cantResenias = 0

// nuevo
global int cantProductores = 0
Semaphore inspectores = new Semaphore(1);

thread Inspector () {
    while (true) {
        inspectores.acquiere()
        permisoProducir.acquiere(2)
        // inspecciona y sale 
        permisoProducir.release(2)
        inspectores.release()
    }
}

thread Aprendiz () { 
    while (true) {
        permisoAprendiz.acquiere();
        mutex.acquiere();
        cantProductores++; 
        if (cantProductores == 1) {
            inspectores.acquire();
        }
        mutex.release();
        // cocina
        mutex.release();
        cantProductores--; 
        if (cantProductores == 0) {
            inspectores.release();
        }
        mutex.release();
        permisoAprendiz.release();

        sushis.acquiere();
        sushis++; 
        sushis.release();
        // yendo a la mesa 
        haySushiEnMesa.release();
        
        if cantResenias >= 3: 
            resenias.acquire();
            cantResenias -= 3;
            resenias.release();
    }    
}

thread SushiMan() {
    while (true) {
        permisoReseniar.acquiere();

        haySushiEnMesa.acquiere();
        // come sushi 
        sushis.acquiere()
        cantSushis--;
        sushis.release()
        // deja reseña
        resenias.acquiere()
        resenias++
        resenias.release()

        permisoReseniar.release();
    }
}