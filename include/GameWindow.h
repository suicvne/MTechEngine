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

/*ruct SDLInitArgs
{
    int x, y, w, h;
    const char *_windowTitle;
    bool vsync;
};*/

class GameWindow
{
public:
    GameWindow();
    ~GameWindow();
    void initializeSDL();
    StandardColors standardColors;
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
    //ScreenManager *screenManager;
    //SoundMixer *mainSoundMixer;
    //Camera2d MainGameCamera;
    int width, height;
    int lastTimeCheck, updateIntervalMs;
    bool __update;
    int __fullscreen = 0;
    float scaleGameH = 1;
    float scaleGameW = 1;
};


#endif // GAMEWINDOW_H_INCLUDED
