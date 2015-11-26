#pragma once
#ifndef TESTSCREEN_H
#define TESTSCREEN_H
#include "Screen.h"
#include "Sprite.h"
#include "StandardColors.h"

class TestScreen : public Screen
{
    public:
        TestScreen(ContentManager &___cm);
        ~TestScreen();
        void draw(SpriteBatch *_sb);
        void update(InputHandler *_ih);
    protected:
    private:
        ContentManager *_cm;
        Sprite *testSprite;
        StandardColors clr;
};

#endif // TESTSCREEN_H
