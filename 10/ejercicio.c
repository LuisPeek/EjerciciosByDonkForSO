#include <stdio.h>

#include "../semaphores_wrap.h"

// -----------------------------------------
/*
10- Sincronice el siguiente código, correspondiente a un proceso que genera procesos hijos, 
para evitar inconsistencias, deadlocks e inanición. Además debe tener en cuenta lo siguiente:


   1 El archivo donde se escriben los logs es único.
   2 No debe haber más de 50 procesos en ejecución
   3 El padre debe escribir en el log antes que el hijo recién creado.
    */
sem_t mutexLogs;
sem_t mutexLogsHijo;
sem_t semCantidadProcesos;
void setup(){

    init(mutexLogs,1);
    init(mutexLogsHijo,0);
    init(semCantidadProcesos,49);
}

int pid;
void *Main(void *_){
    
    while (1){

        wait(semCantidadProcesos);
        pid = fork();
        
        
        if (pid < 0) {
        
          wait(mutexLogs);
          print("log(Error)");
          signal(mutexLogs);

        } else if (pid == 0) {
            
          wait(mutexLogsHijo);  
          wait(mutexLogs);
          printf("log(Y yo soy el hijo);");
          signal(mutexLogs);
          
          realizarTarea();
          signal(semCantidadProcesos);
          // Finaliza el proceso hijo
          
          exit(0);
        
        } else { // Padre
        

          wait(mutexLogs);
          printf("log(pid +  soy tu padre)");
          signal(mutexLogs);
          signal(mutexLogsHijo);       
        }
        
    }
}


// --------------------------------------------
int main()
{
    setup();

    create(a, Main);

    join(a);
    

    return 0;
}
