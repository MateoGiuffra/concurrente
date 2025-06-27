global Semaphore[] checkpointsSemaforos = new Sempaphore[5] 
// son 5 semaforos con 5 permisos cada uno. Todos son fuertes 
global string[] checkpoints = ["rojo","azul", etc]; 
// lista de checkpoints con colores aleatorios. Su tamaño es de 5

thread Jugador (string color) {
    while (true){
        for i in range(5){
            checkpointsSemaforos[i].acquire();
            if (checkpoints[i] == color){
                comprar()
                curarse()
            } 
            checkpointsSemaforos[i].release();
        }
    }
}