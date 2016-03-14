#include "_vector2i.h"

_vector2i::_vector2i()
{
    x = 0;
    y = 0;
}

/*_vector2i operator+ (const _vector2i& first, const _vector2i& second)
{
    //_vector2i temp = _vector2i((first.getX() + second.getX()), (first.getY() + second.getY()));
    return nullptr;
}*/

inline _vector2i _vector2i::operator* (const _vector2i& first) const
{
    _vector2i temp = *this;
    temp.setX(first.getX() * temp.getX());
    temp.setY(first.getY() * temp.getY());
    return temp;
}

_vector2i::_vector2i(int _x, int _y)
{
    x = _x;
    y = _y;
}

SDL_Rect _vector2i::rectFromVector()
{
    SDL_Rect tempRect;
    tempRect.x = x;
    tempRect.y = y;
    return tempRect;
}

void _vector2i::setY(int _y)
{
    y = _y;
}
void _vector2i::setX(int _x)
{
    x = _x;
}

int _vector2i::getX() const
{
    return x;
}
int _vector2i::getY() const
{
    return y;
}

_vector2i::~_vector2i()
{}
