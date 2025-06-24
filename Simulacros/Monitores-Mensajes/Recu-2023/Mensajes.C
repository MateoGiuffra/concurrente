// es mi solución

Channel canalSesiones = new Channel()
process ServidorFirmas(){
    Channel historialDeUsuarios = new Channel();
    List<(id, clavePrincipal)> historial = [];
    historialDeUsuarios.send(historial)
    while (true){
        reqSesion = canalSesiones.receive()
        thread (reqSesion, historialDeUsuarios){
            userId = reqSesion.id
            canalCliente = reqSesion.channel
            Request reqRes = new Request(); // 
            reqRes.response = "Login invalido"
            reqRes.miCanal = null; 
            if (!validar(id)){
                canalCliente.send(reqRes)
                return 
            }
            reqRes.response = "Login valido"; 
            reqRes.miCanal = new Channel(); 
            // genero claves
            Clave clavePrincipal = null; 
            historial = historialDeUsuarios.receive();
            for id, clave in historial: 
                if (id == userId) {
                    clavePrincipal = clave; 
                }
            if (clavePrincipal == null){
                clavePrincipal = generar_clave()
                historial.append((userId, clavePrincipal))
            } 
            historialDeUsuarios.send(historial)
            Clave claveSecundaria = generar_clave()
            
            canalCliente.send(reqRes)
            Request req =  miCanal.receive()                     
            List<Documento> documentos = req.documentos
            List<Documento> documentosFirmados = [];
            Clave claveElegida = req.tipoDeClave == "principal" ? clavePrinicipal : claveSecundaria  
            for doc in documentos: 
                documentosFirmados.append(certificar_digitalmente(doc, claveElegida))
            Request docsYLogout = new Request()
            docsYLogout.documentosFirmados = documentosFirmadosM 
            cananLogout = new Channel()
            docsYLogout.canalLogout = canalLogout
            req.canalCliente.send(docsYLogout)
            canalLogout.receive()
        }
    }

}

// b)

Channel canalSesiones = new Channel()
process ServidorFirmas(){
    Channel historialDeUsuarios = new Channel();
    Map<(id, clavePrincipal)> historial = [];
    historialDeUsuarios.send(historial)
    while (true){
        reqSesion = canalSesiones.receive()
        thread (reqSesion, historialDeUsuarios){
            // reqSesion tiene el userId, el canal del cliente y si quiere actualizar la contraseña
            userId = reqSesion.id
            canalCliente = reqSesion.channel

            Request reqRes = new Request(); // 
            reqRes.response = "Login invalido"
            reqRes.miCanal = null; 
            if (!validar(id)){
                canalCliente.send(reqRes)
                return 
            }
            reqRes.response = "Login valido"; 
            reqRes.miCanal = new Channel(); 

            Clave clavePrincipal = null; 
            historial = historialDeUsuarios.receive();
            
            case lookupM userId historial of
                    Nothing ->  clavePrincipal = generar_clave(); 
                                historial.append((userId, clavePrincipal)); 
                    Just clave -> if (reqRes.quiereNuevaClave) { clave = generar_clave() }; 
                                  clavePrincipal = clave;  

            historialDeUsuarios.send(historial)

            Clave claveSecundaria = generar_clave()

            canalCliente.send(reqRes)
            Request req =  miCanal.receive()   
            List<Documento> documentos = req.documentos
            List<Documento> documentosFirmados = [];
            Clave claveElegida = req.tipoDeClave == "principal" ? clavePrinicipal : claveSecundaria  
            for doc in documentos: 
                documentosFirmados.append(certificar_digitalmente(doc, claveElegida))
            Request docsYLogout = new Request()
            docsYLogout.documentosFirmados = documentosFirmadosM 
            cananLogout = new Channel()
            docsYLogout.canalLogout = canalLogout
            req.canalCliente.send(docsYLogout)
            canalLogout.receive()
        }
    }
}