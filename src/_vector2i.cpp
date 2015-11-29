#include "_vector2i.h"

_vector2i::_vector2i()
{
    x = 0;
    y = 0;
}

_vector2i::_vector2i(int _x, int _y)
{
    x = _x;
    y = _y;
}

void _vector2i::setY(int _y)
{
    y = _y;
}
void _vector2i::setX(int _x)
{
    x = _x;
}

int _vector2i::getX()
{
    return x;
}
int _vector2i::getY()
{
    return y;
}

_vector2i::~_vector2i()
{}
