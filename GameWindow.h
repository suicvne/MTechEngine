#ifndef GAMEWINDOW_H_INCLUDED
#define GAMEWINDOW_H_INCLUDED

#include <iostream>
#include <SDL.h>

class GameWindow
{
public:
    GameWindow();
    GameWindow(const char *windowTitle);
    ~GameWindow();
    void draw();
    void update();
private:
    int quit;
    SDL_Window *gameWindow;
    SDL_Renderer *mainRenderer;
    SDL_Event mainEventLoop;
};


#endif // GAMEWINDOW_H_INCLUDED
