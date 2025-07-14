## Semaforos 

### Prácticas
Los ejercicios del tp 1 los hice en papel, entonces no hay registro. 
Pre parcial el tp2 lo habia hecho masomenos, pero para el recu rehice los ejercicios y creo que ahora estan bien o por lo menos mas orientados que antes jajajaj, miralos para tener una idea. 

### Esquemas 
Su explicación estan en el mismo codigo, no voy a hacer un readme para explicarlas [Esquemas](https://github.com/MateoGiuffra/concurrente/blob/main/Semaforos/Esquemas)
[Link a la clase de esquemas](https://www.youtube.com/watch?v=R8Sl82XPcIQ&list=PLiroaJ49ZKkJ3fCdH2m1AmgWlFMdezpiq&index=8)

### Teoría
- Entender que ya no van a haber threads preguntando todo el rato si es su turno. 
- Si un thread quiere hacer x operacion, por lo general se resuelve envolviendo la operación/es con un semáforo, si hay permisos lo hace, si no se duerme. 
- Para despertarlo, usas un release
- Podes ordenar a los threads en una cola (F.I.F.O) para evitar starvation. Es caro, por default no funciona asi y a veces no es necesario, pero cuando lo es solo decis que es fuerte o lo inicializas con true.  

### Tips 
- A mi me sirvió más no pensar en esquemas e ir directamente a resolver. Quizas uno por pensar que un problema se parece a un esquema se ata a esa idea y terminas haciendo cualquier cosa solo por querer apegarte al esquema. Mi recomendación es que conozcas los esquemas, lo tengas presentes pero NO partas de ninguno, simplemente lanzate a resolver. **Igualmente te dejo soluciones tipicas que vi durante los ejercicios, obvio seguramente hay mas y sos libre de tirar una pr si encontras una que no puede faltar.**


- Muchas veces estas soluciones bastan:
  
| Tipo de semaforo | Caso de uso |
|----------------|----------------|
| Mutex  | Para evitar perdida de sumas, restas etc |
| Split Mutex  | Cuando querés que se ejecute de forma alternada Xs operaciones. Mínimo dos semáforos, uno en 0 y otro en 1 |
| Semaphore(0)  | Cuando necesitas que pase x accion primero antes de ejecutar otra |
| Semaphore(N)  | Cuando tenes un número finito de semáforos y NO tiene importancia conocer cual semáforo es |
| Semaphore[N]  | Cuando tenes un número finito de semáforos y SI tiene importancia conocer cual semáforo es |
- Sirve mucho hacer contadores (por ej lectores y escritores lo usan)
- **Truco del ID:** Variable global para conocer el id. Un thread al ejecutar cambia la variable global con SU ID. Envolve esto en un mutex para que otro thread no cambie al mismo tiempo la variable global. 
- Se pueden crear semáforos internos y hasta incluso threads, es raro que una solución lo requiera pero esta bueno saberlo, por ejemplo [este ejercicio](https://github.com/MateoGiuffra/concurrente/blob/main/Semaforos/Ejercicios) se usa para evitar ifs (entre otras ventajas) y tener una flag interna. [Link a la explicación]
