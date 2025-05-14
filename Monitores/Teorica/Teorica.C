Monitor Semaphore{
    int permisos; 
    int esperando; 
    public Semaphore(int permisos){
        this.permisos = permisos;
        this.esperando = 0;
    }
    void acquire(){
        whileA(permisos == 0){
            wait();
        }
        permisos--; 
    }
    void release(){
        permisos++;
        notify();
    }
}