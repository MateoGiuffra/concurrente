/*Ejercicio 1. Se busca computar la suma de los primeros N n ́umeros impares utilizando dos
threads llamados generador y acumulador, que deben cooperar entre s ́ı para resolver esta tarea.
Contamos con dos variables globales impar, que comienza inicializada en N, y suma, que comienza
inicializada en 0. Buscamos que generador se encargue de que impar contenga el valor i cuando
se deba sumar el i- ́esimo n ́umero impar, y que acumulador compute cu ́al es el i- ́esimo impar y lo
sume a suma. Al finalizar el c ́omputo, el thread generador debe imprimir el valor correcto de la
sumatoria.
a) Escriba un programa concurrente que funcione seg ́un esta din ́amica.
b) ¿Qu ́e modificaci ́on deber ́ıa hacerse si existieran m ́ultiples threads generador? ¿Y si hubieran
m ́ultiples threads acumulador? ¿Existe posibilidad de starvation?
*/

// a
impar = N 
suma = 0
Semaphore permisoAcumulador = new Semaphore(1)
Semaphore permisoGeneral = new Semaphore(1)

thread generador{
    while (impar > 1)
    {
        permisoGeneral.acquiere()
        impar --; 
        permisoAcumulador.release()
    }
    permisoGenerar.acquire()
    print(suma)
}

thread acumulador{
    while (impar != 1)
    {
        permisoAcumulador.acquire()
        suma += 2 * impar - 1
        permisoGenerador.release()
    }
    suma += 1 
    permisoGeneral.release()    
}

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

/*
Ejercicio 3. En un gimnasio hay cuatro aparatos, cada uno para trabajar un grupo muscular
distinto. Los aparatos son cargados con discos (el gimnasio cuenta con 20 discos, todos del mismo
peso). Cada cliente del gimnasio posee una rutina que le indica qu ́e aparatos usar, en qu ́e orden
y cuanto peso utilizar en cada caso (asuma que la rutina es una lista de tuplas con el n ́umero de
aparato a usar y la cantidad de discos cargar, la rutina podr ́ıa incluir repeticiones de un mismo
aparato). Como norma el gimnasio exige que cada vez que un cliente termina de utilizar un
aparato descargue todos los discos y los coloque en el lugar destinado a su almacenamiento (lo
que incluye usos consecutivos del mismo aparato).
a) Indique cuales son los recursos compartidos y roles activos.
b) Escriba un codigo que simule el funcionamiento del gimnasio, garantizando exclusi ́on mutua
en el acceso a los recursos compartidos y que est ́e libre de deadlock y livelock.
Ayuda: Considere modelar a los clientes como threads (cada uno con su propia rutina) y a
los aparatos como un arreglo de sem ́aforos.

[(numAparato, cantDiscos),(numAparato, cantDiscos)]

4 aparatos
20 discos
cliente -> rutina:
                - aparatos a usar
                - orden 
                - peso en cada aparto 
                - repeticiones por aparato

roles:
- cliente 

*/
p1 = [(1, 20),(1, 20)]
// []
p2 = [(1, 20),(1, 20)]

// 4 => 0 
// pj 5 => pj duerme 
// []

Semaphore[] aparatos = new Semaphore[4]{1,1,1,1} // FUERTE
Semaphore discos = new Semaphore(20)
Semaphore mutex = new Semaphore(1)

thread cliente(tupla){
    // a index de aparato
    // d cant de discos  
    for a, c in tuplas{
        aparatos[a].acquiere()  

        mutex.acquire()
        cantDiscos.acquire(d)
        mutex.release()
        // hacer rutina
        aparatos[a].release()  

        cantDiscos.release(d)
    }
}


/*
Ejercicio 4. 
En un famoso shopping de la ciudda se agrego un puesto de tintorerıa automatica
para que la gente pueda dejar su ropa mientras recorre los locales. Novedosamente, estas maquinas 
entregan un beeper a la gente que parpadea para indicar que la ropa ya esta lista para ser retirada. 
Hay K maquinas de lavado listas para funcionar. Cada persona que quiere utilizar el
servicio (en este ejemplo no modelaremos a quieres no lo requieran) espera que haya alguna
maquina disponible para serle asignada segun disponibilidad, carga su ropa y recibe su beeper.
Luego, se va a mirar locales, y si al terminar su beeper a ́un no parpadea, espera que lo haga
para volver al local y retirar sus prendas (Si el beeper parpadea mientras la persona a ́un esta
mirando locales, esta lo ignora hasta que est ́a por retirarse). Modele este escenario por medio de
semaforos. 
Procure que no suceda que una persona vaya a retirar su ropa cuando se termino de
procesar la de alguien mas. O sea el beeper es unico por persona. 

- K maquinas
- Persona elige una, carga sus cosas 
- Le dan beeper
- Espera a que suene el beeper
- Retira sus prendas


// */
// Semaphore[] maquinas = new Semaphore[K]{1 ... } // fuerte
// Semaphore[] beepers = new Semaphore[K]{1 ... } 
// Semaphore[] notificador = new Semaphore[K]{0 ... } 

// thread maquina{
//     // limpiando
//     while(true){
//         notificador[idMaquina].release()
//     }
// }

// thread cliente (idMaquina){
//     maquinas[idMaquina].acquiere()
//     // pone su ropa
//     beepers[idMaquina].acquiere()
//     // va a recorrer locales 
//     notificador[idMaquina].acquiere()
//     // va a retirar la ropa
//     beepers[idMaquina].release()
//     maquinas[idMaquina].release()
// }


