#include <stdio.h>

#include "../semaphores_wrap.h"

// TODO: sean dos procesos A y B, sincronizarlos para que se ejecuten de manera alternada: A,B,A,B…

/*
Existe un aeropuerto que se utiliza como base de operaciones  de una flota de aviones. 
Existen muchos aviones, diez pistas de aterrizaje 
/ despegue y dos controladores aéreos. 
Cada vez que un avión desea despegar o aterrizar, debe utilizar una pista. Para ello, 
la misma es solicitada al controlador de entrada, y luego de ser utilizada se le notifica al 
controlador de salida para que vuelva a estar disponible.
Se pide que sincronice el siguiente pseudo-código respetando las reglas establecidas, 
sin que se produzca deadlock ni starvation 
(cuando el avión ya pidió pista).  Para ello solamente debe utilizar semáforos, 
indicando el tipo de los mismos y sus valores iniciales.

*/
// -----------------------------------------

// - Globals -
sem_t pedirPista;
sem_t liberarPista;
sem_t countPistas;
sem_t controladorOk;
sem_t pistasDisponles;
//varGlobalCompartidas
int  pistasLibres  = 10;
int  varB  = 0;


/// AVIONES = N
///  10 pistas de aterrizaje =>  pistas= [10]; 
/// 2 CONTROLADORES AEREOS

void setup() {
    init(pedirPista, 0);
    init(pistasDisponles,10);
    init(countPistas,1);
}

void* Avion(void* _) {
   
    while(1){
        
        printf("Mantenimiento\n");

        signal(pedirPista);
        wait(controladorOk);
        printf("Despegar\n");
        signal(liberarPista);

        printf("Volar\n");

        
        signal(pedirPista);
        wait(controladorOk);
        printf("Aterrizar\n");
        signal(liberarPista);

        //// despegar y aterrizar utilizan siempre al controlador de entrada luego este es quien les dice
        //// si esta disponible  :v
        ////  
    }
}

void* ControladorDeEntrada(void* _) {
   
    while(1){

      wait(pedirPista);
      wait(pistasDisponles);  
      printf("otorgarUnaPista\n");
            wait(countPistas);
                pistasLibres--;
                printf("log de pistasLibres %d\n",pistasLibres);
            signal(countPistas);
        signal(controladorOk);

    }
}


void* ControladorDeSalida(void* _) {
   
    while(1){
        
        wait(liberarPista);
        printf("liberarUnaPista\n");
        signal(pistasDisponles);

        wait(countPistas);
            pistasLibres++;
            log("Pistas libres actuales: %d\n",pistasLibres);
        signal(countPistas);
        
        

    }
}



// --------------------------------------------
int main() {
    setup();

    create(a, Avion);
    create(b, ControladorDeEntrada);
    create(c, ControladorDeSalida);


    join(a);
    join(b);
    join(c);

    return 0;
}


