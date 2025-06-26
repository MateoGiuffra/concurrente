// es mi solución y esta verificada por un profe, asi que confia

Channel canalSesiones = new Channel()
process ServidorFirmas(){
    Clave clavePrincipal = generar_clave()
    while (true){
        reqSesion = canalSesiones.receive()
        thread (clavePrincipal, reqSesion){
            Bool mantenerSesion = true; 
            String id = reqSesion.id;
            canalCliente = reqSesion.channel;
                
            Request reqRes = new Request(); 
            
            if (!validar(id)){
                reqRes.response = "Login invalido"
                reqRes.miCanal = null; 
                canalCliente.send(reqRes)
                return 
            }

            reqRes.response = "Login valido"; 
            reqRes.miCanal = new Channel(); 
            canalCliente.send(reqRes)

            Clave claveSecundaria = generar_clave()

            while (mantenerSesion){
                Request req = miCanal.receive() 
                if (req.cerrarSesion){
                    mantenerSesion = false; 
                    continue;
                }                
                Documento doc = req.documento
                Clave claveElegida = req.tipoDeClave == "principal" ? clavePrinicipal : claveSecundaria  
               
                miCanal.send(certificar_digitalmente(doc, claveElegida))
            }
        }
    }
}


// b)
Channel canalSesiones = new Channel()

process ServidorFirmas(){
    Clave clavePrincipal = generar_clave()
    Channel canalClavePrincipal = new Channel()
    canalClavePrincipal.send(clavePrincipal)
    while (true){
        reqSesion = canalSesiones.receive()
        thread (canalClavePrincipal, reqSesion){
            Bool mantenerSesion = true; 
            String id = reqSesion.id;
            canalCliente = reqSesion.channel;
                
            Request reqRes = new Request(); 
            
            if (!validar(id)){
                reqRes.response = "Login invalido"
                reqRes.miCanal = null; 
                canalCliente.send(reqRes)
                return 
            }

            Channel miCanal = new Channel();  
            reqRes.miCanal = miCanal; 
            reqRes.response = "Login valido";
            canalCliente.send(reqRes)

            Clave claveSecundaria = generar_clave()
            
            while (mantenerSesion){
                Request req = miCanal.receive() 
                if (req.cerrarSesion){
                    mantenerSesion = false; 
                    continue;
                }

                Clave clavePrincipal = canalClavePrincipal.receive();
                if (req.actualizarClavePrincipal) {
                    clavePrincipal = generar_clave()
                }
                canalClavePrincipal.send(clavePrincipal)

                Documento doc = req.documento
                Clave claveElegida = req.tipoDeClave == "principal" ? clavePrincipal : claveSecundaria  
               
                miCanal.send(certificar_digitalmente(doc, claveElegida))
            }
        }
    }
}