Semaphore permisoPasajeros = new Semaphore(1, True);
Semaphore permisoDespacharValija = new Semaphore(0);
Semaphore avisarValijaDespachada = new Semaphore(0);
Semaphore entregarDocumentacion = new Semaphore(0);
Semaphore entregarTuplaDeNums = new Semaphore(0);

Semaphore permisoPista = new Semaphore(1);  // porque hay una única pista
Semaphore[] permisoPuertas = new Semaphore[M]; // Todos con 1

Semaphore[] permisosSubirseAlAvion = new Semaphore[K]; // Todos con 0 
Semaphore[] permisosBajarseDeAvion = new Semaphore[K]; // Todos con 0

Semaphore[] pasajeroSeSubeAlAvion = new Semaphore[K]; // Todos con 0 
Semaphore[] pasajeroSeBajaDelAvion = new Semaphore[K]; // Todos con 0 


global Documentacion docDePasajeroActual = null; 
global (int, int) numVueloYnumPuerta = (null, null);


thread Pasajero (id) {
    // checkin
    permisoPasajeros.acquiere();

    docDePasajeroActual = entregarDocumentacion(id);
    entregarDocumentacion.release();
    
    permisoDespacharValija.acquiere();
    avisarValijaDespachada.release();

    entregarTuplaDeNums.acquire();
    numVuelo, numPuerta = docDePasajeroActual; 
    
    permisoPasajeros.release();
    // parte del viaje 
    permisosSubirseAlAvion[numVuelo].acquiere();
    pasajeroSeSubeAlAvion[numVuelo].release();
    
    permisosBajarseDeAvion[numVuelo].acquire();
    pasajeroSeBajaDelAvion[numVuelo].release();
}

theead Recepcionista () {
    while (true){
        entregarDocumentacion.acquire();
        
        permisoDespacharValija.release();
        avisarValijaDespachada.acquire(); 

        numVueloYnumPuerta = entregaIdYEmbarqueVuelo(docDePasajeroActual);
        entregarTuplaDeNums.release();
    }
}

thread Avion (numVuelvo, destinoFijo, capacidadMaxima) {
    while (true) {
        vuelaAlAeropuertoOrigen()
        numPuerta = obtienenIdPuertaEmbarque(); 
        // pide sitio para aterrizar
        permisoPista.acquiere();
        aterrizar()
        permisoPista.release();
        // pido permiso para acercarme a mi puerta de embarque
        permisoPuertas[numPuerta].acquire(); 
        meAcomodo();
        // una vez que esta acomodado en la puerta de embarque, 
        // pregunta N veces si estan todos siendo N la capacidadMaxima
        repeat (capacidadMaxima) { permisosSubirseAlAvion[numVuelo].release(); }
        repeat (capacidadMaxima) { pasajeroSeSubeAlAvion[numVuelo].acquire(); }
        // pide permiso para despegar
        permisoPista.acquiere();
        // libera el permiso de la puerta
        permisoPuertas[numPuerta].release(); 
        despegar();
        // libera el permiso del despliegue
        permisoPista.release();
        // viaja a destino
        viajoADestino(destinoFijo);
        // cuando llega espera a que todos bajen
        repeat (capacidadMaxima) { permisosBajarseDeAvion[numVuelo].release(); }
        repeat (capacidadMaxima) { pasajeroSeBajaDelAvion[numVuelo].acquire(); }
    }
 
}