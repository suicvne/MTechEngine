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

    GameWindow::mainRenderer = SDL_CreateRenderer(GameWindow::gameWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
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

    initBlocks();
    std::cin.get();

    __update = true;

    targetTexture = SDL_CreateTexture(mainRenderer, 0, SDL_TEXTUREACCESS_TARGET, initArgs.w, initArgs.h);
    spriteBatch->sbSetRenderTarget(targetTexture);

    lastTimeCheck = SDL_GetTicks();

    while(quit == 0)
    {
        GameWindow::update();
        GameWindow::draw();
    }
}

void GameWindow::loadTextures()
{
    //if(contentManager == nullptr)
    SDL_Texture *txture = spriteBatch->loadTexture(getResourcePath("") + "rayquaza.png", &mainRenderer);
    //std::cout << txture << std::endl;
    contentManager.addTexture("r", txture);
    contentManager.addTexture("test_sheet", spriteBatch->loadTexture(getResourcePath("") + "temp_tileset.png", &mainRenderer));
    delete txture;
    screenManager = new ScreenManager(contentManager);
}

void GameWindow::initBlocks()
{
    LuaBlockConfigLoader *lbcl = new LuaBlockConfigLoader();

    lbcl->loadBlocks();

    delete lbcl;
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
        spriteBatch->sbSetRenderTarget(targetTexture);
        screenManager->draw(spriteBatch);
        spriteBatch->sbSetRenderTarget(nullptr);

        spriteBatch->sbBegin();
        spriteBatch->sbDrawTextureScaled(targetTexture, 0, 0, width, height);
        spriteBatch->sbEnd();
    }
}

void GameWindow::update()
{
    if(__update)
    {
        if(lastTimeCheck + updateIntervalMs < SDL_GetTicks())
        {
            screenManager->update(inputHandler);

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

            lastTimeCheck = SDL_GetTicks();
        }
        //SDL_PollEvent(mainEventLoop);
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
