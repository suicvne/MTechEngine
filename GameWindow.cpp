#include "GameWindow.h"

GameWindow::GameWindow()
{
    initArgs.x = -1;
    initArgs.y = -1;
    width = 800;
    height = 600;
    winTitle = "SDLEngine";
}

GameWindow::GameWindow(SDLInitArgs initializerArgs)
{
    initArgs = initializerArgs;
    width = initArgs.w;
    height = initArgs.h;
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

    //screenManager = new ScreenManager(contentManager);

    __update = true;

    targetTexture = SDL_CreateTexture(mainRenderer, NULL, SDL_TEXTUREACCESS_TARGET, initArgs.w, initArgs.h);
    spriteBatch->sbSetRenderTarget(targetTexture);
    while(quit == 0)
    {
        GameWindow::update();
        GameWindow::draw();
    }
}

void GameWindow::loadTextures()
{
    //if(contentManager == nullptr)
    contentManager = new ContentManager();

    std::cout << "addr_of mainRenderer (init): " << &mainRenderer << std::endl;

    SDL_Texture *txture = spriteBatch->loadTexture(getResourcePath("") + "rayquaza.png", &mainRenderer);

    contentManager->addTexture("rayquaza", txture);
}

GameWindow::~GameWindow()
{
    std::cout << "Destroying game objects" << std::endl;
    SDL_Quit();
    SDL_DestroyWindow(GameWindow::gameWindow);
    SDL_DestroyRenderer(GameWindow::mainRenderer);
    delete screenManager;
    delete mainEventLoop;
}

void GameWindow::draw()
{
    if(__update)
    {
        //spriteBatch->sbSetRenderTarget(targetTexture);
        //screenManager->draw(spriteBatch);
        //spriteBatch->sbSetRenderTarget(nullptr);

        //spriteBatch->sbBegin();
        //spriteBatch->sbDrawTextureScaled(targetTexture, 0, 0, width, height);
        //spriteBatch->sbEnd();
    }
}

void GameWindow::update()
{
    if(__update)
    {
        //SDL_PollEvent(mainEventLoop);
        inputHandler->update();
        if(inputHandler->getEvent()->type == SDL_KEYDOWN)
        {
            if(inputHandler->getEvent()->key.keysym.sym == SDLK_ESCAPE)
                quit = 1;
        }
        if(inputHandler->getEvent()->type == SDL_QUIT)
        {
            quit = 1;
        }
        if(inputHandler->getEvent()->type == SDL_WINDOWEVENT)
        {
                switch(inputHandler->getEvent()->window.event)
                {
                case SDL_WINDOWEVENT_RESIZED:
                    width = inputHandler->getEvent()->window.data1;
                    height = inputHandler->getEvent()->window.data2;
                    break;
                case SDL_WINDOWEVENT_MINIMIZED:
                    __update = false;
                    std::cout << "Update stopped" << std::endl;
                    break;
                }
        }
    }
    else
    {
        inputHandler->update();
        if(inputHandler->getEvent()->type == SDL_WINDOWEVENT)
        {
            if(inputHandler->getEvent()->window.event == SDL_WINDOWEVENT_RESTORED)
            {
                __update = true;
                std::cout << "Update began" << std::endl;
            }
        }

    }
}
