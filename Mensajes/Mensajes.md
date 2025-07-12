## Mensajes 

### Thread vs Process

#### Thread

* Hilo de ejecución
* Comparten la misma instancia de memoria
* Tienen la posibilidad de compartir memoria entre ellos

#### Process

* Instancias de memoria distintas (entre otros process)
* Normalmente se crean threads dentro de un Process (tambien se puede dentro de threads)

### Canales

#### ¿Qué son?

Buzones donde dejas y sacas mensajes. Poseen dos methods principales: `send(T)` y `receive()`

#### Estrategias

Hay 3:
1. **Uno a uno**:
* Un canal para solo dos process
2. **Uno a muchos**: 
    * O sea cada proceso (A,B,C...) deja un mensaje en el buzón de Z y Z solo recibe, no le interesa quién manda.
3. **Muchos a muchos**:
    * Hay un buzón donde todos los procesos dejan un mensaje y lo puede agarrar cualquiera, no es definido.

### Sincronico vs asincronico
* Cuando estamos en contexto **sincrónico**, los métodos son **bloqueantes**, por lo tanto el `send` espera un `receive` y el `receive` espera un `send`.
* En cambio en **asincrónica** solo el `receive` es bloqueante.

### ¿Qué nos interesa a nosotros?
- Estrategia muchos a muchos
- Canales asincronicos 

#### Características

* Pueden entrar N mensajes al canal, no hay límite (cálculo que chances de overflow pero raro que quieras hacer solo un while true de send).
* Cuando se hace un `receive`, se saca un mensaje del canal.
* El primer mensaje que entró es el primero que sale. O sea es una **Queue**. No hay forma de acceder por índice.
* Si hacés `receive` sin mensajes, espera.
* No es costoso un channel, se pueden reutilizar.

### Mensajes
* Es un objeto, por lo general son variables que querés compartir (ysi que va a ser).
* Tienen que ser **serializables**, significa que la instancia de ese objeto se debe poder transformarla en string y guardarla en disco.
* **Dato importante**: Cuando necesitás exclusividad, podés mandar canales por canales porque son serializables.
* Normalmente usamos `Request()` para guardar las variables porque le podés inventar campos y sus valores.

### DATOS DE LA NOTACIÓN
* En pseudocódigo, la creación de un thread necesita inicializarse con las variables que va a usar.
* Esas variables van a ser una **copia** de cada thread y si cambia la variable padre no va a cambiar la variable del thread.
* Antes esto se solucionaba con un canal intermedio, pero ahora se hace así.


### NO HACER
* Esta prohibido dentro de un thread, editar variables que hereda de Process porque estarías compartiendo variables (...) y justamente aprendemos mensajes para evitar usar variables compartidas. Asi que la queres modificar, pasa un canal con esa/s variable/s.


### Tips
* [Dependiendo del caso] Si vas a generar un thread dentro de un process, chequea si podes hacer el `receive` **antes** de generarlo, en vez de un `while true {thread(){...}}` porque:
    * En la primera solución solo crea un thread cuando recibe
    * En la segunda los crea siempre, haciendo explotar la CPU y memoria 

### Hydra

* En Hydra no se puede usar la keyword `process`, solo `thread`, pero en pseudocódigo se usa `process` porque ahora no hay memoria compartida


### \[Dudas]

**¿Cuándo creo un thread del lado del cliente?**

