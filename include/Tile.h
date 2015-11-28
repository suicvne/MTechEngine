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
        Tile();
        ~Tile();
        int getWorldX();
        int getWorldY();
        int getWidth();
        int getHeight();
        std::string getSheetName();
        SDL_Rect getNonAnimatedArea();

        bool getAnimated();
        int getFrameCount();
        int getFrameUpdateInterval();
        int getCurrentFrame();
        SDL_Rect **getAllFrames();

        void setWorldPosition(int x, int y);
        void setBlockSize(int w, int h);
        void setSheetName(std::string _sheetname);
        void setNonAnimatedArea(SDL_Rect _nanimarea);

        void setAnimated(bool __anim);
        void setFrameCount(int framec);
        void setFrameUpdateInterval(int __interval);
        void setCurrentFrame(int __curframe);
        void setAnimatedFrames(SDL_Rect **__frames);
    protected:
    private:
        int worldX, worldY; //position in the world, to be determined later
        int width, height;
        std::string sheetName; //name of the sheet in the content manager
        SDL_Rect area; //area on the sheet for non animated blocks

        bool animated; //whether or not the block is animated
        int frameCount; //amount of frames in the animation
        int frameUpdateInterval; //how many frames go by before it's updated? divide frame index by this
        int currentFrame; //not used yet
        SDL_Rect **frames; //the actual frames
};

#endif // TILE_H
