#pragma once
#ifndef TESTSCREEN_H
#define TESTSCREEN_H
#include "Screen.h"
#include "Sprite.h"

class TestScreen : public Screen
{
    public:
        TestScreen(ContentManager *___cm);
        ~TestScreen();
        void draw(SpriteBatch *_sb);
        void update(InputHandler *_ih);
    protected:
    private:
        void doRealDraw(SpriteBatch *_sb);
        void doRealUpdate(InputHandler *_ih);
        ContentManager *_cm;
        Sprite *testSprite;
};

#endif // TESTSCREEN_H
