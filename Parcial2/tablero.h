#ifndef TABLERO_H
#define TABLERO_H
#include <ficha.h>


class tablero : public ficha
{
public:
    tablero();
    ~tablero();
    int get_dimension_tablero();
    void mostrar_matriz_tablero();

private:
    int dimension_tablero=8;
    ficha** matriz_tablero;
    const char color_negro='-',color_blanco='*';

};

#endif // TABLERO_H
