#pragma once
#ifndef TITLESCREEN_H
#define TITLESCREEN_H
#include "Screen.h"
#include "ContentManager.h"
#include "SpriteBatch.h"
#include "InputHandler.h"
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <vector>
#include "Menu.h"

struct MessageBox;

class TitleScreen : public Screen
{
    public:
        TitleScreen(ContentManager *___cm);
        ~TitleScreen();
        void draw(SpriteBatch *_sb);
        void update(InputHandler *_ih);
        void processInput(InputHandler *_ih);
    protected:
    private:
        void drawTitleCopyrightEtc(SpriteBatch *_sb);
        void drawOptions(SpriteBatch *_sb);
        ContentManager *_cm;
        std::vector<Menu*> menuOptions;
        int totalOptions, currentSelection;
        bool upPressed, downPressed, showTestMessage;
        MessageBox *testMessage;
};

#endif // TITLESCREEN_H
