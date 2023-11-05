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
    bool primer_encuentro=false;
    int diferencia=0,suma=0;
    /*char _color_secundario;
    if(_color=='-'){
        _color_secundario='*';

    }
    else _color_secundario='-';*/

    /*VERIFICAR SI AMBAS COORDENADAS SE ENCUENTRAN EN  LAS DIMENSIONES DE LA MATRIZ*/
    if( ( (_fila_actual<0 && _fila_actual>=dimension_tablero) && (_columna_actual<0 && _columna_actual>=dimension_tablero) ) | ( (_fila_destino<0 && _fila_destino>=dimension_tablero) && (_columna_destino<0 && _columna_destino>=dimension_tablero)) ){
        cout<<"coordenadas fuera de rango del tablero";
    }
    else{
        if(matriz_tablero[_fila_destino][_columna_destino].get_color()=='\0'){
            diferencia=_fila_destino-_columna_destino;
            suma=_fila_destino+_columna_destino;
            /*CASO 1 --->*/
            if(_fila_destino==_fila_actual && _columna_destino>_columna_actual){
                for(int j=_columna_actual+1;j<_columna_destino && primer_encuentro==false;j++){
                    if((matriz_tablero[_fila_destino][j].get_color()=='\0') |(_color==matriz_tablero[_fila_destino][j].get_color())){
                        primer_encuentro=true;
                    }

                }
                if(primer_encuentro){
                    cout<<"Movimiento no valido."<<endl;
                }
                else{
                    agregar_ficha(_fila_destino,_columna_destino,_color);
                }
            }

            /*CASO 2 <---*/
            else if(_fila_destino==_fila_actual && _columna_destino<_columna_actual){
                for(int j=_columna_actual-1;j>_columna_destino && primer_encuentro==false;j--){
                    if((matriz_tablero[_fila_destino][j].get_color()=='\0') |(_color==matriz_tablero[_fila_destino][j].get_color())){
                        primer_encuentro=true;
                    }

                }
                if(primer_encuentro){
                    cout<<"Movimiento no valido."<<endl;
                }
                else{
                    agregar_ficha(_fila_destino,_columna_destino,_color);
                }
            }
            /* CASO 3 ARRIBA*/
            else if(_fila_destino<_fila_actual && _columna_destino==_columna_actual){
                for(int i=_fila_actual-1;i>_fila_destino && primer_encuentro==false;i--){
                    if((matriz_tablero[i][_fila_actual].get_color()=='\0') |(_color==matriz_tablero[i][_fila_actual].get_color())){
                        primer_encuentro=true;
                    }

                }
                if(primer_encuentro){
                    cout<<"Movimiento no valido."<<endl;
                }
                else{
                    agregar_ficha(_fila_destino,_columna_destino,_color);
                }
            }

            /*CASO 4 ABAJO*/
            else if(_fila_destino>_fila_actual && _columna_destino==_columna_actual){
                for(int i=_fila_actual+1;i>_fila_destino && primer_encuentro==false;i++){
                    if((matriz_tablero[i][_fila_actual].get_color()=='\0') |(_color==matriz_tablero[i][_fila_actual].get_color())){
                        primer_encuentro=true;
                    }

                }
                if(primer_encuentro){
                    cout<<"Movimiento no valido."<<endl;
                }
                else{
                    agregar_ficha(_fila_destino,_columna_destino,_color);
                }
            }

            /*CASO 5 DIAGONAL IZQUIERDA ARRIBA*/
            else if(_fila_destino<_fila_actual && _columna_destino<_columna_actual){
                for(int i=_fila_actual-1;i>_fila_destino && primer_encuentro==false;i--){
                    for(int j=_columna_actual-1;j>_columna_destino && primer_encuentro==false;j--){
                        if(i-j==diferencia){
                            if((matriz_tablero[i][j].get_color()=='\0') | (matriz_tablero[i][j].get_color()==_color)){
                                primer_encuentro=true;
                                }
                        }
                    }
                }

                if(primer_encuentro){
                    cout<<"Movimiento no valido."<<endl;
                }
                else{
                    agregar_ficha(_fila_destino,_columna_destino,_color);
                }
            }

            /*CASO 6 DIAGONAL IZQUIERDA ABAJO */
            else if(_fila_destino>_fila_actual && _columna_destino<_columna_actual){
                for(int i=_fila_actual+1;i<_fila_destino && primer_encuentro==false;i++){
                    for(int j=_columna_actual-1;j>_columna_destino && primer_encuentro==false;j--){
                        if(i+j==suma){
                                if((matriz_tablero[i][j].get_color()=='\0') | (matriz_tablero[i][j].get_color()==_color)){
                                primer_encuentro=true;
                                }
                        }
                    }
                }

                if(primer_encuentro){
                    cout<<"Movimiento no valido."<<endl;
                }
                else{
                    agregar_ficha(_fila_destino,_columna_destino,_color);
                }
            }

            /*CASO 7 DIAGONAL DERECHA ABAJO*/
            else if(_fila_destino>_fila_actual && _columna_destino>_columna_actual){
                for(int i=_fila_actual+1;i<_fila_destino && primer_encuentro==false;i++){
                    for(int j=_columna_actual+1;j<_columna_destino && primer_encuentro==false;j++){
                        if(i-j==diferencia){
                                if((matriz_tablero[i][j].get_color()=='\0') | (matriz_tablero[i][j].get_color()==_color)){
                                primer_encuentro=true;
                                }
                        }
                    }
                }

                if(primer_encuentro){
                    cout<<"Movimiento no valido."<<endl;
                }
                else{
                    agregar_ficha(_fila_destino,_columna_destino,_color);
                }
            }

            /*CASO 8 DIAGONAL DERECHA ARRIBA*/
            else if(_fila_destino<_fila_actual && _columna_destino>_columna_actual){
                for(int i=_fila_actual-1;i>_fila_destino && primer_encuentro==false;i--){
                    for(int j=_columna_actual+1;j<_columna_destino && primer_encuentro==false;j++){
                        if(i+j==suma){
                                if((matriz_tablero[i][j].get_color()=='\0') | (matriz_tablero[i][j].get_color()==_color)){
                                primer_encuentro=true;
                            }
                        }
                    }
                }

                if(primer_encuentro){
                    cout<<"Movimiento no valido."<<endl;
                }
                else{
                    agregar_ficha(_fila_destino,_columna_destino,_color);
                }
            }
        }
        else{
            cout<<"Movimiento no valido."<<endl;

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
