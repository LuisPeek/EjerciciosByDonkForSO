#include <stdio.h>

#include "../semaphores_wrap.h"

// -----------------------------------------
/*
1° Parcial 2C2025 (TM) · Práctica 3 · 04/10/2025
Inicialice los semáforos utilizados en el pseudocódigo de tal 
forma que los hilos A, M, C, R, E y N impriman de forma
coordinada y repetida la palabra MACARENA.
*/
sem_t sem_A;
sem_t sem_m;
sem_t sem_c;
sem_t sem_r;
sem_t sem_e;
sem_t sem_n;
void setup(){
  init(sem_m, 3);
  init(sem_a, 0);
  init(sem_c, 2);
  init(sem_r, 1);
  init(sem_e, 0);
  init(sem_n, 0);
}
///(N instancias)
void *A(void *_){
    
  while(1) {
  wait(sem_A);
  printf("A");
  signal(sem_m);
  signal(sem_c);
  signal(sem_r);

}


}
///(M instancias)
void *M(void *_){
    
    while(1) {
      wait(sem_m);
      wait(sem_m);
      wait(sem_m);
      printf("M");
      signal(sem_A);

}

}
/// (4 instancias)
void *C(void *_){
    
  while(1) {
    wait(sem_c);
    wait(sem_c);
    wait(sem_c);
    printf("C");
    signal(sem_A);

   
}
}
///(5 instancias)
void *R(void *_){
    while(1) {
    wait(sem_r);
    wait(sem_r);
    wait(sem_r);
    printf("R");
    signal(sem_e);

  }
}

void *E(void *_){
    while(1) {
    wait(sem_e);
    printf("E");
    signal(sem_n);

  }
}

void *N(void *_){
    while(1) {
    wait(sem_n);
    printf("N");
    signal(sem_A);
  }
}


// --------------------------------------------
int main(){
    setup();

    create(a, ProcesoFred);

    join(a);
    

    return 0;
}
