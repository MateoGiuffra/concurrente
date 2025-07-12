camillas = new Semaphore(10, true);
revistas = new Semaphore(4, false);

thread Donante {
    noQuieroRevista = new Semaphore(0);

    thread EsperaCamilla {
        camillas.acquire();
        noQuieroRevista.release();
        // dona
        camillas.release();
        // se va
    }

    thread EsperaRevista {
        revistas.acquiere();
        noQuieroRevista.acquire();
        revistas.release();
    }
}