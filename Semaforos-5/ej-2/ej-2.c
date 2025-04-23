/* 
Ejercicio 2. Para cruzar un determinado r ́ıo, se tiene un peque ̃no bote que lleva a la gente
que lo necesite de una costa a la otra. El bote tiene capacidad para una persona y s ́olo hace
el recorrido en una direcci ́on (en una primera instancia, el viaje de regreso no lleva pasajeros).
Las personas se van acercando a la orilla de partida y esperan poder subir al bote, en orden de
llegada. Aquella que lo logra, se sube y se acomoda en el asiento, lo cual toma unos minutos. Una
vez acomodada la persona, el bote sale hacia la costa opuesta. Durante ese inter ́ın, la persona a
bordo debe esperar. Al llegar, la persona debe descender (que, de nuevo, toma algo de tiempo),
y una vez que termin ́o de bajar, el bote regresa a la costa original para tomar a la siguiente
persona.
a) Modele el escenario descrito utilizando un thread transbordador para el bote y uno persona
para cada persona que llegue a la costa. Modele las esperas a realizar mediante el uso de
semaforos.
*/

Semaphore asientoEnBote  = new Semaphore(0, true); // Con 0 permisos por que no hay nadie en el bote.
//  Con true indicamos que es un semáforo FIFO
// FIFO para que el primero en llegar sea el primero en salir // No modelamos una Queue. El semaforo con true es una queue implicita. 
Semaphore personaSentada = new Semaphore(0); //empieza en 0 porque inicialemente no hay nadie sentado en el bote
Semaphore llegoADestino = new Semaphore(0); // empieza en 0 porque el bote no ha llegado a la costa
Semaphore seBajo = new Semaphore(0); // empieza en 0 porque el bote no ha llegado a la costa


thread transborador {
    while (true){
        // Llega a la orilla 
        asientoEnBote.release();
        personaSentada.acquire();
        // Bote viaja a la costa
        llegoADestino.release();
        seBajo.acquire();
        // Regresa a la costa original 
    }
}

thread persona {
    // Llega a la orilla 
    asientoEnBote.acquire();
    // Subir al bote < tomó tiempo >
    personaSentada.release();
    llegoADestino.acquire();
    // Bajarse del bote < tomó tiempo >
    seBajo.release();
    // Ya termino
}

// OTRA VERSION CON 'asientoEnBote' CON UN PERMISO
Semaphore asientoEnBote  = new Semaphore(1, true); // Con 0 permisos por que no hay nadie en el bote.
//  Con true indicamos que es un semáforo FIFO
// FIFO para que el primero en llegar sea el primero en salir // No modelamos una Queue. El semaforo con true es una queue implicita. 
Semaphore personaSentada = new Semaphore(0); //empieza en 0 porque inicialemente no hay nadie sentado en el bote
Semaphore llegoADestino = new Semaphore(0); // empieza en 0 porque el bote no ha llegado a la costa
Semaphore seBajo = new Semaphore(0); // empieza en 0 porque el bote no ha llegado a la costa


thread transborador {
    while (true){
        personaSentada.acquire();
        // Bote viaja a la costa
        llegoADestino.release();
        seBajo.acquire();
        // Regresa a la costa original 
    }
}

thread persona {
    // Llega a la orilla 
    asientoEnBote.acquire();
    // Subir al bote < tomó tiempo >
    personaSentada.release();
    llegoADestino.acquire();
    // Bajarse del bote < tomó tiempo >
    seBajo.release();
    // Ya termino
}

// punto B
/*

b) 
Suponga ahora que se cuenta con un transbordador con capacidad para N personas, y que
en esta oportunidad el barco lleva gente tanto en el viaje de ida como en el de regreso,
teniendo la siguiente din ́amica.
    - Empieza en la costa oeste (podemos pensar que es la costa “0”).
    - Espera en una costa hasta que haya gente acomodada en los N asientos.
    - Viaja hasta la costa este (“1”).
    - Amarra, permitiendo que los pasajeros desciendan.
    - Repite el procedimiento desde el principio, en la costa actual ⚠!!

Tenga en cuenta que el thread pasajero puede llevar un par ́ametro que indica en qu ́e costa
comienza su viaje.
Se proponen dos variantes:
    (i) Cuando el bote llega a una costa, espera que todos sus ocupantes terminen de bajar
    antes de permitir subir a la gente que est ́a esperando all ́ı.

    (ii) Cuando el bote llega a una cosa, la gente empieza a bajar y subir en forma concurrente,
    s ́olo se busca que no hayan m ́as de N personas sobre el barco en un momento dado.
*/ 

// Semaphore asientoEnBote_costa0  = new Semaphore(0, true);
// Semaphore asientoEnBote_costa1  = new Semaphore(0, true);
Semaphore[] asientoEnBote  = new Semaphore[2]{0, 0}; // FUERTES 
Semaphore personaSentada = new Semaphore(0); 
Semaphore llegoADestino = new Semaphore(0); 
Semaphore seBajo = new Semaphore(0); 


thread transborador {
    costaActual = 0;
    while (true){
        repeat(N) asientoEnBote[costaActual].release();
        repeat(N) personaSentada.acquire();
        // Bote viaja a la costa
        costaActual = (costaActual + 1) % 2;
        repeat(N) llegoADestino.release();
        repeat(N) seBajo.acquire();
        // Regresa a la costa original 
    }
}

thread persona(int costaInicial) {
    // Llega a la orilla 
    // Esto vale y anda pero vamos a hacer una algo mas elegante 
    // if (costaInicial == 0) {
    //     asientoEnBote_costa0.acquire();
    // } else {
    //     asientoEnBote_costa1.acquire();
    // }
    asientoEnBote[constaInicial].acquire();

    // Subir al bote < tomó tiempo >
    personaSentada.release();
    llegoADestino.acquire();
    // costaInicial = (costaActual + 1) % 2; esto si tendrian que volver
    // Bajarse del bote < tomó tiempo >
    seBajo.release();
    // Ya termino
}


// B-2
Semaphore[] boteEnOrilla = new Semaphore[2]{0, 0}; // FUERTES 
Semaphore asiendoEnBote  = new Semaphore(N); 
Semaphore personaSentada = new Semaphore(0); 
Semaphore[] llegoADestino  = new Semaphore[2]{0,0}; 

thread transborador {
    costaActual = 0;
    while (true){
        repeat(N) boteEnOrilla[costaActual].release();
        repeat(N) personaSentada.acquire();
        // Bote viaja a la costa opuesta
        costaActual = (costaActual + 1) % 2;
        repeat(N) llegoADestino[costaActual].release();
    }
}

thread persona(int costaInicial) {
    costaOpuesta = (costaInicial + 1) % 2;
    // Llega a la orilla 
    boteEnOrilla[costaInicial].acquire();
    asiendoEnBote.acquire(); // Esto es para que no suban mas de N personas al bote
    // Subir al bote <== tomó tiempo
    personaSentada.release();
    llegoADestino[costaOpuesta].acquire();
    // Bajarse del bote <== tomó tiempo
    asiendoEnBote.release();
    // Ya termino
}