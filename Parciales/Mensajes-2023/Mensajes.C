Channel servidor = new Channel();

process Servidor () {
    while (true) {
        Request req = servidor.receive();
        // 
        thread (req) {
           bool finalizar = false;  
           Carrito carrito = new Carrito(); //inicialmente vacio
           while (!finalizar){
                Producto p = req.producto; 
                Channel canalCliente = req.canal; 
                if (hayStock(p)){
                    carrito.add(p);
                    canalCliente.send("Se pudo agregar");
                } else {
                    canalCliente.send("No se pudo agregar");
                }
                Request response = canalCliente.receive();
                if (response.quiereComprar) {
                    try {
                        string resumen = validar_compra(carrito);
                        carrito.clear();
                        canalCliente.send(resumen)
                    } catch (Error) {
                        carrito.clear();
                        canalCliente.send("Algo salio mal!")
                    }
                }
                finalizar = req.quiereFinalizar;
           } 
        }
    }
}

//b
Channel servidor = new Channel();

process Servidor () {
    Channel chContador = new Channel();
    contador.send(0);
    while (true) {
        Request req = servidor.receive();
        thread (req, chContador) {
            
            contador = chContador.receive();
            contador++;
            chContador.send(contador); 
            if (contador > M){
                print("⚠"); 
            }
            bool finalizar = false;  
           Carrito carrito = new Carrito(); //inicialmente vacio
           while (!finalizar) {
                Producto p = req.producto; 
                Channel canalCliente = req.canal; 
                if (hayStock(p)){
                    carrito.add(p);
                    canalCliente.send("Se pudo agregar");
                } else {
                    canalCliente.send("No se pudo agregar");
                }
                Request response = canalCliente.receive();
                if (response.quiereComprar) {
                    try {
                        string resumen = validar_compra(carrito);
                        carrito.clear();
                        canalCliente.send(resumen)
                    } catch (Error) {
                        carrito.clear();
                        canalCliente.send("Algo salio mal!")
                    }
                }
                finalizar = req.quiereFinalizar;
           } 
           contador = chContador.receive();
           contador--;
           chContador.send(contador);
        }
    }
}


//c ( lo tengo que hacer )
Channel servidor = new Channel();

process Servidor () {
    Channel chContador = new Channel();
    contador.send(0);
    Channel mapThreads = new Channel();
    Map <string, Channel> map = new Map();
    mapThread.send(map);
    while (true) {
        Request req = servidor.receive();
        thread (req, chContador, id) {
           Channel miCanal = new Channel();
           map = mapThread.receive();
           map.assocM((id, miCanal)); 
           mapThread.send(map);      
           contador = chContador.receive();
           contador++;
           chContador.send(contador); 
           bool finalizar = false;  
           Carrito carrito = new Carrito(); 
           while (!finalizar) {
                Producto p = req.producto; 
                Channel canalCliente = req.canal; 
                if (hayStock(p)){
                    carrito.add(p);
                    canalCliente.send("Se pudo agregar");
                } else {
                    canalCliente.send("No se pudo agregar");
                }
                Request response = canalCliente.receive();
                if (response.quiereComprar) {
                    try {
                        string resumen = validar_compra(carrito);
                        carrito.clear();
                        canalCliente.send(resumen)
                    } catch (Error) {
                        carrito.clear();
                        canalCliente.send("Algo salio mal!")
                    }
                }
                finalizar = req.quiereFinalizar;
           } 
           contador = chContador.receive();
           contador--;
           chContador.send(contador);
        }
    }
}

