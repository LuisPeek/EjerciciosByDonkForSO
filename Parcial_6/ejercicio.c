#include <stdio.h>

#include "../semaphores_wrap.h"

// TODO: Sean los procesos A, B y C, 
// sincronizarlos para que ejecuten de manera alternada: A,B,C,A,B,C…
// -----------------------------------------

/*
Se tienen tres procesos concurrentes con múltiples instancias (T, O y R) 
que se ejecutan indefinidamente. Se desea
sincronizarlos para que, independientemente del orden en que sean planificados, 
el contenido generado sea siempre
“TORO TORO TOROTORO...”. Los semáforos SEM_X, SEM_Y, SEM_Z y SEM_W se encuentran 
 xoxo
declarados, pero no se
indican sus valores iniciales.

Complete los tres semáforos faltantes e indique el valor inicial de SEM_X, SEM_Y, SEM_Z y SEM_W, de manera que se
genere la secuencia solicitada. Indique además si es necesario el uso de semáforos mutex.
*/
// - Globals -
sem_t SEM_X;
sem_t SEM_Y;
sem_t SEM_Z;
sem_t SEM_W;
void setup() {
     init(SEM_X,1);
     init(SEM_W,1);
     init(SEM_Y,0);
     init(SEM_Z,0);
}

void* PROCESO_O(void* _) {
    while(1){
       wait(SEM_Y)
        agregarAlFinal(COLA, "O")
        signal(SEM_W)
        
    }
}

void* PROCESO_T(void* _) {
    while(1){
    wait( SEM_X);  
    wait(SEM_W)  ;
    agregarAlFinal(COLA, "T")  
    signal(SEM_Y) 
    signal(SEM_Z) 
    }
}

void* PROCESO_R(void* _) {
    while(1){
        wait( SEM_Z)
        wait(SEM_W)
        agregarAlFinal(COLA, "R")
        signal(SEM_Y)
        signal(SEM_X)
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

    return 0;
}


