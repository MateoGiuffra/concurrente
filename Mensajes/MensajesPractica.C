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

//para hacer el b, con esto ya alcanza ✅
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

// esta es la solucion propuesta por los profes 
// SOLUCION
// Crear dos threads:
// - uno que reciba del cliente y manda a S y 
// - otro que solo recibe por S y manda al cliente
// - hacer un canal con n cantidad de mensajes, por cada recibido se saca uno

// 🟨 esta la hice yo siguiendo la solucion de los profes, no esta verificada por nadie (aparte de mi), pero creo que funciona
process P(){
    Channel canalMensajes = new Channel()
    repeat(20){
        canalMensajes.send("mensaje")
    }
    thread (canalMensajes){
        while (true){
            calculo = canal3.receive()
            canalMensajes.receive()
            canal1.send(calculo) 
        }
    }

    thread (cantMensajes){
        while (true){
            res = canal1.receive()
            canalMensajes.send("mensaje")
            canal4.send(res)
        }
    }
}


// Y yo queria responder la pregunta, entonces hice esto siguiendo mi version
// para garantizar que le llegue a cada cliente su calculo.
// Basicamente sincronizo el indice con el turno del cliente, asi le paso al cliente su turno
// y ademas la lista para que él elija su propio calculo
// 🟨 
process P {
    Channel canalP = new Channel();
    canalP.send([])

    repeat(N){
        thread(canalP, canalClientes){ 
            while(true){
                calculoAHacerDelCliente, canalCliente = canal3.receive() 
                
                canal1.send(calculoAHacerDelCliente)
                calculo = canal2.receive() 
                
                listaDeCalculo = canalP.receive()
                turno = len(listaDeCalculo) 

                listaDeCalculo.add(calculo)
                canalP.send(listaDeCalculo)
                
                canalClientes.send(turno)

                canal4.send(listaDeCalculo) 
            }
        }
    }
}
process C1 {
    Channel miCanal = new Channel()
    canal3.send((calculoAHacer, miCanal))
    miTurno = miCanal.receive()
    
    lista = canal4.receive()
    miCalculo = lista[miTurno]
}



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

process Timer(Channel canalPedidos, int freq, int cantMinClientes){
    Channel canalClientes = new Channel 
    canalClientes.send([])
    while (true){
        req = canalPedidos.receive()
        list = canalClientes.receive()
        canalClientes.send(list.append(req.canalCliente))
        if (len(list) + 1) >= cantMinClientes 
            thread Clock(freq, canalClientes)
    }
}

process Clock(freq, canalClientes){
    while(true){
        sleep(freq)
        list = canalClientes.receive()
        canalClientes.send(list)
        for ch in list{
            ch.send("Tick")
        }
    }
}
























