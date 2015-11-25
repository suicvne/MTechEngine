#pragma once
#ifndef TESTSCREEN_H
#define TESTSCREEN_H

#include "Screen.h"


class TestScreen : public Screen
{
    public:
        TestScreen();
        virtual ~TestScreen();
        void draw(SpriteBatch *_sb);
        void update(InputHandler *_ih);
    protected:
    private:
        void doRealDraw(SpriteBatch *_sb);
        void doRealUpdate(InputHandler *_ih);
};

#endif // TESTSCREEN_H
