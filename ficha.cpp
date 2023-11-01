#include "ficha.h"

ficha::ficha()
{

}
void ficha::set_color(char _color)
{
    if(_color!='-' && _color!='*' && _color!='\0'){
        throw "No es un color valido o fondo válido.\n";
    }
    color=_color;
}

char ficha::get_color()
{
    return color;
}


