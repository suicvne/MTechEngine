#ifndef MATHSSTUFF_H
#define MATHSSTUFF_H

#include <SDL.h>
#include "global_vars.h"
#include <stdlib.h>
#include <cmath>

class MathsStuff
{
    public:
        static int math_clamp(int compare, int _min, int _max)
        {
            return ((compare > _max) ? _max : (compare < _min) ? _min : ((compare < _max && compare > _min) ? compare : compare));

        //    This is equivalent code. I was just showing off to my friends that I can one line it

        //    if(compare > _max)
        //        return _max;
        //    if(compare < _min)
        //        return _min;
        //    if(compare < _max && compare > _min)
        //    {
        //        return compare;
        //    }
        }
        static bool sdl_rect_intersects(SDL_Rect *rect1, SDL_Rect *rect2)
        {
            SDL_Rect res;
            return (SDL_IntersectRect(rect1, rect2, &res) == SDL_TRUE ? true : false);
        }
        static int ceiling(float const input)
        {
            return (int)ceil(input);
        }

    private:
        MathsStuff();
};

#endif // MATHSSTUFF_H
