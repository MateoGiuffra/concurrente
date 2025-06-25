// [ATENCION] Es mi solución, no esta chequeada asi que solo usala como guia si te sirve.
// Hice hasta el B

// a
enum tipoRonda = ELECCION_LIDER | FIN | NUEVA_RONDA
Process Nodo (List<Channel> otrosNodos, canalMaxId, canalTimer){
    myId = randomId()
    maxVisto = myId
    myChannel = new Channel()
    canalTimer.send(myChannel)
    while (true){
        tipoRonda = myChannel.receive()
        if (tipoRonda == FIN) {
            print(maxVisto == myId ? "Soy el lider" : "No Soy Lider")
        } else {
            if (tipoRonda == ELECCION_LIDER){
                myId = randomId()
            }
            for nodo in otrosNodos{
                nodo.send(max_visto)
            }
            maxVistoVecino = canalMaxId.receive()
            maxVisto = maxVistoVecino > maxVisto ? maxVistoVecino : maxVisto
        }
    }
}
// b
Process Timer(diametro, freq, canalRegistros) {
    canalNodos = new Channel();
    // nodos anotados | llegamos a un multiplo de 10
     //             lista | bool
    req = new Request([], false);
    canalNodos.send(req);
    myChannel = new Channel();

    thread(canalRegistros, canalNodos) {
        while (true) {
            nuevoNodoChannel = canalRegistros.receive();
            req = canalNodos.receive();
            newReq = new Request();
            newReq.lista = req.lista.append(nuevoNodoChannel);
            newReq.bool = (len(req.lista) + 1) % 10 == 0;
            canalNodos.send(newReq);
        }
    }

    thread(canalNodos) {
        rondas = 0;
        while (true) {
            sleep(freq);
            rondas++;
            req = canalNodos.receive();
            canalNodos.send(req);
            if (req.bool) {
                for (ch in req.lista) {
                    ch.send(ELECCION_LIDER);
                }
            } else {
                if (rondas == diametro) {
                    for (ch in req.lista) {
                        ch.send(FIN);
                        rondas = 0;
                    }
                } else {
                    for (ch in req.lista) {
                        ch.send(NUEVA_RONDA);
                    }
                }
            }
        }
    }
}

// c
// no lo entiendo muy bien, pero creo que es esto

enum tipoRonda = ELECCION_LIDER | FIN | NUEVA_RONDA
Process Nodo (List<Channel> otrosNodos, canalMaxId, canalTimer){
    myId = randomId()
    maxVisto = myId
    myChannel = new Channel()
    canalTimer.send(myChannel)
    while (true){
        req = myChannel.receive()
        const { tipoRonda, computo } = req
        if (tipoRonda == FIN) {
            print(maxVisto == myId ? "Soy el lider" : "No Soy Lider")
            computo_costoso(computo)
        } else {
            if (tipoRonda == ELECCION_LIDER){
                myId = randomId()
            }
            for nodo in otrosNodos{
                nodo.send(max_visto)
            }
            maxVistoVecino = canalMaxId.receive()
            maxVisto = maxVistoVecino > maxVisto ? maxVistoVecino : maxVisto
        }
    }
}

Process Timer(diametro, freq, canalRegistros) {
    canalNodos = new Channel();
    // nodos anotados | llegamos a un multiplo de 10
     //             lista | bool
    req = new Request([], false);
    canalNodos.send(req);
    myChannel = new Channel();

    thread(canalRegistros, canalNodos) {
        while (true) {
            nuevoNodoChannel = canalRegistros.receive();
            req = canalNodos.receive();
            newReq = new Request();
            newReq.lista = req.lista.append(nuevoNodoChannel);
            newReq.bool = (len(req.lista) + 1) % 10 == 0;
            canalNodos.send(newReq);
        }
    }

    thread(canalNodos) {
        rondas = 0;
        while (true) {
            sleep(freq);
            computo = canalClientes.receive()
            rondas++;
            req = canalNodos.receive();
            canalNodos.send(req);
            if (req.bool) {
                for (ch in req.lista) {
                    ch.send(new Request(ELECCION_LIDER, computo));
                }
            } else {
                if (rondas == diametro) {
                    for (ch in req.lista) {
                        ch.send(new Request(FIN, computo));
                        rondas = 0;
                    }
                } else {
                    for (ch in req.lista) {
                        ch.send(new Request(NUEVA_RONDA, computo));
                    }
                }
            }
        }
    }
}
