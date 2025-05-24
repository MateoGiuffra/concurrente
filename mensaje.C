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
