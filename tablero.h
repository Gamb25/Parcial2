#ifndef TABLERO_H
#define TABLERO_H
#include <ficha.h>


class tablero : public ficha
{
public:
    tablero();
    ~tablero();
    void agregar_ficha(int _fila,int _columna,char _color);
    void mover_ficha(int _fila_actual,int _columna_actual,int _fila_destino,int _columna_destino,char _color);
    int get_dimension_tablero();
    void mostrar_matriz_tablero();

private:
    int dimension_tablero=8;
    ficha** matriz_tablero;
    const char color_negro='-',color_blanco='*';

};

#endif // TABLERO_H
