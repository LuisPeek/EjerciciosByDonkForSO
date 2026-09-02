#include <stdio.h>

#include "../semaphores_wrap.h"

// TODO: sean dos procesos A y B, sincronizarlos para que se ejecuten de manera alternada: A,B,A,B…
// -----------------------------------------

// - Globals -
sem_t semA;
sem_t semB;
//varGlobalCompartidas
int  varA  = 0;
int  varB  = 0;

void setup() {
    init(semA, 1);
    init(semB,1);
}

void* procesoA(void* _) {
    int d =1;
    while(1){
        wait(semA);
        //SECCION CRITICA 
        printf("===PROCESO A=== \n");
        printf("ANTES DEL SEMMAFORO  varGlobal A : %d\n ",varA);
        varA = varA + d ;
        printf("Despues DEL SEMAFORO varGlobal A : %d\n ",varA);
       // signal(semA);
        d =  d * d;
       // wait(semB);
        printf("===PROCESO A=== \n");
        printf("ANTES DEL SEMMAFORO  varGlobal B : %d\n ",varB);
        varB = varB - d;
        printf("Despues DEL SEMMAFORO  varGlobal B : %d\n ",varB);
        signal(semA);
        
    }
}

void* procesoB(void* _) {
    int e =2;
    while(1){
       // 
       // SECCCION CRITICA
        wait(semA);
        printf("===PROCESO B=== \n");
        printf(" ANTES DEL SEMAFORO  varGlobal B : %d\n ",varB);
        varB = varB + e;
        printf("Despues DEL SEMAFORO  varGlobal B : %d\n ",varB);
       // signal(semB);
        e =  e  ^ e;
       // wait(semA);
        printf("===PROCESO B=== \n");
        printf(" ANTES DEL SEMAFORO  varGlobal A : %d\n ",varA);
        varA ++ ;
        printf("Despues DEL SEMAFORO  varGlobal A : %d\n ",varA);
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


