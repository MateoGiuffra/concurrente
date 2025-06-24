// Esta es la resolución de un profe

Channel srvTruconc = new Channel()

process JugadorTruconc(ID){
    Channel miCh = new Channel();
    Request req; 
    req.id = ID; 
    req.channel = miCh; 
    srcTrunconc.send(req)

    Request req = miCh.receive()
    // comunicarse con el servidor 
    int miTurno = req.nroJugador; 
    Channel chSala  = req.chSala; 
    Mesa mesaActual = req.mesa; 
    // iniciar ronda
    for (i = 0; i < 6; i++){
        print(mesaActual)
        mesaActual = miCh.receive()
        if (i == miTurno) {
            jugada = read()
            chSala.send(jugada)
        }
    }
    // jugar
    puntaje = miCh.receive() 
    print(puntaje > 30 ? "Gane" : "Perdi") 
}

process ServidorTruconc() {
    while (true) {
        reqJugadores = [];
        repeat (6) {
            req = srvTruconc.receive();
            reqJugadores.append(req)
        }
        thread (reqJugadores){
            Channel chSala = new Channel(); 
            mesaPartida = inicializarMesa();
            Request req; 
            req.chSala = chSala; 
            req.mesaInicial = mesaPartida; 
            for (i = 0; i < 6;i++) {
                req.nroJugador = 1 
                reqJugadores[i].channel.send(req);
            }
            for (i = 0; i < 6; i++) {
                jugada = chSala.receive();
                mesaPartida = procesarJugada(mesaPartida, jugada); 
                for ( i = 0; i < 6; i++){
                    reqJugadores[i].channel.send(mesaPartida); 
                }
            }
            puntajes = puntuacion(mesaPartida); 
            for (i = 0; i < 6; i++) {
                reqJugadores[i].channel.send(puntajes[i]); 
            }
        }
    }
}

//c

Channel srvTruconc = new Channel()

process JugadorTruconc(ID){
    Channel miCh = new Channel();
    Request req; 
    req.id = ID; 
    req.channel = miCh; 
    srcTrunconc.send(req)

    Request req = miCh.receive()
    // comunicarse con el servidor 
    int miTurno = req.nroJugador; 
    Channel chSala  = req.chSala; 
    Mesa mesaActual = req.mesa; 
    // iniciar ronda
    for (i = 0; i < 6; i++){
        print(mesaActual)
        mesaActual = miCh.receive()
        if (i == miTurno) {
            jugada = read()
            chSala.send(jugada)
        }
    }
    // jugar
    puntaje = miCh.receive() 
    print(puntaje > 30 ? "Gane" : "Perdi") 
}

process ServidorTruconc() {
    Channel chLeaderboard = new Channel(); 
    thread (chLeaderboard){
        ranking = Dictionary(); 
        while (true){
            nuevosGanadores = chLeaderboard.receive();
            for id in nuevosGanadores {
                if ranking.isDefined(id){
                    ranking[id]++;
                }else{
                    ranking[id]=1;
                }
            }
            for (id, victorias) in ranking.getSortedItems(definition){
                print(id, partidas)
            }
        }
    }
    
    while (true) {
        reqJugadores = [];
        repeat (6) {
            req = srvTruconc.receive();
            reqJugadores.append(req)
        }
        thread (reqJugadores, chLeaderboard){
            Channel chSala = new Channel(); 
            mesaPartida = inicializarMesa();
            Request req; 
            req.chSala = chSala; 
            req.mesaInicial = mesaPartida; 
            for (i = 0; i < 6;i++) {
                req.nroJugador = 1 
                reqJugadores[i].channel.send(req);
            }
            for (i = 0; i < 6; i++) {
                jugada = chSala.receive();
                mesaPartida = procesarJugada(mesaPartida, jugada); 
                for ( i = 0; i < 6; i++){
                    reqJugadores[i].channel.send(mesaPartida); 
                }
            }
            puntajes = puntuacion(mesaPartida);
            ganadores = [] 
            for (i = 0; i < 6; i++) {
                reqJugadores[i].channel.send(puntajes[i]);
                if (puntajes[i] > 30){
                    ganadores.append(reqJugadores[i].id);
                }
            }
            chLeaderboard.send(ganadores)
        }
    }
}


// Main java nombreImagen a b c d e f 
