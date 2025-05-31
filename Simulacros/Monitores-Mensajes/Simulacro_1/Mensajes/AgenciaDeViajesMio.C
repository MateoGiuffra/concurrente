// este file es el mio
Channel agencia = new Channel()
Channel auto = new Channel()
Channel hotel = new Channel()
Channel vuelo = new Channel()
//a
process Agencia() {
    while(true){
        fecha, canalCliente = agencia.receive();
        Channel canalInterno = new Channel();;

        // los mando como tupla
        hotel.send((fecha, canalInterno));
        vuelo.send((fecha, canalInterno));
        auto.send((fecha, canalInterno));

        bool res = True;
        repeat (3) {
            res = res && canalInterno.receive();
        }
        canalCliente.send(fecha, res)
    }
}
//b
Channel agencia = new Channel()
Channel auto = new Channel()
Channel hotel = new Channel()
Channel vuelo = new Channel()

process Agencia() {
    while(true){
        fecha, canalCliente = agencia.receive();
        // al crearlo como thread, estoy diciendo, llego un cliente? bueno este thread lo atiende
        // asi desocupo al process Agencia y habilito a atender a varios threads de forma concurrente
        thread (fecha, canalCliente){
            Channel canalInterno = new Channel();;

            // los mando como tupla
            hotel.send((fecha, canalInterno));
            vuelo.send((fecha, canalInterno));
            auto.send((fecha, canalInterno));

            bool res = True;
            repeat (3) {
                res = res && canalInterno.receive();
            }
            canalCliente.send(fecha, res)
        }
    }
}

//c este esta mal 
Channel agencia = new Channel()

process Agencia (List<Chanell> autos ,List<Chanell> hoteles, List<Chanell> vuelos) {
    while (true) {
        fecha, canalCliente = agencia.receive();
        thread (fecha, canalCliente){
            List<(List<bool>)> respuestas = []
            for listOfChannel in [autos, hoteles, vuelos] {
                respuestasDeCanal = []
                respuestas.add(respuestasDeCanal)
                for channel in listOfChannel {
                    Channel canalInterno = new Channel();
                    channel.send(fecha, canalInterno)
                    bool res = canalInterno.receive()
                    respuestasDeCanal.add(res)
                }
            }
            autosRes = respuestas[0]
            hotelesRes = respuestas[1]
            vuelosRes = respuestas[2]
            for i in range(min(len(hotelesRes), len(vuelosRes), len(autosRes))){
                res = autosRes[i] && hotelesRes[i] && vuelosRes[i]
                canalCliente.send(fecha, res)
            }
        }
    }

}

// c 
Channel agencia = new Channel()
process Agencia (autos, hoteles, vuelos){
    while (true){
        fecha, canalCliente = agencia.receive()
        // no puedo suponer que tienen la misma longitud
            for i in range(len(autos)){
                thread (i, fecha, canalCliente){
                    Channel canalInterno = new Channel();
                    autos[i].send((fecha, canalInterno))
                    hoteles[i].send((fecha, canalInterno))
                    vuelos[i].send((fecha, canalInterno))
                    // el problema de este es que, la fecha es la misma 
                    // y cambia el auto | hotel | vuelo pero yo ya mande
                    // la respuesta al cliente con alguno.
                    res = canalInterno.receive() && canalInterno.receive() && canalInterno.receive()
                    canalCliente.send(fecha, res)
                }
        }
    }
}

// solucion franco
process Agencia(){
    while(true){
        fecha, canalCliente = canalAgencia.receive();
        thread (fecha, canalCliente){
            Channel canalInterno = new Channel(); 
            threadConsultar(autos, fecha, canalInterno)
            threadConsultar(hoteles, fecha, canalInterno)
            threadConsultar(vuelos, fecha, canalInterno)
            res = True 
            repeat (3){
                res = res && canalInterno.receive();
            }
            canalCliente.send(res)
        }
    }
}

thread threadConsultar(servicios, fecha, canalInterno){
    aux = new Channel()
    for service in servicios{
        service.send((fecha, canalInterno))
    }
    found = false 
    int = 0
    while (i < len(servicios) && !found){
        found = aux.receive();
        i++; 
    }
    canalInterno.send(found)
}