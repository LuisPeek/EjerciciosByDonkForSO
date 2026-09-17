#include <stdio.h>

#include "../semaphores_wrap.h"

// -----------------------------------------
/*
Sincronice el siguiente pseudocódigo, utilizando únicamente 
funciones de semáforos, de tal manera que los procesos
impriman constantemente la frase “CANADA CAMPEON”.
*/
sem_t sem_a;
sem_t sem_c;
sem_t sem_d;
sem_t sem_n;
sem_t sem_campeon;

void setup(){
  init(sem_a, 0);
  init(sem_c, 1);
  init(sem_campeon, 0);
  init(sem_n, 2);
  init(sem_d, 1);
}
///(N instancias)
void *A(void *_){  
  while(1) {
  wait(sem_a)
  printf("A");
  signal(sem_n);
  signal(sem_d);  
  signal(sem_campeon);
  }
}

void *C(void *_){   
  while(1) {
    wait(sem_c);
    printf("C");
    signal(sem_a);
  }
}

void *D(void *_){
    
    while(1) {
      wait(sem_d);
      wait(sem_d);
      wait(sem_d);
      printf("D");
      signal(sem_a);

}

}

void *N(void *_){
    while(1) {
   wait(sem_n);
   wait(sem_n);
   wait(sem_n);
   printf("N");
   signal(sem_a);

  }
}

void *CAMPEON(void *_){
    while(1) {
    wait(sem_campeon);
    wait(sem_campeon);
    wait(sem_campeon);
    printf("CAMPEON");
    signal(sem_c);

  }
}


// --------------------------------------------
int main(){
    setup();

    create(a, ProcesoFred);

    join(a);
    

    return 0;
}
