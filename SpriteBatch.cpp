#include "SpriteBatch.h"

SpriteBatch::SpriteBatch(SDL_Renderer *renderer)
{
    __renderer = renderer;
}

SpriteBatch::~SpriteBatch()
{}

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
    if(drawingInProgress)
        throw "sbBegin already called!";
    SDL_RenderClear(__renderer);
    drawingInProgress = true;
}

void SpriteBatch::sbDrawTexture(SDL_Texture *tex, int x, int y)
{
    if(!drawingInProgress)
        throw "sbBegin must be called.";
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;

    SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
    SDL_RenderCopy(__renderer, tex, NULL, &dst);
}

void SpriteBatch::sbEnd()
{
    if(!drawingInProgress)
        throw "sbBegin never called!";
    SDL_RenderPresent(__renderer);
    drawingInProgress = false;
}
