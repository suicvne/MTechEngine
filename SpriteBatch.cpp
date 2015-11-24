#include "SpriteBatch.h"

SpriteBatch::SpriteBatch(SDL_Renderer *renderer)
{
    __renderer = renderer;
}

SpriteBatch::~SpriteBatch()
{/*Don't destroy the renderer just in case we need it later. GameWindow takes care of that anyway*/}

SDL_Texture* SpriteBatch::loadTexture(const std::string &file, SDL_Renderer *ren)
{
    SDL_Texture *texture = NULL;
    texture = IMG_LoadTexture(ren, file.c_str());

    if(texture == nullptr)
    {
        std::cout << "Error loading texture: " << SDL_GetError() << std::endl;
    }

    return texture;
}

void SpriteBatch::sbBegin()
{
    SDL_RenderClear(__renderer);
}

void SpriteBatch::sbDrawTexture(SDL_Texture *tex, int x, int y)
{
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;

    SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
    SDL_RenderCopy(__renderer, tex, NULL, &dst);
}

void SpriteBatch::sbEnd()
{
    SDL_RenderPresent(__renderer);
}
