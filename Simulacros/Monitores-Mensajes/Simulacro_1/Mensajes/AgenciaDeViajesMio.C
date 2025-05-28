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

//c
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