#include "_color.h"

_color::_color()
{
    _r = 0;
    _g = 0;
    _b = 0;
    _a = 0;
}

_color::_color(int r, int g, int b)
{
    _r = r;
    _g = g;
    _b = b;
    _a = 255;
}

_color::_color(int r, int g, int b, int a)
{
    _r = r;
    _g = g;
    _b = b;
    _a = a;
}

_color::~_color()
{}

SDL_Color _color::getAsSDLColor()
{
#if defined __llvm__
    SDL_Color col;
    col.r = _r;
    col.g = _g;
    col.b = _b;
    col.a = _a;
    return col;
#else
    return SDL_Color{_r,_g,_b,_a};
#endif
}

int _color::getR()
{
    return _r;
}

int _color::getG()
{
    return _g;
}

int _color::getB()
{
    return _b;
}

int _color::getA()
{
    return _a;
}

void _color::setR(int r)
{
    _r = r;
}

void _color::setG(int g)
{
    _g = g;
}

void _color::setB(int b)
{
    _b = b;
}

void _color::setA(int a)
{
    _a = a;
}
