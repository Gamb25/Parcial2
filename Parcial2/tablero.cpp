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
    bool posible_arreglo[8]={false}, posible=false;
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
        if(( (_fila_destino==_fila_actual) &&(_columna_destino>_columna_actual) )|( (_fila_destino==_fila_actual) &&(_columna_destino<_columna_actual) )
            |( (_fila_destino>_fila_actual) &&(_columna_destino==_columna_actual) )|( (_fila_destino<_fila_actual) &&(_columna_destino==_columna_actual) )|
            ( (_fila_destino>_fila_actual) &&(_columna_destino>_columna_actual) )|( (_fila_destino<_fila_actual) &&(_columna_destino<_columna_actual) )|
            ( (_fila_destino>_fila_actual) &&(_columna_destino<_columna_actual) )|( (_fila_destino<_fila_actual) &&(_columna_destino>_columna_actual) ))
        {

            if(matriz_tablero[_fila_destino][_columna_destino].get_color()=='\0'){
                /*VERIFICAR QUE  SE EN LAS ESQUINAS*/
                if(_fila_destino==dimension_tablero-1 && _columna_destino==dimension_tablero-1){
                    posible_arreglo[0]=metodo_busqueda_sandwich(2,_fila_actual,_columna_actual,_fila_destino,_columna_destino,_color);//Izquierda
                    posible_arreglo[1]=metodo_busqueda_sandwich(3,_fila_actual,_columna_actual,_fila_destino,_columna_destino,_color);//Arriba
                    posible_arreglo[2]=metodo_busqueda_sandwich(5,_fila_actual,_columna_actual,_fila_destino,_columna_destino,_color);//Izquierda Arriba
                    for(int i=0;i<3 && posible==false;i++){
                        if(posible_arreglo[i]==true){
                            posible=true;
                        }
                    }


                }
                else if(_fila_destino==dimension_tablero-1 && _columna_destino==0){
                    posible_arreglo[0]=metodo_busqueda_sandwich(1,_fila_actual,_columna_actual,_fila_destino,_columna_destino,_color);//Derecha
                    posible_arreglo[1]=metodo_busqueda_sandwich(3,_fila_actual,_columna_actual,_fila_destino,_columna_destino,_color);//Arriba
                    posible_arreglo[2]=metodo_busqueda_sandwich(8,_fila_actual,_columna_actual,_fila_destino,_columna_destino,_color);//Derecha arriba
                    for(int i=0;i<3 && posible==false;i++){
                        if(posible_arreglo[i]==true){
                            posible=true;
                        }
                    }

                }
                else if(_fila_destino==0 && _columna_destino==dimension_tablero-1){
                    posible_arreglo[0]=metodo_busqueda_sandwich(2,_fila_actual,_columna_actual,_fila_destino,_columna_destino,_color);//Izquierda
                    posible_arreglo[1]=metodo_busqueda_sandwich(4,_fila_actual,_columna_actual,_fila_destino,_columna_destino,_color);//Abajo
                    posible_arreglo[2]=metodo_busqueda_sandwich(6,_fila_actual,_columna_actual,_fila_destino,_columna_destino,_color);//Izquierda Abajo
                    for(int i=0;i<3 && posible==false;i++){
                        if(posible_arreglo[i]==true){
                            posible=true;
                        }
                    }

                }
                else if(_fila_destino==0 && _columna_destino==0){
                    posible_arreglo[0]=metodo_busqueda_sandwich(1,_fila_actual,_columna_actual,_fila_destino,_columna_destino,_color);//Derecha
                    posible_arreglo[1]=metodo_busqueda_sandwich(4,_fila_actual,_columna_actual,_fila_destino,_columna_destino,_color);//Abajo
                    posible_arreglo[2]=metodo_busqueda_sandwich(7,_fila_actual,_columna_actual,_fila_destino,_columna_destino,_color);//Derecha Abajo.
                    for(int i=0;i<3 && posible==false;i++){
                        if(posible_arreglo[i]==true){
                            posible=true;
                        }
                    }
                }
                else if((_fila_destino<dimension_tablero-1)&&(_fila_destino>0) &&(_columna_destino==0)){
                    posible_arreglo[0]=metodo_busqueda_sandwich(3,_fila_actual,_columna_actual,_fila_destino,_columna_destino,_color);//Arriba
                    posible_arreglo[1]=metodo_busqueda_sandwich(4,_fila_actual,_columna_actual,_fila_destino,_columna_destino,_color);//Abajo
                    posible_arreglo[2]=metodo_busqueda_sandwich(1,_fila_actual,_columna_actual,_fila_destino,_columna_destino,_color);//Derecha
                    posible_arreglo[3]=metodo_busqueda_sandwich(8,_fila_actual,_columna_actual,_fila_destino,_columna_destino,_color);//Derecha arriba
                    posible_arreglo[4]=metodo_busqueda_sandwich(7,_fila_actual,_columna_actual,_fila_destino,_columna_destino,_color);//Derecha Abajo.
                    for(int i=0;i<4 && posible==false;i++){
                        if(posible_arreglo[i]==true){
                            posible=true;
                        }
                    }
                }
                else if((_fila_destino<dimension_tablero-1)&&(_fila_destino>0) &&(_columna_destino==dimension_tablero-1)){
                    posible_arreglo[0]=metodo_busqueda_sandwich(3,_fila_actual,_columna_actual,_fila_destino,_columna_destino,_color);//Arriba
                    posible_arreglo[1]=metodo_busqueda_sandwich(4,_fila_actual,_columna_actual,_fila_destino,_columna_destino,_color);//Abajo
                    posible_arreglo[2]=metodo_busqueda_sandwich(2,_fila_actual,_columna_actual,_fila_destino,_columna_destino,_color);//Izquierda
                    posible_arreglo[3]=metodo_busqueda_sandwich(5,_fila_actual,_columna_actual,_fila_destino,_columna_destino,_color);//Izquierda Arriba
                    posible_arreglo[4]=metodo_busqueda_sandwich(6,_fila_actual,_columna_actual,_fila_destino,_columna_destino,_color);//Izquierda Abajo

                    for(int i=0;i<4 && posible==false;i++){
                        if(posible_arreglo[i]==true){
                            posible=true;
                        }
                    }
                }
                else{
                    posible_arreglo[0]=metodo_busqueda_sandwich(3,_fila_actual,_columna_actual,_fila_destino,_columna_destino,_color);//Arriba
                    posible_arreglo[1]=metodo_busqueda_sandwich(4,_fila_actual,_columna_actual,_fila_destino,_columna_destino,_color);//Abajo
                    posible_arreglo[2]=metodo_busqueda_sandwich(2,_fila_actual,_columna_actual,_fila_destino,_columna_destino,_color);//Izquierda
                    posible_arreglo[3]=metodo_busqueda_sandwich(5,_fila_actual,_columna_actual,_fila_destino,_columna_destino,_color);//Izquierda Arriba
                    posible_arreglo[4]=metodo_busqueda_sandwich(6,_fila_actual,_columna_actual,_fila_destino,_columna_destino,_color);//Izquierda Abajo
                    posible_arreglo[5]=metodo_busqueda_sandwich(1,_fila_actual,_columna_actual,_fila_destino,_columna_destino,_color);//Derecha
                    posible_arreglo[6]=metodo_busqueda_sandwich(8,_fila_actual,_columna_actual,_fila_destino,_columna_destino,_color);//Derecha arriba
                    posible_arreglo[7]=metodo_busqueda_sandwich(7,_fila_actual,_columna_actual,_fila_destino,_columna_destino,_color);//Derecha Abajo.
                    for(int i=0;i<7 && posible==false;i++){
                        if(posible_arreglo[i]==true){
                            posible=true;
                        }
                    }
                }
                if(posible){
                    cout<<"Movimiento valido"<<endl;
                    agregar_ficha(_fila_destino,_columna_destino,_color);
                    for (int i=1;i<=8;i++){
                        cambio_color_sandwich(i,_fila_destino,_columna_destino,_color);
                    }

                }
                else{
                    cout<<"Movimiento no valido"<<endl;
                }
            }
            else{
                cout<<"Movimiento no valido."<<endl;
            }

        }
        else{
            cout<<"Movimiento no valido"<<endl;

        }

    }




}

