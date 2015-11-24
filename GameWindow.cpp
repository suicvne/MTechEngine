#include "GameWindow.h"

GameWindow::GameWindow()
{
    //Try initializing SDL
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return;
    }

    GameWindow::gameWindow = SDL_CreateWindow("Game", 20, 20, 640, 480, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if(GameWindow::gameWindow == NULL)
    {
        std::cout << "SDL_CreateWindow error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return;
    }

    GameWindow::mainRenderer = SDL_CreateRenderer(GameWindow::gameWindow, -1, SDL_RENDERER_ACCELERATED);
    if(GameWindow::mainRenderer == NULL)
    {
        SDL_DestroyWindow(GameWindow::gameWindow);
        std::cout << "SDL_CreateRenderer error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return;
    }

    quit = 0;
}

GameWindow::GameWindow(const char *windowTitle)
{
    //Try initializing SDL
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return;
    }

    GameWindow::gameWindow = SDL_CreateWindow(windowTitle, 20, 20, 640, 480, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if(GameWindow::gameWindow == NULL)
    {
        std::cout << "SDL_CreateWindow error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return;
    }

    GameWindow::mainRenderer = SDL_CreateRenderer(GameWindow::gameWindow, -1, SDL_RENDERER_ACCELERATED);
    if(GameWindow::mainRenderer == NULL)
    {
        SDL_DestroyWindow(GameWindow::gameWindow);
        std::cout << "SDL_CreateRenderer error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return;
    }

    quit = 0;
}

GameWindow::~GameWindow()
{
    SDL_Quit();
    SDL_DestroyWindow(GameWindow::gameWindow);
    SDL_DestroyRenderer(GameWindow::mainRenderer);
}

void GameWindow::draw()
{
    while(quit == 0)
    {
        SDL_RenderClear(GameWindow::mainRenderer);

        //do other drawing in here

        SDL_RenderPresent(GameWindow::mainRenderer);
    }
}

void GameWindow::update()
{}
