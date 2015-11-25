#include "GameWindow.h"
#include <Res.h>

GameWindow::GameWindow()
{
    initArgs.x = -1;
    initArgs.y = -1;
    winTitle = "SDLEngine";
}

GameWindow::GameWindow(const char* _windowTitle)
{
    winTitle = _windowTitle;
}

GameWindow::GameWindow(SDLInitArgs initializerArgs)
{
    initArgs = initializerArgs;
}

void GameWindow::initializeSDL()
{
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return;
    }

    GameWindow::gameWindow = SDL_CreateWindow(initArgs._windowTitle,
        initArgs.x == -1 ? SDL_WINDOWPOS_UNDEFINED : initArgs.y,
        initArgs.y == -1 ? SDL_WINDOWPOS_UNDEFINED : initArgs.y,
        initArgs.w,
        initArgs.h,
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

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

    inputHandler = new InputHandler();

    loadTextures();

    testSprite = new Sprite(contentManager->getTexture("rayquaza"));

    while(quit == 0)
    {
        GameWindow::update();
        GameWindow::draw();
    }
}

void GameWindow::loadTextures()
{
    if(contentManager == nullptr)
        contentManager = new ContentManager();

    contentManager->addTexture("rayquaza", spriteBatch->loadTexture(getResourcePath("") + "rayquaza.png", mainRenderer));
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
    spriteBatch->sbDrawTexture(contentManager->getTexture("rayquaza"), 100, 100);
    spriteBatch->sbEnd();
}

void GameWindow::update()
{
    //SDL_PollEvent(mainEventLoop);
    inputHandler->update();

    if(inputHandler->InputState.keysDown == SDLK_ESCAPE)
        quit = 1;
}
