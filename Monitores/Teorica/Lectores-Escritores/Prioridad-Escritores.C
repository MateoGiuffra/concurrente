Monitor PrioridadEscritores {

    writers = 0
    readers = 0
    waitingWriters = 0

    bool canRead(){
        return writers == 0 && waitingWriters == 0
    }

    bool canWrite(){
        return writers == 0 && readers == 0
    }

    void beginWrite(){
        while (!canWrite()){
            waitingWriters++; 
            wait()
        }
        waitingWriters--;
        writers = 1 
        escribir()
    }

    void endWrite(){
        writers = 0
        notifyAll()
    }

    void beginRead(){
        while (!canRead()){
            wait()
        }
        readers++; 
        leer()
    }
    
    void endRead(){
        readers--
        if (readers == 0){
            notify()
        }
    }
}