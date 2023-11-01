#include "tablero.h"

tablero::tablero()
{
    int x,y;
    char color;
    ficha fi;

    matriz_tablero=new ficha *[dimension_tablero];
    for(int i=0;i<dimension_tablero;i++){
        matriz_tablero[i]= new ficha[dimension_tablero];
    }
    for(int fil=0;fil<dimension_tablero;fil++){
        for(int col=0;col<dimension_tablero;col++){
            fi.set_color('\0');
            matriz_tablero[fil][col]=fi;
        }
    }

    for(int i=0;i<2;i++){
        x=dimension_tablero/2-1;
        y=x+i;
        if(i==0){
            color='-';
        }
        else{
            color='*';
        }

        fi.set_color(color);
        matriz_tablero [x][y]=fi;
    }

    for(int i=0;i<2;i++){
        x=dimension_tablero/2;
        y=x-1+i;
        if(i==0){
            color='*';
        }
        else{
            color='-';
        }

        fi.set_color(color);
        matriz_tablero [x][y]=fi;
    }
}

tablero::~tablero()
{
    for(int fil=0;fil<dimension_tablero;fil++){
        delete[] matriz_tablero[fil];
    }
    delete [] matriz_tablero;
}



void tablero::agregar_ficha(int _fila, int _columna, char _color)
{
    ficha fi;
    fi.set_color(_color);
    if((_fila>0 && _fila<dimension_tablero) && (_columna>=0 && _columna<dimension_tablero)){
        if(matriz_tablero[_fila][_columna].get_color()=='\0'){
            matriz_tablero[_fila][_columna]=fi;
            cout<<"Se agrego con exito"<<endl;
        }
    }
    else{
        cout<< "fuera de limites"<<endl;
    }


}

void tablero::mover_ficha(int _fila_actual,int _columna_actual,int _fila_destino,int _columna_destino,char _color)
{


    if(matriz_tablero[_fila_actual][_columna_actual].get_color()==_color && matriz_tablero[_fila_destino][_columna_destino].get_color()=='\0'){
        if((_fila_destino<dimension_tablero && _fila_destino>=0)&&(_columna_destino<dimension_tablero && _columna_destino>=0)){
            /*CASO 1*/
            if(_fila_destino==_fila_actual && _columna_destino==_columna_actual+2){

                agregar_ficha(_fila_destino,_columna_destino,_color);
            }
            /*CASO 2*/
            else if(_fila_destino==_fila_actual && _columna_destino==_columna_actual-2){

                agregar_ficha(_fila_destino,_columna_destino,_color);
            }
            /*CASO 3*/
            else if(_fila_destino==_fila_actual-2 && _columna_destino==_columna_actual){

                agregar_ficha(_fila_destino,_columna_destino,_color);
            }
            /*CASO 4*/
            else if(_fila_destino==_fila_actual+2 && _columna_destino==_columna_actual){

                agregar_ficha(_fila_destino,_columna_destino,_color);
            }
            /*CASO 5*/
            else if(_fila_destino==_fila_actual-2 && _columna_destino==_columna_actual-2){

                agregar_ficha(_fila_destino,_columna_destino,_color);
            }
            /*CASO 6*/
            else if(_fila_destino==_fila_actual+2 && _columna_destino==_columna_actual-2){

                agregar_ficha(_fila_destino,_columna_destino,_color);
            }
            /*CASO 7*/
            else if(_fila_destino==_fila_actual+2 && _columna_destino==_columna_actual+2){

                agregar_ficha(_fila_destino,_columna_destino,_color);
            }
            /*CASO 8*/
            else if(_fila_destino==_fila_actual-2 && _columna_destino==_columna_actual+2){

                agregar_ficha(_fila_destino,_columna_destino,_color);
            }
            else{
                cout<<"No es un movimiento valido"<<endl;
            }

        }
        else{
            cout<<"Fuera de rango del tablero"<<endl;

        }
    }
    else{
        if(matriz_tablero[_fila_actual][_columna_actual].get_color()!=_color){
            cout<<"La ficha que quieres mover no es de color "<<_color<<" es "<<matriz_tablero[_fila_actual][_columna_actual].get_color()<<endl;
        }
        else if(matriz_tablero[_fila_destino][_columna_destino].get_color()!='\0'){
            cout<<"La coordenada a donde quieres hacer el movimiento está ya ocupada por una ficha."<<endl;
        }

    }




}


int tablero::get_dimension_tablero()
{
    return dimension_tablero;
}

void tablero::mostrar_matriz_tablero()
{
    char key='A';

    for(int fil=0;fil<dimension_tablero;fil++){

        cout<<"   "<<key++;
    }
    cout<<endl;
    for(int fil=0;fil<dimension_tablero;fil++){
        cout<<fil+1;

        for(int col=0;col<dimension_tablero;col++){

            cout<<"| "<<matriz_tablero[fil][col].get_color()<<" ";
        }
        cout<<"|"<<fil+1<<endl;
    }

    key='A';
    for(int fil=1;fil<=dimension_tablero;fil++){

        cout<<"   "<<key++;

    }
    cout<<endl;
}
