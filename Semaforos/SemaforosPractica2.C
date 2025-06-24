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