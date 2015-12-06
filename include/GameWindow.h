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

struct SDLInitArgs
{
    int x, y, w, h;
    const char *_windowTitle;
    bool vsync;
};

class GameWindow
{
public:
    GameWindow();
    GameWindow(SDLInitArgs initializerArgs);
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
    static std::string getResourcePath(const std::string &subDir)
    {
#ifdef _WIN32
	const char PATH_SEP = '\\';
#else
	const char PATH_SEP = '/';
#endif
	//This will hold the base resource path: Lessons/res/
	//We give it static lifetime so that we'll only need to call
	//SDL_GetBasePath once to get the executable path
	static std::string baseRes;
	if (baseRes.empty()){
		//SDL_GetBasePath will return NULL if something went wrong in retrieving the path
		char *basePath = SDL_GetBasePath();
		if (basePath){
			baseRes = basePath;
			SDL_free(basePath);
		}
		else {
			std::cerr << "Error getting resource path: " << SDL_GetError() << std::endl;
			return "";
		}
		//We replace the last bin/ with res/ to get the the resource path
		size_t pos = baseRes.rfind("bin");
		baseRes = baseRes.substr(0, pos) + "res" + PATH_SEP;
	}
	//If we want a specific subdirectory path in the resource directory
	//append it to the base path. This would be something like Lessons/res/Lesson0
	return subDir.empty() ? baseRes : baseRes + subDir + PATH_SEP;
    };
private:
    SDLInitArgs initArgs;
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
    ContentManager contentManager;
    InputHandler *inputHandler;
    ScreenManager *screenManager;
    //SoundMixer *mainSoundMixer;
    Camera2d MainGameCamera;
    int width, height;
    int lastTimeCheck, updateIntervalMs;
    bool __update;
    int __fullscreen = 0;
    float scaleGameH = 1;
    float scaleGameW = 1;
};


#endif // GAMEWINDOW_H_INCLUDED
