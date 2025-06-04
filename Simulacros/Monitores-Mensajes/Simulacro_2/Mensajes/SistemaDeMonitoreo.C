// a
Channel canalProxy = new Channel()
Channel canalServidor = new Channel()

process Agente(id){
    canalProxy.send("Estoy vivo {id}")
}

process Servidor{
    log = canalServidor.receive()
    print(log)
}

process Proxy{
    reporte = canalProxy.receive()
    canalServidor.send(reporte)
}

// b
Channel canalProxy = new Channel()
Channel canalServidor = new Channel()
process Agente(id){
    canalAgentes.send(("Estoy vivo {id}", id ))
}

process Servidor{
    while (true){
        log, id = canalServidor.reveive()
        random = ranint()
        print("El log es " + log + " .ID mas numero random " + (id + random))
    }
    
}

process Proxy{
    while (true){
        log = canalAgentes.receive()
        canalServidor.send(log)
    }
}
// C
Channel canalProxy = new Channel()
Channel canalServidor = new Channel()
Channel huboReporteReciente = new Channel()

process Agente(id){
    canalAgentes.send(("Estoy vivo {id}", id ))
}

process Contador {
    huboReporteReciente.send([])
    while (true){
        bool array = huboReporteReciente.receive() 
        if (not array.isEmpty() && not array[-1]) { //para quedarme con la ultima respuesta
            canalProxy.send("No hubo respuesta de ningun agente")
        }
    }
}

process Servidor{
    while (true) {
        log, id = canalServidor.receive()
        random = ranint()
        print("El log es " + log + " .ID mas numero random " + (id + random))
        
    }
}

process Proxy{
    while (true) {
        log = canalAgentes.receive()
        start = time.perf_counter()
        huboReporteReciente.send(true)
        canalServidor.send(log)
        end = time.perf_counter()
        array = huboReporteReciente.receive()
        huboReporteReciente.send(array.append((end - start) < 2000ms))
    }
   
}
