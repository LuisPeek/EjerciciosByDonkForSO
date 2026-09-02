#include <stdio.h>

#include "../semaphores_wrap.h"

// TODO: sean dos procesos A y B, sincronizarlos para que se ejecuten de manera alternada: A,B,A,B…
// -----------------------------------------

// - Globals -
sem_t semA;
sem_t semB;


void setup() {
    init(semA, 1);
    init(semB,0);
}

void* procesoA(void* _) {
    
    while(1){
        wait(semA);
        //SECCION CRITICA 
        printf("===PROCESO A=== \n");
        signal(semB);
        // varB  = varB + varA;
        
    }
}

void* procesoB(void* _) {
    int e =2;
    while(1){
       // 
       // SECCCION CRITICA
        wait(semB);
         printf("===PROCESO B=== \n");
        signal(semA);
    }
}



// --------------------------------------------
int main() {
    setup();

    create(a, procesoA);
    create(b, procesoB);

    join(a);
    join(b);

    return 0;
}


