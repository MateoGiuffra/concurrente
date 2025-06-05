Monitor PrioridadLectores {
    writers = 0
    readers = 0
    bool canRead(){
        return writers == 0
    }

    bool canWrite(){
        return writers == 0 && readers == 0
    }

    void beginWrite(){
        while (!canWrite()){
            wait()
        }
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