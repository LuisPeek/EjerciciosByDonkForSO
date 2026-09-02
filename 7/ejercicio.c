#include <stdio.h>

#include "../semaphores_wrap.h"

// TODO: 
/*
7- Suponga que un proceso tiene por tarea compilar un conjunto de programas y luego enviar el resultado de cada 
compilación por email al encargado de ese proyecto. Dicho proceso está organizado de la siguiente manera: 
N hilos de kernel compilan cada uno un programa distinto, y luego cada uno de ellos depositan en una lista (compartida para todo el proceso) el resultado; 
por otro lado, un hilo de kernel retira los resultados de las compilaciones y manda un email por cada uno de ellos.
*/
// -----------------------------------------

// - Globals -
sem_t semCompilacion;
sem_t semLista;
sem_t semListaTieneAlgo;
sem_t semElementoEnLista;
//varGlobalCompartidas
int  varA  = 0;
int  varB  = 0;

void setup() {
    init(semCompilacion, 1);
    init(semLista, 1);
    
}
int id_programa = 0;
int r =0;

//// 100  = infinito 
int listaCompartida[100];

int obtener_nuevo_programa (){
    printf("imaginamos que devuelve un numero ramdon :v\n");
    return  10;
}
int compilar_programa(){
    
    printf("Sin IA :v \n");
    return 5;
}
int retirarResultado(int lista[]){
    return 1;
}

void* procesoA(void* _) {
    
    while(1){
        
        // para que cada proceso no trabaje con el mismo programa :v
        wait(semCompilacion);
        id_programa =  obtener_nuevo_programa();
        r = compilar_programa(id_programa);    
        signal(semCompilacion);

        wait(semElementoEnLista);
        wait(semLista);
        printf("Depositar resultado (r) en Lista\n");
        signal(semLista);
        signal(semListaTieneAlgo);
        
    }
}

void* procesoB(void* _) {
    int r2 =2;
    while(1){
        wait(semListaTieneAlgo);
        wait(semLista);
        r2  =  retirarResultado(listaCompartida);
        signal(semLista);
        signal(semElementoEnLista);

        printf("envio resultado :v \n");
        
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


