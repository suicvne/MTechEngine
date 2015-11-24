#ifndef SPRITEBATCH_H
#define SPRITEBATCH_H

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

class SpriteBatch
{
    public:
        SpriteBatch(SDL_Renderer *renderer);
        virtual ~SpriteBatch();
        void sbBegin();
        void sbEnd();
        SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren);
        void sbDrawTexture(SDL_Texture *tex, int x, int y);
    protected:
    private:
        SDL_Renderer *__renderer;

};

#endif // SPRITEBATCH_H
