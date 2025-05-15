## Exclusion Mutua 

Lamentablemente no tengo material en codigo, lo hice todo en papel como probablemente lo vayas a hacer vos, asi que te dejo unos tips para entender el tema y como resolver la practica: 

### ¿Que vas a ver?
Muchooos algoritmos para garantizar exclusion mutua. 

### Teoria
- Entende que settear valores conlleva dos operaciones: 
    - Leer 
    - Escribir 
- En el medio de esas dos operaciones (las cuales son atomicas) pueden haber interleavings, juga con eso. 
- Por lo tanto, algo tan tipico como incrementar en uno una variable de tipo int, conllevaria leer esa variable y despues escribir en ella la suma.
  Si en el medio hay un interlaving, probablemente se pierda una suma. 
- La unica forma de evitar esto, es hacer que leer y escribir sea una SOLA operacion atomica, evitando que se puedan hacer interleaving de por medio.
- Basicamente, le decis a la [ISA](https://en.wikipedia.org/wiki/Instruction_set_architecture) esta funcion ahora es atomica y la usas.  

### Tips para resolver la practica
- Hace interleaving a cada rato, asi en algun momento te va a caer la ficha de que cual traza rompe el programa.  
- Usa un thread hasta la mitad de camino (ponele que T1) y guarda su valor en una variable local. Antes de settearle ese valor local a la variable global, cámbiate a T2 y dejalo correr normal. Cuando termine T2, cambia a T1 y pisa lo que hizo T2 con la variable local de T1. 

### Demostraciones
Podes demostrar por absurdo/contradiccion o a manopla. 
A mi me gusta demostrar a manopla así que te dejo estás preguntas guías que me ayudaron a demostrar:
#### Mutex: 
    ¿Puede haber mas de un thread en la Seccion Critica?
#### Garantia de Entrada:    
    ¿Al menos entra el primero?
    ¿El thread que entró, habilita a algun proximo?