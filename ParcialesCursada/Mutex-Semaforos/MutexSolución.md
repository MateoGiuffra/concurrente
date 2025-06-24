# Solución de Exclusión Mutua
## Voy a escribir lo que puse en el parcial + las correcciones del profe (Me saque un 9 asi que confia )

### a) Encontrar la traza
Esta en la foto.  

### b) ¿Cumple con garantia de entrada si son atomicas?: 
Funciona porque se da priodidad al de menor ID. El thread acutal indica cual es el siguiente, el cual 
es el último del array marcado como true (esta esperando)
Esto puede pasar porque se recorre el array al reves, permitiendo encontrar el proximo en la lista.

***Si llegan threads constantemente y hay uno esperando, pareciera que siempre se va a quedar esperando porque nunca es su turno y se podria considerar un caso de Starvation, PERO como son un número finito de thread, EVENTUALEMNTE va a ser su turno cuando el resto haya terminado.***

Por lo tanto cumple con garantia de entrada ya que el thread que termino de ejecutar la S.C se saca del array (se marca como que NO esta esperando) y se descuenta en uno la 'cantEsperando' para saber si es el útimo o no. Si es el último, no hace nada. Si NO es el último, significa hay threads esperando y por lo tanto entra al if, llama a 'llamarProx()' y actualiza el valor del proximo, o sea cede el puesto. Y para el thread con su ID igual al proximo, saldra del while y ejecuta la S.C.

### Aclaración: 
Lo que esta en negrita y cursiva arriba esta reformulado para que quede mas claro, no lo escribi asi tal cual en el parcial. Basicamente estoy defendiendo que funciona el algoritmo si las operaciones son atomicas, demostrando que no hay caso de Starvation.  
Igualmente no siento que este del todo demostrado, pero estoy escribiendo esto post parcial y ya no me acuerdo mucho (algo es algo) 


### c) Cumple con mutex si son atomicas ya que: 
- No hay perdidas de sumas / restas 
- Imposible que dos threads entren a la S.C ya que el proximo se settea según el indice del array, el 
cual no posee indices repetidos y tambien esta el ID que tambien es único. Por lo tanto no hay forma qudos thread compartan su ID o indice. -
- [CORRECCIÓN] "Falta observar que no ocurren dos llamados a 'proximo' concurrentes"
