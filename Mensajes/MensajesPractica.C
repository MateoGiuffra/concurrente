//1.a ✅

global Channel canal = new Channel()
global Channel canalN = new Channel()

process Cliente{
    mensaje = read()
    canalCuenta.send(mensaje)
}

process Servidor{
    int n = 0
    while (true){
        msj = canal.receive()
        if (msj == "sigue") {
            n++
        }
        if (msj == "cuenta") {
            print(n)
            n = 0
        }
    }
}

// 1.b
global Channel canal = new Channel()
global Channel canalN = new Channel()

process Cliente{
    mensaje = read()
    canalCuenta.send(mensaje)
    thread {
        n = canalN.receive()
        print(n)
    }
}

process Servidor{
    int n = 0
    while (true){
        msj = canal.receive()
        if (msj == "sigue") {
            n++
        }
        if (msj == "cuenta") {
            canalN.send(n)
            n = 0
        }
    }
}



// 2 ✅

process Servidor(){
    while(true){
        msg1 = c1.receive()
        msg2 = c2.receive()
        print(msg1 + msg2)
    }
}

// 3 ✅

global Channel serv; 
/*
La request tiene los campos: 
* channel: canal del thread
* type: read | write
* setter: el valor que sobreescribe la sharedVar
*/
process Servidor (){
    object sharedVar; 
    while (true){
        req = serv.receive()
        if req.type == "read" 
            req.channel.send(sharedVar)
        if req.type == "write" 
            sharedVar = req.setter
    }
}

// 4 (hice el b directamente)
/*
La request tiene los campos: 
* ch: canal del thread
* str: la string
*/ ✅

global Channel canal = new Channel(); 
process Servidor(){
    while(true){
        req = canal.receive()        
        strFormat = trim(req.str)
        req.ch.send(strFormat)
    }
}


// 5 
// esta es mi version, tengo que chequear si esta bien 🟨

Channel canal = new Channel(); 

process Client{
    Request req = new Request()
    res; 
    Channel channel = new Channel()
    req.channel = channel;
    do {
        number = read()
        req.number = number;
        canal.send(req)
        res = channel.receive()
    } while (res == "Mal") 
}

process Servidor {
    while(true){    
        req = canal.receive()
        thread (req){
                random = randint() 
                req.channel.send(random == req.number ? "Bien" : "Mal")
        }
    }
}

// Ej 6 🟨
// a)
Channel canalT = new Channel()
Channel canalR = new Channel()

process T {
    while (true) {
        mensaje = canalT.receive()
        mensajeCodificado = codificar(mensaje)
        canalR.send(mensajeCodificado)
    }
}

process C {
    miMensaje = read()
    canalT.send(miMensaje)
}

// b)
Channel canalT = new Channel()
Channel canalR = new Channel()

process T {
    canalAMandar = canalR
    while (true){
        req = canalT.receive();
        if (canalAMandar != req.canalCliente){
            canalAMandar = req.canalCliente
        }
        mensaje = req.mensaje()
        mensajeCodificado = codificar(mensaje)
        canalAMandar.send(mensajeCodificado)
    }
}

// c)
Channel canalT = new Channel()
Channel canalR = new Channel()
Channel canalK = new Channel()

process T {
    canalAMandar = canalR
    while (true){
        req = canalT.receive();
        key = canalK.receive();
        if (canalAMandar != req.canalCliente){
            canalAMandar = req.canalCliente
        }
        mensaje = req.mensaje()
        mensajeCodificado = codificar(mensaje, key)
        canalAMandar.send(mensajeCodificado)
    }
}


//Ej 7
//a ✅

process P {
    while (true) {
        req = canal3.receive() // espero msj del cliente, si no hay espero
        canal1.send(req) // se la mandamos a S para que procese
        calculo = canal2.receive() // recibimos de S el calculo
        canal4.send(calculo) // mandamos el calculo al cliente
    }
}

//b version vieja
process P {
    repeat(N){
        thread () {
            while (true) {
                req = canal3.receive() // espero msj del cliente, si no hay espero
                canal1.send(req) // se la mandamos a S para que procese
                calculo = canal2.receive() // recibimos de S el calculo
                canal4.send(calculo) // mandamos el calculo al cliente
            }
        }
    }
}

//b 🟨
process P {
    Channel canalP = new Channel();
    Channel canalClientes = new Channel()
    canalClientes.send(0) // inicializo el contador
    canalP.send([])
    repeat(N){ // creo N threads
        thread(canalP, canalClientes){ 
            while(true){
                msjCliente = canal3.receive() // recibo msj del cliente, si no hay espero
                canal1.send(msjCliente) // se la mandamos a S para que procese
                calculo = canal2.receive() // recibimos de S el calculo, si todavia no termina espero
                copiaDeLaLista = canalP.receive()
                copiaDeLaLista.add(calculo)
                // si ya tengo todas las respuestas, las devuelvo en orden al cliente
                if (copiaDeLaLista.size() == N) {
                    for index, c in enumerate(copiaDeLaLista) {
                     canal4.send((c, index, canalClientes)) // mandamos el calculo al cliente correspondiente
                    }
                    canalP.send([]) // limpio la lista
                  } else {
                    canalP.send(copiaDeLaLista)
                }
            }
        }
    }
}

process C1 {
    canal3.send(calculoAHacer)
    calculo, numCliente, canalClientes = canal4.receive()
    // recibo un calculo, el numero que indica a quien pertenece el calculo y el canalClientes

    // recibo el num / turno actual
    numActual = canalClientes.receive()
    // me guardo mi copia
    miNum = numActual
    // incremento y devuelvo
    canalClientes.send(numeroActual++)

    while (true){
        // si el numero es igual al mio, significa que es mi calculo: 
        if (miNum == numCliente){
            // . .  hago lo que necesito con el calculo y resto uno en canalClientes.
            numActual = canalClientes.receive()
            canalClientes.send(max(numActual--, 0))
            return // salgo 
        } else {
            // si no es mi numero, devuelvo el calculo con su numero de cliente
            canal4.send((calculo, numCliente))
            // esto indefinidamente hasta que recibir el calculo correcto
        }
    }
}

process C2 {
    canal3.send(algo)
//    NOS QUEDAMOS ACA
    canal4.receive()
}

// ahora yo cree N threads, ponele que 5
// ahora tengo a 5 threads corriendo concurrentemente esperando mensajes
// puedo suponer
// el primer thread receive un mensaje por el canal 3

// EJ8 ✅
// los hizo Nico en clase (el profe)
process Timer(Channel timerCh, int freq, int min){
    chList = new Channel()
    chList.send([])
    while (true){
        req = timerCh.receive()
        clientList = chList.receive().append(req.ch)
        chList.send(clientList)
        clientList.append(req.ch)
        if (len(clienList) == min){
            thread clock(freq, chList)
        }
    }
}

thread Clock(int freq, Channel cdList){
    while(true){
        sleep(freq)
        // mandar ticks
        myList = chList.receive()
        chList.send(myList)
        for (ch in myList) {
            ch.send("Tick")
        }
    }
}

// b ✅
process Cell(List<Channel> vecinos, Channel myCh, Channel timerCh, bool alive){
    // registrar al timer
    estado = alive
    myTimerCh = new Channel()
    timerCh.send(Request(myTimerCh))
    while (true){
        if(myTimerCh.receive() == "Tick"){
            for ch in vecinas {
                ch.send(estado)
                repeat (8){
                    int cantVivas += myCh.receive()
                    estado = nextState(cantVivas, estado) // esta funcion hay que implementarla nosotros (...)
                }
            }
        }
    }
    
}
























