#ifndef SPRITEBATCH_H
#define SPRITEBATCH_H

#include <SDL.h>

class SpriteBatch
{
    public:
        SpriteBatch(SDL_Renderer *renderer);
        virtual ~SpriteBatch();
        void sbBegin();
        void sbEnd();
    protected:
    private:
        SDL_Renderer *__renderer;

};

#endif // SPRITEBATCH_H
