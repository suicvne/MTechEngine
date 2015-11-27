#pragma once
#ifndef TILE_H
#define TILE_H
#include <SDL.h>
#include <iostream>
#include <string>
#include "../SpriteBatch.h"
#include "ContentManager.h"

class Tile
{
    public:
        Tile(std::string _sheetname);
        Tile(std::string _sheetname, SDL_Rect _area);
        Tile(std::string _sheetname, bool animated, int _framec, SDL_Rect *_frames[]);
        //Tile(bool animated, int _frames);
        ~Tile();
        void draw();
        void update();

        void setPosition(int _x, int _y);
        void setAnimated(bool _anim){animated = _anim;};
        void setFrameCount(int frmC){frameCount = frmC;};
        void setFrames(SDL_Rect **__frames){frames = __frames;};
        void setUpdateInterval(int frmUI){frameUpdateInterval = frmUI;};
        int getX();
        int getY();
        int getWidth();
        int getHeight();
        bool getAnimated(){return animated;};
    protected:
    private:
        int x, y;
        int width, height;
        std::string sheetName;
        SDL_Rect area;
        bool animated;
        int frameCount, frameUpdateInterval;
        SDL_Rect **frames;
};

#endif // TILE_H
