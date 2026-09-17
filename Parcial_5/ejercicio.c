#include <stdio.h>

#include "../semaphores_wrap.h"

// TODO: sean dos procesos A y B, sincronizarlos para que se ejecuten de manera alternada: A,B,A,B…
// -----------------------------------------

// - Globals -
/*
Se dispone de dos procesos, donde uno de ellos produce ciertos elementos que, 
luego de ser depositados en una lista
compartida, son consumidos por el otro proceso. Se dispone de la 
siguiente solución parcial:
////codigo

Complete la solución indicando qué semáforos corresponden a las 
incógnitas X1 y X2 (eligiendo entre los semáforos
existentes) y luego inicialice todos los semáforos de forma 
tal que se respete el enunciado y no se produzca deadlock ni
starvation.
Nota: la lista no puede tener más de 5 elementos.
*/

sem_t SC; /// SOlo 5 elementos
sem_t SB; //MUTEX
sem_t SA; // HAY ELEMETOS EN LA LISTA

void setup() {
    init(SB,1);
    init(SC,5);
    init(SA,0);

}

void* procesoA(void* _) {
 
    while(1){
        elemento = producir() 
        wait(SC) 
        wait(SB) 
        depositar(elemento, lista) 
        signal(SB) 
        signal(SA)
    }
}

void* procesoB(void* _) {


    while(1){
        wait( SA );
        wait( SB );
        elemento = retirar(lista);
        signal(SB);
        signal(SC);
        consumir(elemento)
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


