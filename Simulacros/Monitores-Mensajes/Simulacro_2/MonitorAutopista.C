// pl 
Monitor Autopista{
    cantKartings =0 
    cantParticulares = 0
    particularEntraPista(){
        while (cantKartings > 0){
            wait()
        }
        cantParticulares++
        // entra
    }

    particularSalePista(){
        cantParticulares--
        if (cantParticulares == 0){
            notify()
        }
    }
    
    kartingEntraPista(){
        while (cantKartings > 0 || cantParticulares > 0){
            wait()
        }
        cantKartings++
        //entra
    }
    
    kartingSalePista(){
        cantKartings-- 
        notifyAll()
    }
}
// pe 
Monitor Autopista{
    cantKartings = 0 
    cantParticulares = 0
    cantKartingsEsperando = 0

    particularEntraPista(){
        while (!(cantKartings == 0 && cantKartingsEsperando == 0)){
            wait()
        }
        cantParticulares++
        // entra
    }

    particularSalePista(){
        cantParticulares--
        if (cantParticulares == 0){
            notify()
        }
    }
    
    kartingEntraPista(){
        while (cantKartings > 0 || cantParticulares > 0){
            cantKartingsEsperando++
            wait()
        }
        cantKartingsEsperando--
        cantKartings = 1
        //entra
    }
    
    kartingSalePista(){
        cantKartings = 0
        notifyAll()
    }
}