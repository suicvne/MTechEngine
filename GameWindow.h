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

struct SDLInitArgs
{
    int x, y, w, h;
    const char *_windowTitle;
};

class GameWindow
{
public:
    GameWindow();
    GameWindow(const char *_windowTitle);
    GameWindow(SDLInitArgs initializerArgs);
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
    //std::string getResourcePath(const std::string &subDir = "");
    SDL_Color white =
    {
        255, 255, 255, 255
    };
private:
    SDLInitArgs initArgs;
    const char *winTitle;
    int quit;
    void draw();
    void update();
    void loadTextures();
    SDL_Window *gameWindow;
    SDL_Renderer *mainRenderer;
    SDL_Event *mainEventLoop;
    SpriteBatch *spriteBatch;
    ContentManager *contentManager;
    InputHandler *inputHandler;
    int width, height;
    Sprite *testSprite;
    bool __update;
};


#endif // GAMEWINDOW_H_INCLUDED
