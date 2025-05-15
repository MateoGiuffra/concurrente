## Semaforos 

### Practicas
Los ejercicios del tp 1 los hice en papel, entonces no hay registro. 
Del 2 hice la mayoria en codigo, no te confies porque seguramente no todos esten bien ni tampoco hice todos, miralos para tener una idea. 

### Esquemas 
Su explicacion estan en el mismo codigo, no voy a hacer un readme para explicarlas [Esquemas](https://github.com/MateoGiuffra/concurrente/blob/main/Semaforos/Esquemas)

### Teoria
- Entender que ya no van a haber threads preguntando todo el rato si es su turno. 
- Si un thread quiere hacer x operacion, primero tener que poner un semaforo envolviendo la operacion, si hay permisos lo hace, si no se duerme. 
- Para despertarlo, usas un release
- Podes ordenar a los threads en una cola (F.I.F.O) para evitar starvation. Es caro, por default no funciona asi y a veces no es necesario, pero cuando lo es solo decis que es fuerte o lo inicializas con true.  

### Tips 
#### Muchas veces estas soluciones bastan: 
| Tipo de semaforo | Caso de uso |
|----------------|----------------|
| Mutex  | Nada que explicar |
| Split Mutex  | Cuando querés que se ejecute de forma alternada Xs operaciones. Mínimo dos semáforos, uno en 0 y otro en 1 |
| Semaforo(0)  | Cuando necesitas que pase x accion primero antes de ejecutar otra |
| Semaforo(N)  | Cuando tenes un numero finito de semaforos y NO tiene tanta importancia conocer cual semaforo es |
| Semaforo[N]  | Cuando tenes un numero finito de semaforos y SI tiene tanta importancia conocer cual semaforo es |
- Tambien sirve hacer contadores (por ej lectores y escritores lo usan)
- Variable global para conocer el id. Un thread al ejecutar cambia la variable global con SU ID. 
