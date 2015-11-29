#pragma once
#ifndef TILE_H
#define TILE_H
#include <SDL.h>
#include <iostream>
#include <string>
#include <vector>
#include "../SpriteBatch.h"
#include "ContentManager.h"
#include "_vector2i.h"

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
        _vector2i *getNonAnimatedArea();

        bool getAnimated();
        int getFrameCount();
        int getFrameUpdateInterval();
        int getCurrentFrame();
        std::vector<_vector2i> getAllFrames();

        std::string getBlockName();

        void setWorldPosition(int x, int y);
        void setWorldX(int __x);
        void setWorldY(int __y);
        void setBlockSize(int w, int h);
        void setSheetName(std::string _sheetname);
        void setNonAnimatedArea(_vector2i *_nanimarea);

        void setAnimated(bool __anim);
        void setFrameCount(int framec);
        void setFrameUpdateInterval(int __interval);
        void setCurrentFrame(int __curframe);
        void setAnimatedFrames(std::vector<_vector2i> __frames);

        void setBlockName(std::string __bn);

        SDL_Rect areaAsRect();
        SDL_Rect currentFrameAsRect();
    protected:
    private:
        int worldX, worldY; //position in the world, to be determined later
        int width, height;
        std::string sheetName; //name of the sheet in the content manager
        std::string blockName;
        _vector2i *area; //area on the sheet for non animated blocks

        bool animated; //whether or not the block is animated
        int frameCount; //amount of frames in the animation
        int frameUpdateInterval; //how many frames go by before it's updated? divide frame index by this
        int currentFrame; //not used yet
        //_vector2i **frames; //the actual frames
        std::vector<_vector2i> frames;
};

#endif // TILE_H
