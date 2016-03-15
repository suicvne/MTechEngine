#ifndef SPRITEBATCH_H
#define SPRITEBATCH_H
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <algorithm>

class Camera2d;

class SpriteBatch
{
    public:
        SpriteBatch(SDL_Renderer *renderer);
        virtual ~SpriteBatch();
        void sbBegin();
        void sbEnd();
        void sbSetRenderTarget(SDL_Texture *target);
        void sbSetMainGameCamera(Camera2d *cam);
        void sbDrawBlankTexture(int x, int y);
        void sbDrawBlankTextureConstant(int x, int y);
        void sbDrawTexture(SDL_Texture *tex, int x, int y);
        void sbDrawTextureConstant(SDL_Texture *tex, int x, int y);
        void sbDrawTextureArea(SDL_Texture *tex, int x, int y, SDL_Rect area);
        void sbDrawTextureAreaScaled(SDL_Texture *tex, int x, int y, SDL_Rect area, float scale);
        void sbDrawTextureAreaScaledConstant(SDL_Texture *tex, int x, int y, SDL_Rect area, float scale);
        void sbDrawTextureScaled(SDL_Texture *tex, int x, int y, float scale);
        void sbDrawTextureScaled(SDL_Texture *tex, int x, int y, int w, int h);
        void sbDrawTextureScaledConstant(SDL_Texture *tex, int x, int y, float scale);
        void sbDrawTextureScaledConstant(SDL_Texture *tex, int x, int y, int w, int h);
        void sbMeasureString(int *w, int *h, std::string msg, float scale, bool upper);
        void sbFillScreen(SDL_Color *color);
        void sbFillRect(SDL_Color *color, SDL_Rect *rect);
        void sbDrawFont(std::string msg, int x, int y, SDL_Color& color, float scale, bool _upper);
        void sbDrawFont(std::string *msg, int x, int y, SDL_Color& color, float scale, bool _upper);
        SDL_Texture* loadTexture(const std::string &file, SDL_Renderer **ren);
        SDL_Texture* loadTexture(const std::string &file);
        bool isDrawing()
        {
            return drawingInProgress;
        };
    protected:
    private:
        SDL_Texture *__target;
        SDL_Texture* blankTexture; //used for things u know
        SDL_Texture *drawFontToTexture(std::string msg, SDL_Color color);
        SDL_Texture *drawFontToTexture(std::string *msg, SDL_Color color);
        bool drawingInProgress = false;
        SDL_Renderer *__renderer;
        TTF_Font *mainGameFont;
        Camera2d *mainGameCamera;
};

#endif // SPRITEBATCH_H
