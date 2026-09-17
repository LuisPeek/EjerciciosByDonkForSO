#include <stdio.h>

#include "../semaphores_wrap.h"

// TODO: Volver a realizar el ejercicio para que ejecuten:
//  A,B,B,C,A,B,B,C…
// -----------------------------------------

/*
Un conjunto de científicos decide modelar la melodía de una 
canción con un proceso de cuatro hilos, donde cada uno toca una
nota (a veces repetidas veces) simulando el sonido de un saxo. 
La melodía a reproducir es: RE#, RE#, RE#, RE#, DO#, DO#,
SOL, SOL#.
Sincronice los hilos usando exclusivamente semáforos, 
para lograr que la melodía deseada se reproduzca infinitamente, sin
que se produzca deadlock ni starvation.
*/
// - Globals -
sem_t semRE;
sem_t semDO;
sem_t semSOL;
sem_t semSOLPRA;


void setup() {
     init(semRE, 4);
     init(semDO, 0);
     init(semSOL, 0);
     init(semSOLPRA, 0);

}   

void* RE(void* _) {
    while(1){
        wait(semRE);
        printf("RE#\n");
        signal(semDO);

    }
}

void* DO(void* _) {
    while(1){
        wait(semDO);
        wait(semDO);
        wait(semDO);
        wait(semDO);
        printf("DO#\n");
        printf("DO#\n");
        signal(semSOL);
      
    }
}

void* SOLPRANO(void* _) {
    while(1){
        wait(semSOL);
        printf("SOL\n");
        signal(semSOLPRA);
    }
}

void* SOLPRANINO(void* _) {
    while(1){
        wait(semSOLPRA);
        printf("SOL#\n");
        signal(semRE);
        signal(semRE);
        signal(semRE);
        signal(semRE);
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


