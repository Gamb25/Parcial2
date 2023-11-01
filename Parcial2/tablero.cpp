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

int tablero::get_dimension_tablero()
{
    return dimension_tablero;
}

void tablero::mostrar_matriz_tablero()
{
    char key='A';
    for(int fil=1;fil<=dimension_tablero;fil++){
        cout<<"   "<<fil;
    }
    cout<<endl;
    for(int fil=0;fil<dimension_tablero;fil++){
        cout<<key++;
        for(int col=0;col<dimension_tablero;col++){

             cout<<"| "<<matriz_tablero[fil][col].get_color()<<" ";
        }
        cout<<"|"<<endl;
    }
    for(int fil=1;fil<=dimension_tablero;fil++){
        cout<<"   "<<fil;
    }
    cout<<endl;
}
