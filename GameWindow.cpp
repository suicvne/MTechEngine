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

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");

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

    #ifdef _WIN32
    GameWindow::mainRenderer = SDL_CreateRenderer(GameWindow::gameWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    std::cout << "Enabling vsync for Windows" << std::endl;
    #else
    GameWindow::mainRenderer = SDL_CreateRenderer(GameWindow::gameWindow, -1,
                                                  SDL_RENDERER_ACCELERATED | initArgs.vsync ? SDL_RENDERER_PRESENTVSYNC : 0);
    #endif // _WIN32

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

    __update = true;

    targetTexture = SDL_CreateTexture(mainRenderer, 0, SDL_TEXTUREACCESS_TARGET, initArgs.w, initArgs.h);
    spriteBatch->sbSetRenderTarget(targetTexture);
    updateIntervalMs = 5;
    lastTimeCheck = SDL_GetTicks();

    SDL_DisplayMode mode;
    SDL_GetDisplayMode(0, 0, &mode);
    std::cout << mode.w << " x " << mode.h << " @ " << mode.refresh_rate << "hz" << std::endl;

    SDL_GetDisplayMode(0, 1, &mode);
    std::cout << mode.w << " x " << mode.h << " @ " << mode.refresh_rate << "hz" << std::endl;

    initBlocks();

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
    txture = spriteBatch->loadTexture(getResourcePath("") + "temp_tileset.png", &mainRenderer);
    contentManager.addTexture("test", txture);

    delete txture;

    std::cout << "addr_of contentManager (init): " << &contentManager << std::endl;
    screenManager = new ScreenManager(contentManager);
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

void GameWindow::toggleFullscreen()
{
    __fullscreen++;
    if(__fullscreen > 2)
        __fullscreen = 0;

    int res;
    switch(__fullscreen)
    {
        case 0:
            res = SDL_SetWindowFullscreen(gameWindow, 0);
            break;
        case 1:
            res = SDL_SetWindowFullscreen(gameWindow, SDL_WINDOW_FULLSCREEN);
            break;
        case 2:
            res = SDL_SetWindowFullscreen(gameWindow, SDL_WINDOW_FULLSCREEN_DESKTOP);
            break;
    }

    if(res != 0)
    {
        std::cerr << "Error executing fullscreen: " << SDL_GetError() << std::endl;
        SDL_SetWindowFullscreen(gameWindow, 0);
    }
}

void GameWindow::initBlocks()
{
    LuaBlockConfigLoader *lbcfl = new LuaBlockConfigLoader();
    lbcfl->loadBlocks();
    delete lbcfl;

    std::cout << "\"" << Tilemap[1]->getSheetName() << "\"" <<  std::endl;
}

void GameWindow::update()
{
    if(__update)
    {
        if(lastTimeCheck + updateIntervalMs < SDL_GetTicks())
        {
            inputHandler->update();
            screenManager->update(inputHandler);
            if(screenManager->getTestScreen()->doQuit)
            {
                std::cout << "Obeying Lua Script Error and quitting" << std::endl;
                quit = 1;
            }

            lastTimeCheck = SDL_GetTicks();
        }
        if(inputHandler->getEvent()->type == SDL_KEYDOWN)
            {
                if(inputHandler->getEvent()->key.keysym.sym == SDLK_ESCAPE)
                    quit = 1;
                if(inputHandler->getEvent()->key.keysym.sym == SDLK_F11)
                    toggleFullscreen();
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
                    std::cout << "Resized: " << width << " x " << height << std::endl;
                    break;
                case SDL_WINDOWEVENT_MINIMIZED:
                    __update = false;
                    std::cout << "Update stopped" << std::endl;
                    break;
                }
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
