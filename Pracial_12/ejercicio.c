#include <stdio.h>

#include "../semaphores_wrap.h"

// TODO: sean dos procesos A y B, sincronizarlos para que se ejecuten de manera alternada: A,B,A,B…
// -----------------------------------------


/*
1° Parcial 2C2025 (TM) · Práctica 4 · 04/10/2025
En una cafetería autónoma, tres robots baristas y un robot procesador 
trabajan en equipo para servir pedidos. Los clientes
realizan pedidos de café mediante una app móvil y luego esperan a recibirlo. 
El robot procesador recibe los pedidos
pendientes, los valida y los deja listos para ser preparados. Luego, 
los robots baristas retiran los pedidos validados, hacen el
café y le avisan a su respectivo cliente que está listo. Además, 
el robot procesador soporta un máximo de 50 pedidos

pendientes en un mismo instante.
Cliente (N instancias)                      Procesador (1 instancia)            Robot Barista (3 instancias)
while(true) {                               while(true) {                       while(true) {
pedido = generarPedido()                    pedido = retirar(pendientes)        pedido = retirar(validados)
agregar(pedido, pendientes)                 validar(pedido)                     cafe = hacerCafe(pedido)
tomarCafe()                                 agregar(pedido,validados)           servir(cafe)
}                                           }                                   }
Sincronice el pseudocódigo utilizando semáforos para que cumpla con lo pedido, 
sin generar deadlocks ni starvation.
Notas: la variable cafe tiene un atributo cafe.idCliente con el id del 
cliente que pidió ese café. El proceso Cliente tiene una función getId() que
devuelve su propio id. Variables compartidas: pendientes y validados.
*/
// - Globals -
sem_t mutexPosts;
sem_t hayPosts;
sem_t mutexValidados;
sem_t maxPedidos;
sem_t semclientes[n] = {0,0,0,0,0,0,0,0}/////.......
sem_t hayValidados;

void setup() {
    init(mutexPosts, 1);
    init(hayPosts, 0);
    init(mutexValidados, 1);
    init(maxPedidos, 50);
    init(hayValidados,0);

}

void* Cliente(void* _) {
    while(true) { 

    pedido = generarPedido()
    
    wait(maxPedidos);

    wait(mutexPendientes);
    agregar(pedido, pendientes)
    signal(mutexPendientes);

    signal(hayPendientes);    

    wait(semClientes[getId()]);
    tomarCafe()                
    }                                                  
}

void* Procesador(void* _) {
    while(true) {
    
    
    wait(hayPendientes);

    wait(mutexPendientes);    
    pedido = retirar(pendientes)
    signal(mutexPendientes);
    signal(maxPedidos);
    validar(pedido)             
        
    wait(mutexValidados);
    agregar(pedido,validados)   
    signal(mutexValidados);

    signal(hayValidados);
    
}                           
}
void* RobotBarista(void* _) {
    while(true) {

    wait(hayValidados);    
    wait(mutexValidados);
    pedido = retirar(validados);
    signal(mutexValidados);


    cafe = hacerCafe(pedido)
    servir(cafe)
    signal(semclientes[cafe.idCliente])
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


