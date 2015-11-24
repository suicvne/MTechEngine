#include "GameWindow.h"

GameWindow::GameWindow()
{
    winTitle = "SDLEngine";
}

GameWindow::GameWindow(const char* _windowTitle)
{
    winTitle = _windowTitle;
}

GameWindow::GameWindow(SDLInitArgs initializerArgs)
{
    initArgs = initializerArgs;

#ifdef __SDLENGINE_DEBUG
    using namespace std;
    cout << "Init Args" << endl << "x: " << initArgs.x << endl;
    cout << "y: " << initArgs.y << endl;
    cout << "w: " << initArgs.w << endl;
    cout << "h: " << initArgs.h << endl;
    cout << "_windowTitle: '" << initArgs._windowTitle << "'" << endl;
#endif // __SDLENGINE_DEBUG

}

void GameWindow::initializeSDL()
{
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return;
    }

    GameWindow::gameWindow = SDL_CreateWindow(initArgs._windowTitle, initArgs.x, initArgs.y, initArgs.w, initArgs.h, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
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

    spriteBatch = new SpriteBatch(mainRenderer);

    while(quit == 0 && mainEventLoop->type != SDL_QUIT)
    {
        GameWindow::update();
        GameWindow::draw();
    }
}

GameWindow::~GameWindow()
{
    std::cout << "Destroying game objects" << std::endl;
    SDL_Quit();
    SDL_DestroyWindow(GameWindow::gameWindow);
    SDL_DestroyRenderer(GameWindow::mainRenderer);
    //TODO: change this to proper SDL destroy
    delete mainEventLoop;
}

void GameWindow::draw()
{
    spriteBatch->sbBegin();

    spriteBatch->sbEnd();
}

void GameWindow::update()
{
    SDL_PollEvent(mainEventLoop);
}
