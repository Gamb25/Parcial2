#ifndef FICHA_H
#define FICHA_H


#include <iostream>
using namespace std;

class ficha
{
public:
    ficha();
    void set_color(char _color);
    char get_color();

private:
    char color;

};
#endif // FICHA_H