bool tablero::metodo_busqueda_sandwich(int caso,int _fila_actual,int _columna_actual, int _fila_destino, int _columna_destino, char _color)
{
    bool posible=true,primer_encuentro= false;
    int diferencia=_fila_actual-_columna_actual,suma=_fila_actual+_columna_actual;

    if(matriz_tablero[_fila_destino][_columna_destino].get_color()=='\0'){
        /*Caso 1--->*/
        if(caso==1){
            if((_fila_actual!=_fila_destino)|(matriz_tablero[_fila_actual][_columna_actual+1].get_color()==_color) |(matriz_tablero[_fila_actual][_columna_actual+1].get_color()=='\0')){
                //Movimiento no valido.
                posible=false;
            }
            else{
                for(int j=_columna_actual+1;j<_fila_destino && primer_encuentro==false;j++){
                    if((matriz_tablero[_fila_destino][j].get_color()=='\0') |(_color==matriz_tablero[_fila_destino][_columna_actual+1].get_color()) |((j==dimension_tablero-1) && (matriz_tablero[_fila_destino][j].get_color()!=_color))){
                        primer_encuentro=true;
                    }
                    else if(matriz_tablero[_fila_destino][j].get_color()==_color){
                        primer_encuentro=true;
                    }


                }
                if(primer_encuentro){
                    //Movimiento no valido.
                    posible=false;

                }
            }
        }
        /*Caso 2 <---*/
        else if(caso==2){
            if((_fila_actual!=_fila_destino)|(matriz_tablero[_fila_actual][_columna_actual-1].get_color()==_color) |(matriz_tablero[_fila_actual][_columna_actual-1].get_color()=='\0')){
                //Movimiento no valido.
                posible=false;
            }
            else{
                for(int j=_columna_actual-1;j>_columna_destino && primer_encuentro==false;j--){
                    if((matriz_tablero[_fila_destino][j].get_color()=='\0') |(_color==matriz_tablero[_fila_destino][_columna_actual-1].get_color()) | ((j==0) && (matriz_tablero[_fila_destino][j].get_color()!=_color))){
                        primer_encuentro=true;
                    }
                    else if(matriz_tablero[_fila_destino][j].get_color()==_color){
                        primer_encuentro=true;

                    }

                }
                if(primer_encuentro){
                    //Movimiento no valido.
                    posible=false;

                }
            }
        }
        /*Caso 3 ARRIBA*/
        else if(caso==3){
            if((_columna_actual!=_columna_destino)|(matriz_tablero[_fila_actual-1][_columna_actual].get_color()==_color) |(matriz_tablero[_fila_actual-1][_columna_actual].get_color()=='\0')){
                //Movimiento no valido.
                posible=false;
            }
            else{
                for(int i=_fila_actual-1;i>_fila_destino && primer_encuentro==false;i--){
                    if((matriz_tablero[i][_columna_destino].get_color()=='\0') |(_color==matriz_tablero[_fila_actual-1][_columna_destino].get_color())|((i==0) && (matriz_tablero[i][_columna_destino].get_color()!=_color))){
                        primer_encuentro=true;
                    }
                    else if(matriz_tablero[i][_columna_destino].get_color()==_color){
                        primer_encuentro=true;

                    }

                }
                if(primer_encuentro){
                    //Movimiento no valido.
                    posible=false;

                }
            }

        }
        /*Caso 4 ABAJO*/
        else if(caso==4){
            if((_columna_actual!=_columna_destino)|(matriz_tablero[_fila_actual+1][_columna_actual].get_color()==_color) |(matriz_tablero[_fila_actual+1][_columna_actual].get_color()=='\0')){
                //Movimiento no valido.
                posible=false;
            }
            else{
                for(int i=_fila_actual+1;i<_fila_destino && primer_encuentro==false;i++){
                    if((matriz_tablero[i][_columna_destino].get_color()=='\0') |(_color==matriz_tablero[_fila_actual+1][_columna_destino].get_color())|((i==dimension_tablero-1) && (matriz_tablero[i][_columna_destino].get_color()!=_color))){
                        primer_encuentro=true;
                    }
                    else if(matriz_tablero[i][_columna_destino].get_color()==_color){
                        primer_encuentro=true;

                    }

                }
                if(primer_encuentro){
                    //Movimiento no valido.
                    posible=false;

                }
            }


        }
        /*Caso 5 Diagonal IZQUIERDA ARRIBA */
        else if(caso==5){
            if((diferencia!=_fila_destino-_columna_destino)|(matriz_tablero[_fila_actual-1][_columna_actual-1].get_color()==_color) |(matriz_tablero[_fila_actual-1][_columna_actual-1].get_color()=='\0')){
                //Movimiento no valido.
                posible=false;
            }
            else{
                for(int i=_fila_actual-1;i>_fila_destino && primer_encuentro==false;i--){
                    for(int j=_columna_actual-1;j>_columna_destino && primer_encuentro==false;j--){
                        if(i-j==diferencia){
                            if((matriz_tablero[i][j].get_color()=='\0') | (matriz_tablero[_fila_actual-1][_columna_actual-1].get_color()==_color)){
                                primer_encuentro=true;
                            }
                            else if(( ( (i==0) && (j==0) ) && (matriz_tablero[i][j].get_color()!=_color))){
                                primer_encuentro=true;
                            }
                            else if(matriz_tablero[i][j].get_color()==_color){
                                primer_encuentro=true;


                            }

                        }
                    }
                }

                if(primer_encuentro){
                    //Movimiento no valido.
                    posible=false;

                }
            }
        }
        /*Caso 6 Diagonal IZQUIERDA ABAJO */
        else if(caso==6){
            if((suma!=_fila_destino+_columna_destino)|(matriz_tablero[_fila_actual+1][_columna_actual-1].get_color()==_color )|(matriz_tablero[_fila_actual+1][_columna_actual-1].get_color()=='\0')){
                //Movimiento no valido.
                posible=false;
            }
            else{
                for(int i=_fila_actual+1;i<_fila_destino && primer_encuentro==false;i++){
                    for(int j=_columna_actual-1;j>_columna_destino && primer_encuentro==false;j--){
                        if(i+j==suma){
                            if((matriz_tablero[i][j].get_color()=='\0') | (matriz_tablero[_fila_actual+1][_columna_actual-1].get_color()==_color)){
                                primer_encuentro=true;
                            }
                            else if(( ( (i==dimension_tablero-1) && (j==0) ) && (matriz_tablero[i][j].get_color()!=_color))){
                                primer_encuentro=true;
                            }
                            else if(matriz_tablero[i][j].get_color()==_color){
                                primer_encuentro=true;


                            }
                        }
                    }
                }

                if(primer_encuentro){
                    //Movimiento no valido.
                    posible=false;

                }
            }

        }
        /*CASO 7 DIAGONAL ABAJO DERECHA*/
        else if (caso==7){
            if((diferencia!=_fila_destino-_columna_destino)|(matriz_tablero[_fila_actual+1][_columna_actual+1].get_color()==_color) |(matriz_tablero[_fila_actual+1][_columna_actual+1].get_color()=='\0')){
                //Movimiento no valido.
                posible=false;
            }
            else{
                for(int i=_fila_actual+1;i<_fila_destino && primer_encuentro==false;i++){
                    for(int j=_columna_actual+1;j<_columna_destino && primer_encuentro==false;j++){
                        if(i-j==diferencia){
                            if((matriz_tablero[i][j].get_color()=='\0') | (matriz_tablero[_fila_actual+1][_columna_actual+1].get_color()==_color)){
                                primer_encuentro=true;
                            }
                            else if(( ( (i==dimension_tablero-1) && (j==dimension_tablero-1) ) && (matriz_tablero[i][j].get_color()!=_color))){
                                primer_encuentro=true;
                            }
                            else if(matriz_tablero[i][j].get_color()==_color){
                                primer_encuentro=true;

                            }

                        }
                    }
                }

                if(primer_encuentro){
                    //Movimiento no valido.
                    posible=false;

                }
            }

        }
        /*CASO 8 DIAONAL DERECHA ARRIBA*/
        else if (caso==8){
            if((suma!=_fila_destino+_columna_destino)|(matriz_tablero[_fila_actual-1][_columna_actual+1].get_color()==_color)|(matriz_tablero[_fila_actual-1][_columna_actual+1].get_color()=='\0')){
                //Movimiento no valido.
                posible=false;
            }
            else{
                for(int i=_fila_actual-1;i>_fila_destino && primer_encuentro==false;i--){
                    for(int j=_columna_actual+1;j<_columna_destino && primer_encuentro==false;j++){
                        if(i+j==suma){
                            if((matriz_tablero[i][j].get_color()=='\0') | (matriz_tablero[_fila_actual-1][_columna_actual+1].get_color()==_color)){
                                primer_encuentro=true;
                            }
                            else if(( ( (i==0) && (j==dimension_tablero-1) ) && (matriz_tablero[i][j].get_color()!=_color))){
                                primer_encuentro=true;
                            }
                            else if(matriz_tablero[i][j].get_color()==_color){
                                primer_encuentro=true;


                            }
                        }
                    }
                }

                if(primer_encuentro){
                    //Movimiento no valido.
                    posible=false;

                }
            }
        }
        else{
            //Movimiento no valido.
            posible=false;

        }
        return posible;
    }
    else{
        posible=false;
        return posible;
    }

}

