#include <iostream>
#include <tablero.h>
#include <string>

using namespace std;

int main()
{
    tablero juego1;
    juego1.mostrar_matriz_tablero();
    juego1.mover_ficha(3,3,3,5,'-');

    juego1.mostrar_matriz_tablero();
    return 0;
}
