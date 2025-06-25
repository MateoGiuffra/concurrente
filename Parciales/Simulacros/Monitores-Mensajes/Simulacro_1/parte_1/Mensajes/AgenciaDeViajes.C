Channel auto = new Channel();
Channel hotel = new Channel();
Channel vuelo = new Channel();
Channel agencia = new Channel();

a)
process AgenciaDeViaje {
    while(true){
        req = agencia.receive();
        Request miReq = new Request();
        Channel canalInterno = new Channel()
        miReq.req = fecha;
        miReq.canal = canalInterno
        hotel.send(req)
        vuelo.send(req)
        auto.send(req)
        respuesta = True
        repeat (3) {
            respuesta = respuesta && canalInterno.receive()
        }
        req.canal.send(respuesta)
    }
}

b)
Channel auto = new Channel();
Channel hotel = new Channel();
Channel vuelo = new Channel();
Channel agencia = new Channel();


process AgenciaDeViaje {
    while(true){
        req = agencia.receive();
        thread (req){
                Request miReq = new Request();
                Channel canalInterno = new Channel()

                miReq.req = fecha;
                miReq.canal = canalInterno

                hotel.send(req)
                vuelo.send(req)
                auto.send(req)

                respuesta = True
                repeat (3) {
                    respuesta = respuesta && canalInterno.receive()
                }
                req.canal.send(respuesta)
        }
    }
}

c)
Channel auto = new Channel();

process AgenciaDeViaje(List<Channel> auto, List<Channel> vuelo, List<Channel> hotel) {
    while(true){
        req = agencia.receive();
        thread (req){
                Channel canalInterno = new Channel()

                for proveedor in [auto, vuelo, hotel]{
                    thread (req, canalInterno, proovedor) {
                        bool found = False
                        Request miReq = new Request();

                        Channel canalProveedor = new Channel();

                        miReq.req = req.fecha;
                        miReq.canal = canalProveedor

                        for chprov in provedor {
                            chprov.send(miReq)
                        }
                        int recibidos = 0;
                        while recibidos < proovedor.size() && !found {
                            found = found || canalProveedor.receive();
                            recibidos++;
                        }
                        canalInterno.send(found);
                }
            }
                respuesta = True
                repeat (3) {
                    respuesta = respuesta && canalInterno.receive()
                }
                req.canal.send(respuesta)
        }
    }
}

