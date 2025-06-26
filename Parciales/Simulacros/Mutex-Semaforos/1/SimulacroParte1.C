/*
DOS EJERCICIOS, uno de cada tema
si el flag de alguno de los dos lados esta prendido y es su turno, espero
inanicion starvation

a) No cumple mutex porque si un thread junto con el de su derecha ejecutan al mismo tiempo de forma secuencial
desde izq = id... hasta turno= der, el valor de turno va a ser pisado por el thread que va un paso mas atras
haciendo que el turno sea el de la izquierda del todo provocan que la condicion no de true para ninguno de los
dos thread ya que el flag del de la izquierda de todo nunca se prendio y no es turno de ninguno de los dos threads
que estan ejecutando

b) Si cumple con garantia de entrada por lo dicho anteriormente.
Siempre da false el while, entonces los tres entran. 

c)
Si:
turno = 0
estan ejecutando
el thread 1 y 2. 
- Para el thread con
id 1:
    - flags[0] false 
    porque no se ejecuta
    or 
    - su der es 2 que
    es distinto de 0 
id 2: 
    - su izq es 1,
    o sea distinto de 0
    or    
    - su der es 0, y flags[0]
       esta marcado como 0, si
todavia no se ejecutando el thread de 
id 0

En resumen, tampoco cunple Mutex ya que cada uno entra a la seccion critica
porque su while es false 

Ejercicio 2 [Semáforos]
Hay 5 estaciones: 
    - Remojado
    - Enjabonado
    - Enjuage 
    - Secado
    - Encerado
Por cada estacion hay una maquina lavadora y un solo vehiculo. 
El vehiculo, al terminar su etapa va a la siguiente de forma secuencial.
Y hay un vehiculo solo por estacion, o sea que no puede avanzar si hay
alguien adelante. 
Pero las maquinas pueden lavar en simultaneo. 

[NOTA]
- Lavar no es atomico. 
- Desplazar lleva tiempo. Se considera que en cierto momento un vehiculo
puede estar en dos estaciones si se esta desplazando.

ROLES: 
    - maquina lavadora
    - vehiculo 
*/
Semaphore[] lavadoras    =  new Semaphore[5]{1,1,1,1,1};
Semaphore mutexDesplazar =  new Semaphore(1);
Semaphore termineDeLavar =  new Semaphore(0);
thread maquinaLavadora(id){
    while(true){
        //lava
        // termineDeLavar.release()
        lavadoras[id].acquire()

    }
}

thread vehiculo{
        lavadoras[lavadoraActual].acquire()
        siguiente = (idLavadora + 1) % 5
        // termineDeLavar.acquiere()
        lavadoras[siguiente].acquire()
        mutexDesplazar.acquire()
        // desplazo
        mutexDesplazar.release()
        lavadoras[lavadoraActual].release()
}

// res profe
// a)
Semaphore[] hayVehiculoEnEstacion = new Semaphore[]{0,0,0,0,0};
Semaphore[] trabajoTerminado = new Semaphore[]{0,0,0,0,0};
Semaphore[] estacionLibre = new Semaphore[]{1,1,1,1,1};

thread MaquinaLavadora{
    while(true){
        hayVehiculoEnEstacion[id].acquiere();
        // realizar trabajo
        trabajoTerminado[id].release();
    }
}

thread Vehiculo{
    for i in range(5){
        estacionLibre[i].acquiere();
        // ir a la estacion i 
        if (i > 0) {
            estacionLibre[i-1].release();
        }
        hayVehiculoEnEstacion[i].release();
        trabajoTerminado[i].acquiere();
    }
    // Salir de la estacion 4
    estacionLibre[4].release();
    // Retirarse
}

// b)
Semaphore[] hayVehiculoEnEstacion = new Semaphore[]{0,0,0,0,0,0,0};
Semaphore[] trabajoTerminado = new Semaphore[]{0,0,0,0,0,0,0};
Semaphore[] estacionLibre = new Semaphore[]{1,1,1,1,1,1,1};
Semaphore robotDisponible = new Semaphore(0);
Semaphore mutex = new Semaphore(1);

// variable de int donde el robot va a decir cual es su id
global int idRobotDisponible= NULL

thread MaquinaLavadora{
    while(true){
        hayVehiculoEnEstacion[id].acquiere();
        // realizar trabajo
        trabajoTerminado[id].release();
    }
}

thread Vehiculo{
    // llegar al centro de lavado
    estacionLibre[0].acquire(); 
    // ir a la estacion 0 
    robotDisponible.acquire();
    int miRobot = idRobotDisponible; 
    mutex.release();

    // ya se cual es mi robot
    puedeSubirse[mi_robot].release()
    robotSubido[mi_robot].acquire()

    for i in range(1...5){
        estacionLibre[i].acquiere();
        // ir a la estacion i 
        if (i > 0) {
            estacionLibre[i-1].release();
        }
        hayVehiculoEnEstacion[i].release();
        trabajoTerminado[i].acquiere();
    }
    // Ir a la estacion 6: 
    estacionLibre[6].acquiere();
    // Salir de la estacion 5:
    estacionLibre[5].release();

    // Retirarse
}

thread AspiradoraRobotica(idRobot){
    while(true){
        mutex.acquire(); // puedo sobreescribir idRobotDisponible con el mio? 
        //                  si cuando no otro vehiculo usandolo
        idRobotDisponible = idRobot;
        robotDisponible.release();
        puedeSubirse[mi_robot].acquire()
        robotSubido[mi_robot].release()
    
        // Subir al auto

        // Limpiar interior del auto

        // Descender del auto 


    }
}

// terminar el protocolo del robot para que se baje
// c => starvation