#include "GameWindow.h"

GameWindow::GameWindow()
{
    //__SDLInitArgs *_args = new __SDLInitArgs;
    //_args->x = 100;
    //_args->y = 100;
    //_args->w = 640;
    //_args->h = 480;
    //_args->_windowTitle = "SDLEngine";

    //initArgs = _args;

    //initArgs.x = 100;
    //initArgs.y = 100;
    //initArgs.w = 640;
    //initArgs.h = 480;
    //initArgs._windowTitle = "SDLEngine";
    winTitle = "SDLEngine";
    initializeSDL();
}

GameWindow::GameWindow(const char* _windowTitle)
{
    winTitle = _windowTitle;
    initializeSDL();
}


void GameWindow::initializeSDL()
{
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return;
    }

    GameWindow::gameWindow = SDL_CreateWindow(winTitle, 100, 100, 640, 480, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
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
    GameWindow::mainEventLoop = new SDL_Event();
    quit = 0;
}

GameWindow::~GameWindow()
{
    SDL_Quit();
    SDL_DestroyWindow(GameWindow::gameWindow);
    SDL_DestroyRenderer(GameWindow::mainRenderer);
    //TODO: change this to proper SDL destroy
    delete mainEventLoop;
}

void GameWindow::draw()
{
    while(quit == 0 && mainEventLoop->type != SDL_QUIT)
    {
        SDL_PollEvent(mainEventLoop);

        SDL_RenderClear(GameWindow::mainRenderer);

        //do other drawing in here

        SDL_RenderPresent(GameWindow::mainRenderer);
    }
}

void GameWindow::update()
{}