Semaphore permisoUsar(1)
Semaphore hayMaq(0)
global proximaMaq = -1
Semaphore permisoCargarRopa[K]{0 ...}
Semaphore beepers[K]{0 ...}

thread maquina(id){
    while(true){
        permisoUsar.acquiere()
        proximaMaq = id 
        hayMaq.release()
        permisoCargar[id].acquire()
        // lavar
        beepers[miMaq].release()
        permisoDescargar[id].acquiere()
    }
}

thread persona(){
    hayMaq.acquiere()
    miMaq = proximaMaq
    permisoUsar.release()
    // cargar ropa
    permisoCargarRopa[miMaq].release()
    // recorrer 
    beepers[miMaq].acquire()
    // retirar
    permisoDescargar[miMaq].release()

}

/*
Ejercicio 6. Se avecina el partido super-mega cl ́asico entre dos equipos que llamaremos BJ y RP.
Para evitar conflictos en la cancha, se dispuso el siguiente mecanismo de control de acceso: 
No se permitir a que la diferencia entre la gente de la hinchada de BJ y la de gente de la hinchada
RP sea mayor que 1 (toda persona que va a ver el partido es de alguno de los dos equipos).
Cada persona que llegue a la cancha debe asegurarse de esta regla le permite el acceso. Si no,
esperar ́a hasta que pase alguien del equipo opuesto de manera de conseguir acceso. Una vez
que una persona entr ́o a la cancha, se quedar ́a hasta finalizar el partido (que no modelaremos,
estipulando que este sigue indefinidamente).
a) Modele este comportamiento utilizando Sem ́aforos.
b) Extienda la soluci ́on anterior contemplando que la cancha tiene una capacidad de N per-
sonas. Cada persona que logra entrar a la cancha ocupa un lugar, y como estos nunca
se liberan, en alg ́un momento la cancha estar ́a llena. En ese momento, toda persona que
llegue deber ́a retirarse sin tener la posibilidad de ingreso. Aseg ́urese, tambi ́en, que ninguna
persona se quede esperando indefinidamente.
c) El partido ya se jug ́o y result ́o uno de los m ́as  ́epicos de la historia. Por ello, se planific ́o pro-
yectarlo en el cine de la ciudad para que la gente pueda verlo en pantalla gigante. La gente
que desea asistir s ́olo debe ir al cine y retirar una entrada, disponible en un mostrador del
lobby (suponemos que las personas las toman de a una, aunque es posible que dos personas
se acerquen a buscar su entrada en momentos muy cercanos. No hay distinci ́on entre per-
sonas de un equipo y otro). La cantidad total de entradas es M , y si alguien llega luego de
que se hayan agotado, se retirar ́a del cine. En un horario determinado, el personal del cine
quita las entradas del mostrador y habilita el acceso a la sala las personas que tengan su
entrada. Luego, se espera a que todas las personas se hayan acomodado en alguna butaca,
el personal cierra las puertas, y comienza la proyecci ́on. Como en el caso anterior, pode-
mos pensar que la gente que entr ́o se queda mirando el partido indefinidamente. Modele
este nuevo escenario utilizando Sem ́aforos. Preste atenci ́on a que el personal del cine no se
quede esperando que se sienten m ́as personas que las que las que retiraron entradas.
*/

// a
Semaphore HinchadaDeBJ = new Semaphore(1);
Semaphore HinchadaDeRP = new Semaphore(1);

thread personaBJ{
    while (true){
        HinchadaDeBJ.acquiere(); 
        // entro a la cancha
        HinchadaDeRP.release(); 
    }
}

thread personaRP{
    while(true){
        HinchadaDeRP.acquiere(); 
        // entro a la cancha
        HinchadaDeBJ.release(); 
    }
}

// b
Semaphore HinchadaDeBJ = new Semaphore(1);
Semaphore HinchadaDeRP = new Semaphore(1);
global int cantDePersonas = 0; 
Semaphore mutex = new Semaphore(1); 

thread personaBJ(N (cantMaxDePersonasSoportadas)){
    while (cantDePersonas <= N){
        HinchadaDeBJ.acquiere(); 
        // entro a la cancha
        mutex.acquire();
        if (cantDePersonas == N){
            mutex.release();
            HinchadaDeRP.release(); 
            break; 
        } 
        cantDePersonas++;
        mutex.release();
        HinchadaDeRP.release(); 
    }
}

thread personaRP(N (cantMaxDePersonasSoportadas)){
    while(cantDePersonas <= N){
        HinchadaDeRP.acquiere(); 
        // entro a la cancha
        mutex.acquire();
        if (cantDePersonas == N){
            mutex.release();
            HinchadaDeBJ.release(); 
            break; 
        } 
        cantDePersonas++;
        mutex.release();
        HinchadaDeBJ.release(); 
    }
}

// c
int global cantEntradas = M; 
Semaphore mutexE = new Semaphore(1); // mutex para sacar la entrada
Semaphore mutexEntry = new Semaphore(1); // mutex para entrar a la sala
thread espectador (){
    while (cantEntradas > 0){
        mutexE.acquiere()
        if cantEntradas == 0 {
            mutexE.release()    
            break
        }
        cantEntradas--; 
        mutexE.release()
    }
    while (cantEntradas < M){
        // entran a la sala
        // sentarse
        
        mutexEntry.acquiere()
        if cantEntradas == 0 {
            mutexEntry.release()    
            break
        }
        cantEntradas++; 
        mutexEntry.release()
        while(true){
            // ven la peli indefinidamente
        }
    }
}