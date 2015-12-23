#ifndef LEVELBACKGROUND_H
#define LEVELBACKGROUND_H

#include <SDL.h>
#include <string>
#include "_vector2i.h"

struct SpriteBatch;

class LevelBackground
{
    public:
        LevelBackground();
        ~LevelBackground();
        void draw(SpriteBatch *_sb);

        //there comes a certain part in your life where you say fuck it
        //and you make all your properties public
        int width, height; //the w/h of the original background area
        int id, framecount, frameupdate; //int id, amount of frames, the frame update interval
        bool topBottom; //if it's a top/bottom background
        bool animated; //if it's animated
        SDL_Texture topArea; //eh
        SDL_Texture bottomArea; //eh
        std::string sheetname, bgname; //the name of the sheet it comes from and the friendly name of the background
        _vector2i *singleFrame; //one single lonely frame

        //other crap
        int xoffset, yoffset;
    protected:
    private:
};

#endif // LEVELBACKGROUND_H
