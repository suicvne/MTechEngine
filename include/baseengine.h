/**
  About basengine.h/basengine.cpp
  By: Mike

  The base engine runner and what not that sets up and stuff.
*/

#ifndef BASEENGINE_H
#define BASEENGINE_H

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "mtechapplication.h"
#include "src/configfile.h"

#include "SpriteBatch.h"
#include "InputHandler.h"
#include "SoundMixer.h"
#include "Camera2d.h"
#include "ContentManager.h"


class BaseEngine
{
public:
    BaseEngine(MTechApplication *application);
    ~BaseEngine();
    int runApplication();
private:
    bool InitializeSDL(ConfigFile &configFile);
    std::string getResourcePath(const std::string &subDir);
    int gameLoop();
    void importantEvents();
    void importantUpdate();
    void importantDraw();
    void toggleFullscreen();
    void windowResize();
    BaseEngine();
    MTechApplication *pApplication;
    //important
    SDL_Window* mainGameWindow;
    SDL_Renderer* sdlRenderer;
    SDL_Event* mainEventLoop;
    SDL_Texture* targetTexture;
    //
    //MTechTypes
    SpriteBatch* spriteBatch;
    InputHandler* inputHandler;
    SoundMixer* mainSoundMixer;
    Camera2d* mainCamera;
    ContentManager* contentManager;
    //
    //fields
    bool __vsyncEnabled, ____DO_QUIT, ____UPDATE;
    int __fullscreen = 0;
    int updateIntervalMs, lastTimeCheck;
    int width, height;
    float scaleGameW = 1, scaleGameH = 1;
    //
};

#endif // BASEENGINE_H
