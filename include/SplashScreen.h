#pragma once
#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H

#include "Screen.h"
#include "ContentManager.h"
#include "SpriteBatch.h"
#include "InputHandler.h"
#include "global_vars.h"
#include <SDL.h>

class SplashScreen : public Screen
{
    public:
        SplashScreen();
        ~SplashScreen();
        void draw(SpriteBatch* _sb, ContentManager* cm);
        void update(SDL_Event const &_ih);
        void getCenter(int *_x, int *_y, SDL_Texture *textureToQuery);
        bool goNext()
        {
            return next;
        };
    protected:
    private:
        int localCounter = 0;
        const int TimeTillNext = 2000; //ms
        bool next = false;
};

#endif // SPLASHSCREEN_H
