#include <stdio.h>

#include "../semaphores_wrap.h"

// TODO: sean dos procesos A y B, sincronizarlos para que se ejecuten de manera alternada: A,B,A,B…
// -----------------------------------------


/*
1er Recuperatorio 1° Parcial 2C2025 · Práctica 4 · 02/12/2025
El siguiente pseudocódigo simula la interacción de N usuarios en la 
red social “Z” y un proceso analizador que toma cada uno
de los posts generados para analizarlos. 
A pesar de estar sincronizado, el sistema se desempeña más lento de lo esperado y
frecuentemente deja de funcionar hasta que el administrador reinicia el proceso Analizador.

Usuario (N instancias)              Analizador (1 instancia)

While(1) {                          While(1) {
wait(mutexPosts);                   wait(mutexPosts);
post = generarPost();               wait(hayPosts);
postear(post, postsNuevos);         post = obtenerPost(postsNuevos);
signal(hayPosts);                   resultado = procesar(post);
mostrarEnPantalla(post);            guardarEnDisco(resultado);
signal(mutexPosts);                 signal(mutexPosts);
}                                   }
Variables compartidas: 
postsNuevos es la cola con los nuevos posts a analizar. 
Semáforos: hayPosts es un contador inicializado en 0 y
mutexPosts es un mutex.
Encuentre errores y/o mejoras en la sincronización planteada. 
No hay que sincronizar de nuevo: sólo marcar y explicar los
errores encontrados.

ERRORES : 

-para utilizar un mutex la SC debe ser lo mas pequeña posible y solo se debe utilizar en variables compartidas
1) En el proceso de Usuario hay un mutexPosts en la primera linea del wail agarrando todo el codigo (SC grande)
  luego de procesar todo ese codigo hace un signal. No tiene sentido que otros usuarios tengas que esperar a generar
  su post mientras otro ya lo genero y solo necesita postearlo.
2) En el proceso de Analizador tenemos un mutex antes que que el wait de hayposts no tiene sentido retener el mutex
si es que no hay posts deberia ir primero el hay posts para que no retenga de forma inecesaria el mutex; 
esto ocasionaria un deadlock 

MEJORAS:
*/
// - Globals -
sem_t mutexPosts;
sem_t hayPosts;

void setup() {
    init(mutexPosts, 1);
    init(hayPosts, 0);
}

void* Usuario(void* _) {
    while(1){
        post = generarPost();       
        
        wait(mutexPosts);           
        postear(post, postsNuevos); 
        signal(mutexPosts);      

        mostrarEnPantalla(post);    
        signal(hayPosts);           
    }
}

void* Analizador(void* _) {
    While(1) {
        wait(hayPosts);

        wait(mutexPosts);
        post = obtenerPost(postsNuevos);
        signal(mutexPosts);
        resultado = procesar(post);
        guardarEnDisco(resultado);
    }
}




// --------------------------------------------
int main() {
    setup();

    create(a, procesoA);
    create(b, procesoB);
    create(c, procesoC);

    join(a);
    join(b);
    join(c);

    printf ("USOS DE IMPRESORA : %d", UsosDeImpresora );
    
    return 0;
}


