#pragma once
#ifndef SCREENMANAGER_H
#define SCREENMANAGER_H

#include "TestScreen.h"
#include "SplashScreen.h"
#include "TitleScreen.h"
#include "TestLevelScreen.h"

class ScreenManager
{
    public:
        enum ScreensEnum
        {
            TESTSCREEN = 2, SPLASHSCREEN = 0, TITLESCREEN = 1, TESTLEVEL = 3
        };
        ScreenManager();
        virtual ~ScreenManager();
        void update(InputHandler* _ih);
        void draw(SpriteBatch* sb, ContentManager* cm);
        void pushScreen(ScreensEnum scr);
        TestScreen* getTestScreen();
        SplashScreen* getSplashScreen();
        TitleScreen* getTitleScreen();
        ScreensEnum getCurrentScreen()
        {
            return CurrentScreen;
        };
    protected:
    private:
        //TestScreen* testScreen; old lua test screen
        SplashScreen* splash;
        TitleScreen* title;
        TestLevelScreen* testLvlScreen;
        ScreensEnum CurrentScreen = TESTSCREEN;
};

#endif // SCREENMANAGER_H
