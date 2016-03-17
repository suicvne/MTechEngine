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
    MTechApplication *pApplication = 0;
    //important
    SDL_Window* mainGameWindow = 0;
    SDL_Renderer* sdlRenderer = 0;
    SDL_Texture* targetTexture = 0;
    SDL_Event mainEventLoop;
    //
    //MTechTypes
    SpriteBatch* spriteBatch = 0;
    //InputHandler* inputHandler;
    //SDL_Event *mainEvent;
    Camera2d* mainCamera = 0;
    ContentManager* contentManager = 0;
    //
    //fields
    bool __vsyncEnabled;
    int __fullscreen = 0;
    int updateIntervalMs, lastTimeCheck;
    int width, height;
    float scaleGameW = 1, scaleGameH = 1;
    std::string windowTitle;
    //
};

#endif // BASEENGINE_H
