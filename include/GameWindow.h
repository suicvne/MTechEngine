/**
  About GameWindow.h/GameWindow.cpp
  By: Mike

  Where everything begins: this is the minimum you need to get a basic example going.
  Initiate a pointer and call GameWindow->initializeSDL(); to get going. Everything else is done
  from there!

  What to modify:
    * loadTextures(); - This handles loading all of the textures that the game needs
  */

#pragma once

#ifndef GAMEWINDOW_H_INCLUDED
#define GAMEWINDOW_H_INCLUDED

#include <iostream>
#include <SDL.h>
#include "SpriteBatch.h"
#include "ContentManager.h"
#include "InputHandler.h"
#include "Sprite.h"
#include "float.h"
#include "StandardColors.h"
#include "ScreenManager.h"
#include "LuaBlockConfigLoader.h"
#include "global_vars.h"
#include "SoundMixer.h"

class GameWindow
{
public:
    GameWindow();
    ~GameWindow();
    void initializeSDL();
    int getWindowWidth()
    {
        return width;
    };
    int getWindowHeight()
    {
        return height;
    };
private:
    const char *winTitle;
    int quit;
    void draw();
    void update();
    void importantUpdates();
    void loadTextures();
    void initBlocks();
    void toggleFullscreen();
    void windowResize();
    SDL_Texture *targetTexture;
    SDL_Window *gameWindow;
    SDL_Renderer *mainRenderer;
    SDL_Event *mainEventLoop;
    SpriteBatch *spriteBatch;
    InputHandler *inputHandler;
    int width, height;
    int lastTimeCheck, updateIntervalMs;
    bool __update;
    int __fullscreen = 0;
    float scaleGameH = 1;
    float scaleGameW = 1;
};


#endif // GAMEWINDOW_H_INCLUDED
