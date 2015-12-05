#pragma once

#ifndef SPRITE_H
#define SPRITE_H

#include "InputHandler.h"
#include "SpriteBatch.h"
#include <SDL.h>

class Sprite
{
    public:
        Sprite(SDL_Texture *tex);
        Sprite(SDL_Texture &tex);
        virtual ~Sprite();
        void draw(SpriteBatch *_sb);
        void update(InputHandler *_ih);
    protected:
    private:
        float x, y;
        SDL_Texture *texture;
};

#endif // SPRITE_H
