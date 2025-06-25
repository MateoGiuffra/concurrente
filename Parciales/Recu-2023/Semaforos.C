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
Semaphore permisoAprendiz = new Semaphore(2, True)
Semaphore lleno = new Semaphore(0)

Semaphore permisoReseniar = new Semaphore(1)

Semaphore resenias = new Semaphore(1)
Semaphore sushis = new Semaphore(1)

global int cantSushis = 0
global int cantResenias = 0

// nuevo
global int cantProductores = 0
Semaphore inspectores = new Semaphore(1)

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
        vacio.requiere();
        permisoAprendiz.acquiere();
        permisoAprendiz.release();

        sushis.acquiere()
        sushis++; 
        sushis.release()
        // yendo a la mesa 
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