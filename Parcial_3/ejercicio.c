#include <stdio.h>

#include "../semaphores_wrap.h"

// -----------------------------------------
/*
Peter se une a Los Palmeras para preparar la fiesta de Colón. 
Para ello, programa una serie de scripts que simulan su gran éxito. 
Los procesos corren infinitamente, y deben repetir 
la frase "A E E A Yo soy Sabalero. A E E A Sabalero, Sabalero". 
Dado que la idea es que el público participe, 
los procesos "Sabale" y "Público" deberían alternarse para 
correr una vez cada uno.

Sincronice los procesos utilizando únicamente semáforos 
para garantizar el correcto orden, sabiendo que las funciones 
próximo() y actual() devuelven 0 si el proceso es "Sabale" y 1 si 
el proceso es "público", y pueden ser usadas de ser necesario.
*/
sem_t A;
sem_t E;
sem_t Sabalero;
sem_t semPalmeras;
sem_t semPublico;
sem_t alternar={0,0};
sem_t estribillo;
void setup(){
  init(A,1);
  init(E,0);
  init(semPalmeras,0);
  init(Sabalero,0);
}
void *A(void *_){
    
    while (1){

    wait(A);
    print("A");
    signal(E);
    signal(E);

    wait(A);
    wait(A);
    print("A");
    signal(alternar[proximo()]);
    }
}
void *E(void *_){
    
    while (1){
      wait(E);
      print("E");
      signal(A);
    }
}
void *Sabale(void *_){
    
  while (1){
  wait(alternar[0]);
  print("Yo soy Sabalero");
  signal(A);
  
  wait(alternar[0]);
  print("Sabalero, Sabalero");
  signal(A);
  }
}
void *Publico(void *_){
    
    while (1){
  
  wait(alternar[1]);

  print("Yo soy Sabalero");
  signal(A);

  wait(alternar[1]);
  print("Sabalero, Sabalero");
  signal(A);
  }
}
// --------------------------------------------
int main(){
    setup();

    create(a, ProcesoFred);

    join(a);
    

    return 0;
}
