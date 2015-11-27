#pragma once

#ifndef SPRITEBATCH_H
#define SPRITEBATCH_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <algorithm>

class SpriteBatch
{
    public:
        SpriteBatch(SDL_Renderer *renderer);
        virtual ~SpriteBatch();
        void sbBegin();
        void sbEnd();
        void sbSetRenderTarget(SDL_Texture *target);
        void sbDrawTexture(SDL_Texture *tex, int x, int y);
        void sbDrawTextureScaled(SDL_Texture *tex, int x, int y, float scale);
        void sbDrawTextureScaled(SDL_Texture *tex, int x, int y, int w, int h);
        void sbDrawFont(std::string msg, int x, int y, SDL_Color color, float scale, bool _upper);
        SDL_Texture* loadTexture(const std::string &file, SDL_Renderer **ren);
        bool isDrawing()
        {
            return drawingInProgress;
        };
    protected:
    private:
        SDL_Texture *__target;
        SDL_Texture *drawFontToTexture(std::string msg, SDL_Color color);
        bool drawingInProgress = false;
        SDL_Renderer *__renderer;
        TTF_Font *mainGameFont;

};

#endif // SPRITEBATCH_H
