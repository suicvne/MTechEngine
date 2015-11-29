#pragma once
#ifndef SCREENMANAGER_H
#define SCREENMANAGER_H

#include "TestScreen.h"

enum ScreensEnum
{
    TESTSCREEN = 0
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
    protected:
    private:
        TestScreen *testScreen;
        ScreensEnum CurrentScreen = TESTSCREEN;
};

#endif // SCREENMANAGER_H
