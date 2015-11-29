#ifndef _VECTOR2I_H
#define _VECTOR2I_H

#include <iostream>
#include <SDL.h>

class _vector2i
{
    public:
        _vector2i();
        _vector2i(int _x, int _y);
        ~_vector2i();
        int getX();
        int getY();
        void setX(int _x);
        void setY(int _y);
        SDL_Rect rectFromVector();
    protected:
    private:
        int x, y;
};

#endif // _VECTOR2I_H
