#pragma once
#ifndef SCREENMANAGER_H
#define SCREENMANAGER_H

#include "TestScreen.h"
#include "SplashScreen.h"

enum ScreensEnum
{
    TESTSCREEN = -1, SPLASHSCREEN = 0
};

class ScreenManager
{
    public:
        ScreenManager(ContentManager &__cm);
        ~ScreenManager();
        void update(InputHandler *_ih);
        void draw(SpriteBatch *_sb);
        void pushScreen(ScreensEnum scr);
        TestScreen *getTestScreen();
        SplashScreen *getSplashScreen();
        ScreensEnum getCurrentScreen()
        {
            return CurrentScreen;
        };
    protected:
    private:
        TestScreen *testScreen;
        SplashScreen *splash;
        ScreensEnum CurrentScreen = TESTSCREEN;
};

#endif // SCREENMANAGER_H
