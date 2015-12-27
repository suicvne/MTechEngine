#ifndef _COLOR_H
#define _COLOR_H

#include <SDL.h>

class _color
{
    public:
        _color();
        _color(int r, int g, int b);
        _color(int r, int g, int b, int a);
        virtual ~_color();
        SDL_Color getAsSDLColor();
        int getR();
        int getG();
        int getB();
        int getA();
        void setR(int r);
        void setG(int g);
        void setB(int b);
        void setA(int a);
    protected:
    private:
        int _r, _g, _b, _a;
};

#endif // _COLOR_H
