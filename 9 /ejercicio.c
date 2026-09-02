#include <stdio.h>

#include "../semaphores_wrap.h"

// -----------------------------------------
/*
9- Se tiene un programa para simular la ejecución de penales de un partido de fútbol,
el cual consta de tres procesos:  árbitro, jugador y arquero.  El pseudo-código es el siguiente:


Las reglas que se deben cumplir son las siguientes:
Existen cinco procesos jugadores, un proceso árbitro y un proceso arquero.
Los jugadores no pueden patear si el árbitro no lo indicó.
El arquero no puede atajar si el jugador no pateó.
El árbitro sólo puede dar la orden cuando el jugador y el arquero están posicionados.
Existe una variable global GOL, la cual es modificada por la función validar_tiro(),
que indica si el último penal pateado fue gol o no.
Una vez que se valide el penal, se le pasará el turno al próximo jugador.
Los jugadores siempre patean en un orden definido (ej: jug1, jug2, …, jug5, jug1, jug2, etc).
Existe a disposición la función actual() que retorna el id del pateador actual (0-4),
y la función siguiente() que retorna el id del próximo pateador.

Provea una solución que sincronice los tres procesos usando solamente semáforos,
asegurándose que se cumplan las reglas establecidas sin producirse deadlock ni starvation.
Se deberá inicializar cada semáforo, indicando también su tipo.

*/

// - Globals -
int GOL = 0;

void setup()
{
}

void *Arbitro(void *_)
{

    while (1)
    {

        wait(posicionArquero);
        wait(posicionJugador);
        dar_orden();
        signal(puedePatear);

        wait(mutexVailidar);
        validar_tiro();
        signal(mutexResultado_J);
        signal(mutexResultado_A);
        signal(estaReady[siguiente()]);
    }
}

void *Jugadores(void *_)
{

    while (1)
    {
        wait(estaReady[actual()]);
        posicionarse();
        signal(posicionJugador);

        wait(puedePatear);
        patear();
        signal(puedeAtajar);

        wait(mutexResultado_J);
        if (GOL == 1)
        {
            festejar();
        }
        else
        {
            lamentarse();
        }
    }
}

void *Arquero(void *_)
{

    while (1)
    {

        posicionarse();
        signal(posicionArquero);

        wait(puedeAtajar);
        atajar();
        signal(mutexValidarTiro);

        wait(mutexResultado_J);
        if (GOL == 0)
        {
            festejar();
        }
        else
        {
            lamentarse();
        }
    }
}

// --------------------------------------------
int main()
{
    setup();

    create(a, Arbitro);
    create(b, Jugadores);
    create(c, Arquero);

    join(a);
    join(b);
    join(c);

    return 0;
}
