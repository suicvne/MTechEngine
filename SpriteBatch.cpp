#include "SpriteBatch.h"

SpriteBatch::SpriteBatch(SDL_Renderer *renderer)
{
    __renderer = renderer;
}

SpriteBatch::~SpriteBatch()
{/*Don't destroy the renderer just in case we need it later. GameWindow takes care of that anyway*/}

void SpriteBatch::sbBegin()
{
    SDL_RenderClear(__renderer);
}

//TODO: Draw?

void SpriteBatch::sbEnd()
{
    SDL_RenderPresent(__renderer);
}
