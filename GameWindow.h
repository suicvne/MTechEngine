#ifndef GAMEWINDOW_H_INCLUDED
#define GAMEWINDOW_H_INCLUDED

#include <iostream>
#include <SDL.h>

struct __SDLInitArgs
{
    int x, y, w, h;
    const char *_windowTitle;
};

class GameWindow
{
public:
    GameWindow();
    GameWindow(const char *_windowTitle);
    //GameWindow(__SDLInitArgs *initializerArgs);
    ~GameWindow();
    void draw();
    void update();
private:
    const char *winTitle;
    int quit;
    void initializeSDL();
    SDL_Window *gameWindow;
    SDL_Renderer *mainRenderer;
    SDL_Event *mainEventLoop;
};


#endif // GAMEWINDOW_H_INCLUDED
