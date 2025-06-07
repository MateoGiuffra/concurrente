/*
[ATENCION] El enunciado esta bastante mal hecho, si lo queres hacer te recomiendo que preguntes a los profes bien que se pide 
El a esta bien y el b tambien, pero leyendo solamente el enunciado vas a decir wtf que hizo este chabon.
Por las dudas explico masomenos el b en comentarios
El c no lo hice
*/
Monitor Autopista{
    cantKartings = 0 
    cantParticulares = 0
    cantKartingsEsperando = 0

    bool puedeEntrarParticular(){
        return cantKartings == 0  && cantKartingsEsperando == 0
    }
    bool puedeEntrarKarting(){
        return cantKartings == 0  && cantParticulares == 0
    }

    particularEntraPista(){
        while (!(puedeEntrarParticular())){
            wait()
        }
        cantParticulares++
        // entra
    }

    particularSalePista(){
        cantParticulares--
        if (cantParticulares == 0){
            notify() // es suficiente porque solo habrian kartings durmiendo
        }
    }

    kartingEntraPista(){
        while (!puedeEntrarKarting()){
            cantKartingsEsperando++
            wait()
            cantKartingsEsperando--
        }
        cantKartings = 1
        //entra
    }
    
    kartingSalePista(){
        cantKartings = 0
        notifyAll() // por que puede estar dormido un karting o un particular
    }
}

// b)
// si hay un karting esperando pero hay lugar, cuando haya lugar le gano
// si hay un karting esperando y no hay lugar, cuando haya lugar le gano
// si hay un karting en la pista, y estan esperando un karting y un particular, gana el karting
Monitor Autopista{
    
    cantKartings = 0
    cantParticulares = 1 

    cantKartingsEsperando = 1
    
    MAX_PARTICULARES = 20


    bool puedeEntrarParticular(){
        return cantKartings == 0  && (cantParticulares != 0 || cantKartingsEsperando == 0) && cantParticulares < MAX_PARTICULARES
    }

    bool puedeEntrarKarting(){
        return cantKartings == 0  && cantParticulares == 0 
    }

    particularEntraPista(){
        while (!(puedeEntrarParticular())){
            wait()
        }
        cantParticulares++
        // entra
    }

    particularSalePista(){
        cantParticulares--
        notifyAll() // porque ahora hay potenciales particulares esperando o kartings queriendo entrar
    }

    kartingEntraPista(){
        while (!puedeEntrarKarting()){
            cantKartingsEsperando++
            wait()
            cantKartingsEsperando--
        }
        cantKartings = 1
        //entra
    }
    
    kartingSalePista(){
        cantKartings = 0
        notifyAll() // por que puede estar dormido un karting o un particular
    }
}

