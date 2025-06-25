// a
Monitor Telescopio  (){
    cantLectores = 0
    cantEscritores = 0
    calibracion = 0.1
    
    int iniciarObservacion(){
        while (cantEscritores > 0){
            wait()
        }
        cantLectores++
        return calibracion //leo
    } 
    
    void finalizarObservacion(){
        cantLectores--
        if (cantLectores == 0){
            notify(); //despierto a un potencial escritor
        }
    }

    void iniciarCalibracion(int nuevaCalibracion){
        while (cantLectores > 0 || cantEscritores > 0){
            wait()
        }
        cantEscritores++
        calibracion = nuevaCalibracion
    }
    void finalizarCalibracion(){
        cantEscritores-- 
        notifyAll()
    }
}
// b
Monitor Telescopio  (){
    cantLectores = 0
    cantEscritores = 0
    calibracion = 0.1
    actualPosicion = 1
    
    int iniciarObservacion(int posicion){
        // si hay escritores o (mi posicion es distinta a la actual y hay lectores)
        while (cantEscritores > 0 || (actualPosicion != posicion && cantLectores != 0)){
            wait()
        }
        actualPosicion = posicion
        cantLectores++
        return calibracion //leo
    } 
    
    void finalizarObservacion(){
        cantLectores--
        if (cantLectores == 0){
            notifyAll(); //despierto a un potencial escritor o algun lector que queria leer en una posicion distitna
        }
    }

    void iniciarCalibracion(int nuevaCalibracion){
        while (cantLectores > 0 || cantEscritores > 0){
            wait()
        }
        cantEscritores++
        calibracion = nuevaCalibracion
    }
    void finalizarCalibracion(){
        cantEscritores-- 
        notifyAll()
    }   
}

// c
Monitor Telescopio  (){
    cantLectores = 0
    cantEscritores = 0
    calibracion = 0.1
    actualPosicion = 1

    cantEscritoresEsperando = 0

    int iniciarObservacion(int posicion){
        // si hay escritores escribiendo o (mi posicion es distinta a la actual y hay gente esperando para calibrar o hay lectores)
        while (cantEscritores > 0 || (actualPosicion != posicion && (cantEscritoresEsperando != 0 || cantLectores != 0))){
            wait()
        }
        actualPosicion = posicion
        cantLectores++
        return calibracion //leo
    } 
    
    void finalizarObservacion(){
        cantLectores--
        if (cantLectores == 0){
            notifyAll(); //despierto a un potencial escritor o algun lector que queria leer en una posicion distitna
        }
    }

    void iniciarCalibracion(int nuevaCalibracion){
        cantEscritoresEsperando++;
        while (cantLectores > 0 || cantEscritores > 0){
            wait()
        }
        cantEscritoresEsperando--
        cantEscritores++
        calibracion = nuevaCalibracion
    }
    void finalizarCalibracion(){
        cantEscritores-- 
        notifyAll()
    }
}
