#include <stdio.h>

#include "../semaphores_wrap.h"

// TODO: Volver a realizar el ejercicio para que ejecuten:
//  A,B,B,C,A,B,B,C…
// -----------------------------------------

/*
La pizzería “La Nonna” ofrece delivery. 
Los maestros pizzeros amasan y cocinan pizzas de forma continua, depositándolas en
el mostrador a medida que están listas. 
El mostrador tiene capacidad para almacenar hasta 50 cajas de pizza. 
Los empleadosdel área de delivery retiran las pizzas del mostrador para entregarlas a 
sus respectivos clientes.

while(1) {                          while(1) {                              wait(timbre[id()])
pizza = amasarYCocinar()            wait(mutexMostrador)                    pizza = recibirPizza()
wait(mutexMostrador)                wait(hayPizzas)                         comer(pizza)
wait(hayLugarEnMostrador)           pizza = sacarDelMostrador(mostrador)
dejarEnMostrador(mostrador, pizza)  signal(mutexMostrador)
signal(mutexMostrador)              signal(hayLugarEnMostrador)
signal(hayPizzas)                   viajar()
}                                   signal(timbre[obtenerIdCliente()])

                                    }



a) Identifique los errores que tuvo el dueño de la pizzería al sincronizar a sus empleados.
b) Suponiendo que el pseudocódigo no tuviera errores de sincronización, inicialice los 
semáforos correctamente.

Respuesta a) 
Se produce un Inanicion debido a que si el delibery llega primero retiene el "mutexMostrado"
y no hay pizzas ; entonces se queda esperando y el proceso "Mostrador" hace wait(MutexMostrador) 
quedando bloqueado indefinamente  debido a que el proceso delibery no libera el recurso(mutexMostrador)

b)
*/
// - Globals -
sem_t semRE;
sem_t hayLugarEnMostrador;
sem_t mutexMostrador;
sem_t hayPizzas;
sem_t timbre[n] = {0,0,0,0,0,0,0,0};.....

void setup() {
     init(hayLugarEnMostrador, 50);
     init(hayPizzas, 0);
     init(mutexMostrador, 1);
     init(semSOLPRA, 0);

}   

void* Mostrador(void* _) {
    while(1){
        pizza = amasarYCocinar()          
        wait(hayLugarEnMostrador)  
        
        wait(mutexMostrador)              
        dejarEnMostrador(mostrador, pizza)
        signal(mutexMostrador)            
        
        signal(hayPizzas)                 

    }
}

void* Delivery(void* _) {
    while(1) {                          
    wait(hayPizzas)                     
    
    wait(mutexMostrador)                
    pizza = sacarDelMostrador(mostrador)
    signal(mutexMostrador)

    signal(hayLugarEnMostrador)
    
    viajar()
    
    signal(timbre[obtenerIdCliente()])
      
    }
}

void* Cliente(void* _) {
    while(1){
        wait(timbre[id()])
        pizza = recibirPizza()
        comer(pizza)
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


