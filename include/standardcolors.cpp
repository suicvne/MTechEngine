/**
  About {{filename}}.h/{{filename}}.cpp
  By: Mike

*/
#include "StandardColors.h"

#ifndef __llvm__
SDL_Color StandardColors::white = SDL_Color{255, 255, 255, 255};
SDL_Color StandardColors::black = SDL_Color{0, 0, 0, 255};
SDL_Color StandardColors::strongRed = SDL_Color{255, 0, 0, 255};
SDL_Color StandardColors::strongGreen = SDL_Color{0, 255, 0, 255};
SDL_Color StandardColors::strongBlue = SDL_Color{0, 0, 255, 255};
#else
SDL_Color StandardColors::white;
SDL_Color StandardColors::black;
SDL_Color StandardColors::strongRed;
#endif

#ifdef __llvm__
void StandardColors::populateColors()
{
    StandardColors::white = SDL_Color();
    StandardColors::white.r = 255;
    StandardColors::white.g = StandardColors::white.b = StandardColors::white.a = StandardColors::white.r;

    StandardColors::black = SDL_Color();
    StandardColors::black.r = StandardColors::black.g = StandardColors::black.b = 0;
    StandardColors::black.a = 255;

    StandardColors::strongRed = SDL_Color();
    StandardColors::strongRed.r = 255;
    StandardColors::strongRed.a = StandardColors::strongRed.r;
    StandardColors::strongRed.g = StandardColors::strongRed.b = 0;
}

#endif
