//1.a
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



// 2
process Servidor(){
    while(true){
        msg1 = c1.receive()
        msg2 = c2.receive()
        print(msg1 + msg2)
    }
}

// 3
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
*/
global Channel canal = new Channel(); 
process Servidor(){
    while(true){
        req = canal.receive()        
        strFormat = trim(req.str)
        req.ch.send(strFormat)
    }
}


// 5
global Channel canal = new Channel(); 

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

// Ej 6
a)
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

b)
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
c)
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
//a

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

//b
process P {
    Channel canalP;
    canalP.send([])
    repeat(N){ // creo N threads
        thread(canalP){ // cada thread por siempre va a esperar mensajes del cliente y se los pasa a S
            while(true){
                 msjCliente = canal3.receive() // espero msj del cliente, si no hay espero
                 canal1.send(msjCliente) // se la mandamos a S para que procese
                 calculo = canal2.receive() // recibimos de S el calculo, si todavia no termina espero
//el tema es que si otro thread que ANTES ya hizo un send a S, me puede mandar
//su respuesta a mi, y no es la del cliente, se la mandaria a otra persona.
//Entonces, lo agrego a la lista
                copiaDeLaLista = canalP.receive()
                copiaDeLaLista.add(calculo)
                // si ya tengo todas las respuestas, las devuelvo en orden al cliente
                if (copiaDeLaLista.size() == N) {
                    for c in copiaDeLaLista {
                     canal4.send(c) // mandamos el calculo al cliente correspondiente
                    }
                    canalP.send([])
                  } else {
                    canalP.send(copiaDeLaLista)
                
                }
            }
        }
    }
}

process C1 {
    canal3.send(algo)
//    NOS QUEDAMOS ACA
    2 = canal4.receive()
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


























