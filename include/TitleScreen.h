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
#include <SDL.h>
struct MessageBox;

class TitleScreen : public Screen
{
    public:
        TitleScreen();
        ~TitleScreen();
        void draw(SpriteBatch* _sb, ContentManager* cm);
        void update(SDL_Event const &_ih);
        void processInput(SDL_Event const &_ih);
    protected:
    private:
        void drawTitleCopyrightEtc(SpriteBatch* _sb, ContentManager* cm);
        void drawOptions(SpriteBatch* _sb, ContentManager* cm);
        std::vector<Menu*> menuOptions;
        int totalOptions, currentSelection;
        bool upPressed, downPressed, showTestMessage;
        MessageBox* testMessage;
};

#endif // TITLESCREEN_H
