#ifndef TABLERO_H
#define TABLERO_H


#include <ficha.h>


class tablero : public ficha
{
public:
    tablero();
    tablero(bool C);
    ~tablero();
    void agregar_ficha(int _fila,int _columna,char _color);
    bool mover_ficha(int _fila_actual,int _columna_actual,int _fila_destino,int _columna_destino,char _color);
    bool metodo_busqueda_sandwich(int caso,int _fila_actual,int _columna_actual, int _fila_destino, int _columna_destino, char _color);
    void cambio_color_sandwich(int caso, int _fila_destino,int _columna_destino,char _color);
    void cambio_color_sandwich_segun_caso(int _fila_destino,int _columna_destino,char _color);
    bool condicion_mientras_partida(char _color);
    bool verificador_segun_caso(int caso,int _fila_actual,int _columna_actual,char _color);
    void conversion_coordenadas(int (&_vector)[2],string _cadena);
    void partida(tablero juego);
    int get_dimension_tablero();
    void mostrar_matriz_tablero();

private:
    int dimension_tablero=8;
    ficha** matriz_tablero;
    const char color_negro='-',color_blanco='*';

};

#endif // TABLERO_H
