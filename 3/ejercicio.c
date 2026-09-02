#include <stdio.h>

#include "../semaphores_wrap.h"

// TODO: sean dos procesos A y B, sincronizarlos para que se ejecuten de manera alternada: A,B,A,B…
// -----------------------------------------

// - Globals -
sem_t semA;
sem_t semB;
sem_t semC;
//varGlobalCompartidas
int variable_compartida =0;
int UsosDeImpresora = 0;
int UsosDeScanner = 0;
void setup() {
    init(semA, 3);
    init(semB,1);
    init(semC, 2);
}
void  usarImpresora(){
    printf("Usando Impresora\n");
    UsosDeImpresora++;
    printf("Abandono Impresora\n");
}
void  usar_scanner(){
    printf("Usando Scanner\n");
    UsosDeScanner++;
     printf("Abandono Scanner\n");
}
void* procesoA(void* _) {
    while(1){
        printf("\nA\n");
        wait(semA);
        usarImpresora();
        printf ("USOS DE IMPRESORA : %d\n", UsosDeImpresora );
        signal(semA);
        wait(semB);
        variable_compartida++;
        signal(semB);
    }
}
void* procesoB(void* _) {
    while(1){
        printf("\nB\n");
        wait(semB);
        variable_compartida++;
        signal(semB);
        wait(semC);
        usar_scanner();
        printf ("USOS DE SCANNER : %d\n", UsosDeScanner );
        signal(semC);
    }
}
void* procesoC(void* _) {
    while(1){
        printf("\nC\n");
        wait(semC);
        usar_scanner();
        printf ("USOS DE SCANNER : %d\n", UsosDeScanner );
        signal(semC);
        wait(semA);
        usarImpresora();
        printf ("USOS DE IMPRESORA : %d\n", UsosDeImpresora );
        signal(semA);
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


