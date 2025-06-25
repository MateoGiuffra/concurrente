// a
Channel canalProxy = new Channel()
Channel canalServidor = new Channel()

process Agente(id){
    while (true){
        canalProxy.send("Estoy vivo " + id)
        sleep(1000ms)
    }
}

process Servidor{
    while (true){
        log = canalServidor.receive()
        print(log)
    }
}

process Proxy{
    while (true) {
        reporte = canalProxy.receive()
        canalServidor.send(reporte)
    }
}

// b
Channel canalProxy = new Channel()
Channel canalServidor = new Channel()

process Agente(id){
     while (true){
        canalProxy.send(("Estoy vivo " + id + "", id ))
        sleep(1000ms)
    }
}

process Servidor{
    while (true){
        log, id = canalServidor.receive()
        random = randint()
        print("El log es " + log + " .ID mas numero random " + (id + random))
    }
}

process Proxy{
    while (true){
        tupla = canalProxy.receive()
        canalServidor.send(tupla)
    }
}
// C
Channel canalProxy = new Channel()
Channel canalServidor = new Channel()

Channel horaUltimoPrint = new Channel()

process Agente(id){
    while (true){
        canalProxy.send(("Estoy vivo {id}", id ))
        sleep(60s)
    }
}

process Contador {
    horaUltimoPrint.send(datetime.now())
    while (true){
        horaUltimoPrint = horaUltimoPrint.receive()
        horaUltimoPrint.send(horaUltimoPrint)

        horaActual =  datetime.now()
        if (horaActual - horaUltimoPrint > timedelta(minutes=2) ) {
            canalProxy.send(("No hubo respuesta de ningun agente", -1))
            sleep(120s)
        }
    }
}

process Servidor{
    while (true) {
        log, id = canalServidor.receive()
        if (id == -1){
            print(log)
        }else{ 
            random = randint()
            print(log + (id + random))
            horaUltimoPrint.receive()
            horaUltimoPrint.send(datetime.now())
        }
    }
}

process Proxy{
    while (true) {
        tupla = canalProxy.receive()
        canalServidor.send(tupla)
    }
}

