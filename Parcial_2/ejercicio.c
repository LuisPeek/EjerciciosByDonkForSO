#include <stdio.h>

#include "../semaphores_wrap.h"

// -----------------------------------------
/*
Tres tipos de procesos se utilizan para generar y leer reportes de una base de datos de gran tamaño.
Los diferentes generadores de reportes obtienen una de las 10 conexiones disponibles, y 
luego de crear la consulta que necesitan correr, la envían al motor de base de datos.
Una vez obtenida esa información generan reportes, y una vez listos los escriben 
en un gran archivo de reportes (siendo esta la única estructura compartida entre procesos).
Una serie de procesos lectores consume luego dichos reportes, sin borrarlos del archivo en cuestión.
Dado que va creciendo cada vez más, las lecturas sobre el archivo de reportes 
pueden llevar horas, pero las escrituras están optimizadas para llevar unos pocos segundos. 
*/


sem_t semDBConexionesDis;
sem_t semPedirConexion;
sem_t semGenReportes;
sem_t mutexRepo;
sem_t semConsulta;
sem_t sem_responsConsulta;
sem_t sem_HayAlgoParaLeer;
sem_t mutexLeer;
void setup(){
  init(semDBConexionesDis,10);
  init(semGenReportes,100);
  init(mutexRepo,1);
  init(mutexLeer,1);
  init(semPedirConexion,0);
  init(semConsulta,0);
  init(sem_responsConsulta,0);
  init(sem_HayAlgoParaLeer,0);
  init(podesHacerUnaConsulta,0);
}
FILE * reportes;
void *Lector(void *_){
    
    while (1){
      nro = rand();
      wait(sem_HayAlgoParaLeer);
      wait(mutexLeer);
      rep = leer(reportes, nro);
      signal(mutexLeer);
      print(rep);
    }
}
/// (100 instancias)
void *GeneradorDeReportes(void *_){
    
    while (1){
    
    wait(semDBConexionesDis);
    db = obtenerConexion();
    signal(semPedirConexion);

    wait(podesHacerUnaConsulta)
    query = generarConsulta();
    data = correr(query, db);
    signal(semConsulta);
  

    wait(sem_responsConsulta);
    rep = generar(data);

    wait(mutexRepo);
    escribir(reportes, rep);
    signal(mutexRepo);
    signal(sem_HayAlgoParaLeer);
    }
}
///Motor de DB (1 instancia)
void *MotorDeDB(void *_){
    
    while (1){
   
    wait(semPedirConexion);
    abrirConexion();
    signal(podesHacerUnaConsulta);

    wait(semConsulta);
    devolverConsulta();
    signal(sem_responsConsulta);
    
    cerrarConexion();
      signal(semDBConexionesDis);

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
