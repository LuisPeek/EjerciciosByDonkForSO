#include <stdio.h>

#include "../semaphores_wrap.h"

// -----------------------------------------
/*
Como tienen mucho tiempo libre en su casa, dos hermanos, Fred y George, 
decidieron organizar su armario que cuenta con muchísima ropa desparramada.

Fred se encarga de sacar de a una prenda del armario, probársela y si le queda bien, 
seleccionarla para volver a guardarla en un cajón. Si no, la separa para donar. 

Mientras, George va a ir tomando de a una la ropa que haya seleccionado su hermano, 
y en base al tipo de prenda la colocará en un cajón diferente.

Existen 3 tipos de prendas, el armario cuenta con 3 cajones con una capacidad de 15 prendas cada uno. 

Su hermano menor, Ron, para molestarlos, aprovecha la ausencia de Fred cada vez que 
separa una prenda para donar, y saca otra previamente guardada en algún cajón y 
la vuelve a poner en el armario, por lo que Fred y George tendrán 
que realizar estas actividades infinitamente. 

La función "tipoDePrenda()" devuelve un número del 0 al 2 en base al tipo de 
prenda de la que se trate, y la función random() devuelve un número del 0 al 2 de manera aleatoria. 
Sincronizar utilizando únicamente semáforos para que la ropa de los hermanos esté ordenada en los cajones
*/
//Variable compartida: cajones[3]

sem_t cajones[3]={15,15,15};
sem_t mutexCajon[3]={1,1,1};
sem_t cajonesConPrendas[3] = {0,0,0};
sem_t semPrendaOk;
sem_t semSepararOk;

void setup(){
  init(semPrendaOk,0);
}
void *ProcesoFred(void *_){
    
    while (1){
      
      agarrarPrenda();

      if(quedaBien()) {

        seleccionar();
        signal(semPrendaOk);

      } else {

        separar();
        signal(semSepararOk);
      }
    }
}
void *ProcesoGeorge(void *_){
    
    while (1){
      wait(semPrendaOk);
      int id_prenda = tipoPrenda();

      wait(cajones[id_prenda]);
        wait(mutexCajon[id_prenda]);
          ponerEnCajon(cajones[id_prenda]);
        signal(mutexCajon[id_prenda]);
      signal(cajonesConPrendas[id_prenda]);
      
    }
}
void *ProcesoRon(void *_){
    
    while (1){
      ///espera a que separe algo
      wait(semSepararOk);
      int id_prenda = random();

      wait(cajonesConPrendas[id_prenda]);
        wait(mutexCajon[id_prenda]);
          sacarPrendaDelCajonYDevolverAlArmario(cajones[id_prenda]);
        signal(mutexCajon[id_prenda]);
      signal(cajones[id_prenda]);


    }
}

// --------------------------------------------
int main()
{
    setup();

    create(a, ProcesoFred);

    join(a);
    

    return 0;
}
