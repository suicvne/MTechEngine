#pragma once
#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H

#include "Screen.h"
#include "ContentManager.h"
#include "SpriteBatch.h"
#include "InputHandler.h"
#include "global_vars.h"

class SplashScreen : public Screen
{
    public:
        SplashScreen(ContentManager *___cm);
        ~SplashScreen();
        void draw(SpriteBatch *_sb);
        void update(InputHandler *_ih);
        void getCenter(int *_x, int *_y, SDL_Texture *textureToQuery);
        bool goNext()
        {
            return next;
        };
    protected:
    private:
        ContentManager *_cm;
        int localCounter = 0;
        bool next = false;
};

#endif // SPLASHSCREEN_H
