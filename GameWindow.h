#ifndef GAMEWINDOW_H_INCLUDED
#define GAMEWINDOW_H_INCLUDED

#include <iostream>
#include <SDL.h>
#include "SpriteBatch.h"

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
    std::string getResourcePath(const std::string &subDir = "");
private:
    SDLInitArgs initArgs;
    const char *winTitle;
    int quit;
    void draw();
    void update();
    SDL_Window *gameWindow;
    SDL_Renderer *mainRenderer;
    SDL_Event *mainEventLoop;
    SpriteBatch *spriteBatch;
};


#endif // GAMEWINDOW_H_INCLUDED
