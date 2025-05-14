## Monitores 

### Teoria 
- Un monitor tiene N methods y Condition Variables (en esta materia solo tenemos una pero pueden haber mas)
- Dos listas: 
    - una que funciona como un conjunto
    - otra que funciona como una cola (F.I.F.O) la cual esta asociada a la Condition Variable.
- Hay un unico Lock por monitor. 
- Solo puede ejecutar un thread a la vez cualquier method del monitor. Se dice que ese thread tiene el lock. 
- Si otro thread quiere ejecutar cualquier method del monitor y alguien mas tiene el lock, se va a dormir en el conjunto de monitores. 

#### Hay dos methods principales: 
    wait(): Duerme al thread. Lo manda a la cola. 
    notify() / notifyAll(): 
        notify() despierta al primer thread. Lo saca de la cola y lo pone en la lista de conjuntos para competir por el lock. 
        notifyAll() lo mismo pero despierta a TODOS. Se usa cuando el thread que te interesa no es el primero. 