void tablero::cambio_color_sandwich(int caso, int _fila_destino, int _columna_destino,char _color)
{
    bool primer_encuentro= false;
    int diferencia=_fila_destino-_columna_destino,suma=_fila_destino+_columna_destino;
    /*Caso 1--->*/
    if(caso==1){
        if ((matriz_tablero[_fila_destino][_columna_destino+1].get_color()!=_color) && (matriz_tablero[_fila_destino][_columna_destino+1].get_color()!='\0')){
            for(int j=_columna_destino+1;j<dimension_tablero && primer_encuentro==false;j++){
                if((matriz_tablero[_fila_destino][j].get_color()=='\0') |(_color==matriz_tablero[_fila_destino][_columna_destino+1].get_color()) |((j==dimension_tablero-1) && (matriz_tablero[_fila_destino][j].get_color()!=_color))){
                    primer_encuentro=true;
                }
                else if(matriz_tablero[_fila_destino][j].get_color()==_color){
                    primer_encuentro=true;
                    for(int t=_columna_destino+1;t<j;t++){
                        set_color(_color);
                    }
                }
            }
        }


    }

    /*Caso 2 <---*/
    else if(caso==2){
        if ((matriz_tablero[_fila_destino][_columna_destino-1].get_color()!=_color) && (matriz_tablero[_fila_destino][_columna_destino-1].get_color()!='\0')){
            for(int j=_columna_destino-1;j>=0 && primer_encuentro==false;j--){
                if((matriz_tablero[_fila_destino][j].get_color()=='\0') |(_color==matriz_tablero[_fila_destino][_columna_destino-1].get_color()) | ((j==0) && (matriz_tablero[_fila_destino][j].get_color()!=_color))){
                    primer_encuentro=true;
                }
                else if(matriz_tablero[_fila_destino][j].get_color()==_color){
                    primer_encuentro=true;
                    for(int t=_columna_destino-1;t<j;t++){
                        set_color(_color);
                    }

                }

            }

        }
    }
    /*Caso 3 ARRIBA*/
    else if(caso==3){
        if((matriz_tablero[_fila_destino-1][_columna_destino].get_color()!=_color) && (matriz_tablero[_fila_destino-1][_columna_destino].get_color()!='\0')){
            for(int i=_fila_destino -1;i>=0 && primer_encuentro==false;i--){
                if((matriz_tablero[i][_columna_destino].get_color()=='\0') |(_color==matriz_tablero[_fila_destino-1][_columna_destino].get_color())|((i==0) && (matriz_tablero[i][_columna_destino].get_color()!=_color))){
                    primer_encuentro=true;
                }
                else if(matriz_tablero[i][_columna_destino].get_color()==_color){
                    primer_encuentro=true;
                    for(int k=_fila_destino-1;k>i;k--){
                        matriz_tablero[k][_columna_destino].set_color(_color);
                    }

                }

            }

        }

    }
    /*Caso 4 ABAJO*/
    else if(caso==4){
        if((matriz_tablero[_fila_destino+1][_columna_destino].get_color()!=_color) && (matriz_tablero[_fila_destino+1][_columna_destino].get_color()!='\0')){
            for(int i=_fila_destino+1;i<dimension_tablero && primer_encuentro==false;i++){
                if((matriz_tablero[i][_columna_destino].get_color()=='\0') |(_color==matriz_tablero[_fila_destino+1][_columna_destino].get_color())|((i==dimension_tablero-1) && (matriz_tablero[i][_columna_destino].get_color()!=_color))){
                    primer_encuentro=true;
                }
                else if(matriz_tablero[i][_columna_destino].get_color()==_color){
                    primer_encuentro=true;
                    for(int k=_fila_destino+1;k<i;k++){
                        matriz_tablero[k][_columna_destino].set_color(_color);
                    }

                }
            }
        }
    }
    /*Caso 5 Diagonal IZQUIERDA ARRIBA */
    else if(caso==5){
        if((matriz_tablero[_fila_destino-1][_columna_destino-1].get_color()!=_color) && (matriz_tablero[_fila_destino-1][_columna_destino-1].get_color()!='\0')){
            for(int i=_fila_destino-1;i>=0 && primer_encuentro==false;i--){
                for(int j=_columna_destino-1;j>=0 && primer_encuentro==false;j--){
                    if(i-j==diferencia)
                    {
                        if((matriz_tablero[i][j].get_color()=='\0') | (matriz_tablero[_fila_destino-1][_columna_destino-1].get_color()==_color)){
                            primer_encuentro=true;
                        }
                        else if(( ( (i==0) && (j==0) ) && (matriz_tablero[i][j].get_color()!=_color))){
                            primer_encuentro=true;
                        }
                        else if(matriz_tablero[i][j].get_color()==_color){
                            primer_encuentro=true;
                            for(int k=_fila_destino-1;k>i;k--){
                                for(int t=_columna_destino-1;t>j;t--){
                                    matriz_tablero[k][t].set_color(_color);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    /*Caso 6 Diagonal IZQUIERDA ABAJO */
    else if(caso==6){
        if((matriz_tablero[_fila_destino+1][_columna_destino-1].get_color()!=_color) && (matriz_tablero[_fila_destino+1][_columna_destino-1].get_color()!='\0')){
            for(int i=_fila_destino+1;i<dimension_tablero && primer_encuentro==false;i++){
                for(int j=_columna_destino-1;j>=0 && primer_encuentro==false;j--){
                    if(i+j==suma){
                        if((matriz_tablero[i][j].get_color()=='\0') | (matriz_tablero[_fila_destino+1][_columna_destino-1].get_color()==_color)){
                            primer_encuentro=true;
                        }
                        else if(( (i==dimension_tablero-1) && (j==0) ) && (matriz_tablero[i][j].get_color()!=_color)){
                            primer_encuentro=true;
                        }
                        else if(matriz_tablero[i][j].get_color()==_color){
                            primer_encuentro=true;
                            for(int k=_fila_destino+1;k<i;k++){
                                for(int t=_columna_destino-1;t>j;t--){
                                    matriz_tablero[k][t].set_color(_color);
                                }
                            }
                        }
                    }
                }
            }

        }

    }
    /*CASO 7 DIAGONAL ABAJO DERECHA*/
    else if (caso==7){
        if((matriz_tablero[_fila_destino+1][_columna_destino+1].get_color()!=_color) && (matriz_tablero[_fila_destino+1][_columna_destino+1].get_color()!='\0')){
            for(int i=_fila_destino+1;i<dimension_tablero && primer_encuentro==false;i++){
                for(int j=_columna_destino+1;j<dimension_tablero && primer_encuentro==false;j++){
                    if(i-j==diferencia){
                        if((matriz_tablero[i][j].get_color()=='\0') | (matriz_tablero[_fila_destino+1][_columna_destino+1].get_color()==_color)){
                            primer_encuentro=true;
                        }
                        else if(( (i==dimension_tablero-1) && (j==dimension_tablero-1) ) && (matriz_tablero[i][j].get_color()!=_color)){
                            primer_encuentro=true;
                        }
                        else if (matriz_tablero[i][j].get_color()==_color){
                            primer_encuentro=true;
                            for(int k=_fila_destino+1;k<i;k++){
                                for(int t=_columna_destino+1;t<j;t++){
                                    matriz_tablero[k][t].set_color(_color);
                                }
                            }

                        }

                    }
                }
            }

        }
    }
    /*CASO 8 DIAONAL DERECHA ARRIBA*/
    else if (caso==8){
        if((matriz_tablero[_fila_destino-1][_columna_destino+1].get_color()!=_color) && (matriz_tablero[_fila_destino-1][_columna_destino+1].get_color()!='\0')){
            for(int i=_fila_destino-1;i>=0 && primer_encuentro==false;i--){
                for(int j=_columna_destino+1;j<_columna_destino && primer_encuentro==false;j++){
                    if(i+j==suma){
                        if((matriz_tablero[i][j].get_color()=='\0') | (matriz_tablero[_fila_destino-1][_columna_destino+1].get_color()==_color)){
                            primer_encuentro=true;
                        }
                        else if(( ( (i==0) && (j==dimension_tablero-1) ) && (matriz_tablero[i][j].get_color()!=_color))){
                            primer_encuentro=true;
                        }
                        else if(matriz_tablero[i][j].get_color()==_color){
                            primer_encuentro=true;
                            for(int k=_fila_destino+1;k>i;k--){
                                for(int t=_columna_destino+1;t<j;t++){
                                    matriz_tablero[k][t].set_color(_color);
                                }
                            }

                        }

                    }
                }
            }
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
