#include <stdio.h>

#include "../semaphores_wrap.h"

// -----------------------------------------
/*
Peter comienza a trabajar en una empresa de envíos internacionales 
de mercadería y deberá usar sus conocimientos en sistemas operativos 
para automatizar el proceso de despacho de productos del almacén a los 
aviones correspondientes mediante robots representados en pseudocódigo.
El proceso consiste en que los robots del almacén tomen los productos a 
despachar y los dejen en una caja compartida con los robots de distribución. 
Cada uno de estos deberá tomar estos productos de la caja y posicionarse en una 
estación de etiquetado que esté disponible, una vez su producto esté etiquetado 
lo deberá despachar al avión correspondiente al destino de ese producto. 
Cada avión despegará una vez que todos los productos con ese destino estén cargados.
Notas:
En total, hay 400 productos a despachar, exactamente 80 para cada destino. 
Cada producto tiene un atributo “destino” que contiene el id del avión correspondiente al mismo.
La caja que comparten almacén y distribución tiene capacidad para 20 productos.
El proceso Distribución tiene una función “id_etiq()” que devuelve el id de la 
estación de etiquetado en la que se encuentra actualmente.
Los procesos Etiquetado y Avión tienen una función “get_id()” que devuelve su propio id.
*/
sem_t semProductos;
sem_t hayProducto;
sem_t mutexCaja;
sem_t estacionEtiquetado[4]={0,0,0,0};
sem_t estaListo;
sem_t aviones[5]={80,80,80,80,80}
sem_t espacioEnCaja;
sem_t etiqDisponibles;
void setup(){
  init(semProductos,400); 
  init(hayProducto,0);
  init(mutexCaja,1);
  init(estaListo,0);
  init(espacioEnCaja,20);
  init(etiqDisponibles,4);
}
///(N instancias)
void *ALMACEN(void *_){
    
  while(1) {
  wait(semProductos);

  producto = tomar_producto()

  wait(espacioEnCaja);
  wait(mutexCaja);
  depositar(producto, caja);
  signal(mutexCaja);

  signa(hayProducto);
}


}
///(M instancias)
void *DISTRIBUCION(void *_){
    
    while(1) {
      wait(hayProducto);

      wait(mutexCaja);
      producto = retirar(caja);
      signal(mutexCaja);
      signal(espacioEnCaja);
     
     wait(etiqDisponibles); 
posicionarse_etiquetado(id_etiq());
signal(estacionEtiquetado[id_etiq]);

wait(estaListo);
despachar(producto, producto.destino);

}


}
/// (4 instancias)
void *ETIQUETADO(void *_){
    
  while(1) {
    wait(estacionEtiquetado[get_id()]);
    etiquetar()
    signal(estaListo);
}
}
///(5 instancias)
void *AVION(void *_){
    
    despegar()

  
}
// --------------------------------------------
int main(){
    setup();

    create(a, ProcesoFred);

    join(a);
    

    return 0;
}
