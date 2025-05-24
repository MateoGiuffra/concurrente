## Monitores 

### Notacion
Cuando escribimos pseudocodigo, hay dos formas: 
#### Monitor NombreDeLaClase
- Todos los method ya son tomados como sync
#### Class NombreDeLaClase
- Tenes que declarar cuales methods son sync

### Teoria 
- Un monitor tiene N methods y Condition Variables (en esta materia solo tenemos una pero pueden haber mas)
- Dos listas: 
    - una que funciona como un conjunto
    - otra que funciona como una cola (F.I.F.O) la cual esta asociada a la Condition Variable.
- Hay un unico Lock por monitor. 
- Solo puede ejecutar un thread a la vez cualquier method del monitor. Se dice que ese thread tiene el lock. 
- Si otro thread quiere ejecutar cualquier method del monitor y alguien mas tiene el lock, se va a dormir en el conjunto de monitores. 

#### Hay dos methods principales: 
- wait() Duerme al thread. Lo manda a la cola. 
- notify() Despierta al primer thread. Lo saca de la cola y lo pone en la lista de conjuntos para competir por el lock. 
- notifyAll() Lo mismo pero despierta a TODOS.

### ¿Cuando usar notify o notifyAll?
Por lo general se usa notifyAll cuando el thread que te interesa no es el primero o tenes mas de un tipo de thread en la cola. 

### Wakeups Espıureos
En Java e inclusive en otros lenguajes como C, el sistema para evitar un race condition, puede despertar a un thread de una espera (wait()) sin que haya recibido explicitamente una señal para hacerlo.
Es una caracteristica del sistema, podes verlo como si te hiciera un notify sin que vos lo hayas hecho. Por eso es importante usar un while para evaluar la condicion.

### Tips
- Generalmente es mejor usar contador que flags (obviamente depende el caso)
- Ante la duda pone notifyAll
- Es mejor solucion EVITAR notifys innecesarios, pero primero hace que ande y despues hilas mas fino. 