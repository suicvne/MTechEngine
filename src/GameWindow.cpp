#include "GameWindow.h"

GameWindow::GameWindow()
{
    initArgs.x = -1;
    initArgs.y = -1;
    width = 800;
    height = 600;
    winTitle = "MTechEngine";
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

    GameWindow::mainRenderer = SDL_CreateRenderer(GameWindow::gameWindow, -1, SDL_RENDERER_ACCELERATED | initArgs.vsync ? SDL_RENDERER_PRESENTVSYNC : 0);

    if(initArgs.vsync)
    {
        std::cout << "Launching the game with vsync" << std::endl;
        __vsyncEnabled = true;
    }

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
    MainGameCamera.setCameraPosition(0.0f, 0.0f);

    initBlocks();
    loadTextures();

    __update = true;

    if(mainRenderer == NULL)
        std::cout << "!!!!!!!!!!! YOURE FUCKED" << std::endl;

    targetTexture = SDL_CreateTexture(mainRenderer, 0, SDL_TEXTUREACCESS_TARGET, initArgs.w, initArgs.h);
    spriteBatch->sbSetRenderTarget(targetTexture);

    //TODO: get the target refresh rate and divide it by half to get the update interval in ms
    updateIntervalMs = 30;
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
    SDL_Texture *txture;
    txture = spriteBatch->loadTexture(getResourcePath("") + "/tiles/full.png", &mainRenderer);
    contentManager.addTexture("test_sheet", txture);
    txture = spriteBatch->loadTexture(getResourcePath("") + "logo.png", &mainRenderer);
    contentManager.addTexture("company_logo", txture);

    //delete txture;

    std::cout << "addr_of contentManager (init): " << &contentManager << std::endl;
    screenManager = new ScreenManager(contentManager);

    screenManager->pushScreen(SPLASHSCREEN);
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
    if(__updateGame)
    {
        spriteBatch->sbSetRenderTarget(targetTexture);
        spriteBatch->sbSetMainGameCamera(&MainGameCamera);
        screenManager->draw(spriteBatch);
        spriteBatch->sbSetRenderTarget(nullptr);

        spriteBatch->sbBegin();
        spriteBatch->sbDrawTextureScaledConstant(targetTexture, 0, 0, width, height);
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

    //Test to make sure we're sane
    std::cout << std::endl << "===BEGIN BLOCK SANITY CHECK===" << std::endl;
    for(int i = 1; i <= TOTAL_TILE_COUNT; i++)
    {
        Tile *t;
        t = Tilemap[i];

        if(t == NULL)
        {
            std::cout << "Tile with index " << i << " was null?!?!" << std::endl;
            continue;
        }

        std::cout << "Test: Tile \"" << t->getBlockName() << "\"" << std::endl;
        if(t->getAnimated())
        {
            std::cout << " Animated. First Index: " << t->getAllFrames()[0].getX() << ", " << t->getAllFrames()[0].getY() << std::endl;
            //std::vector<_vector2i> frms = t->getAllFrames();
        }
        else
        {
            std::cout << " Non-Animated. Area: " << t->getNonAnimatedArea()->getX() << ", " <<t->getNonAnimatedArea()->getY() << std::endl;
        }
    }
    std::cout << "===END BLOCK SANITY CHECK===" << std::endl << std::endl;
    //std::cout << "From GameWindow: \"" << Tilemap->operator[](1)->getSheetName() << "\"" <<  std::endl;
}

void GameWindow::windowResize()
{
    int w, h;
    SDL_GetWindowSize(GameWindow::gameWindow, &w, &h);
    scaleGameW = w / 800;
    scaleGameH = h / 600;

    width = w;
    height = h;
    SDL_DestroyTexture(targetTexture);
    targetTexture = SDL_CreateTexture(mainRenderer, SDL_GetWindowPixelFormat(gameWindow), SDL_TEXTUREACCESS_TARGET, 800, 600);
    SDL_Rect viewport;
    SDL_RenderGetViewport(mainRenderer, &viewport);

    if(viewport.w != width || viewport.h != height)
    {
        SDL_Rect newWindowSize;
        newWindowSize.w = w;
        newWindowSize.h = h;
        SDL_RenderSetViewport(mainRenderer, &newWindowSize);
    }
}

/**
These updates take priority over even Lua updates
*/
void GameWindow::importantUpdates()
{
if(inputHandler->getEvent()->type == SDL_WINDOWEVENT)
            {
                switch(inputHandler->getEvent()->window.event)
                {
                case SDL_WINDOWEVENT_RESIZED:
                    windowResize();
                    //width = inputHandler->getEvent()->window.data1;
                    //height = inputHandler->getEvent()->window.data2;
                    //std::cout << "Resized: " << width << " x " << height << std::endl;
                    break;
                case SDL_WINDOWEVENT_MINIMIZED:
                    __updateGame = false;
                    std::cout << "Update stopped" << std::endl;
                    break;
                }
            }
        if(inputHandler->getEvent()->type == SDL_KEYDOWN)
            {
                if(inputHandler->getEvent()->key.keysym.sym == SDLK_ESCAPE)
                    quit = 1;
                if(inputHandler->getEvent()->key.keysym.sym == SDLK_F11)
                    toggleFullscreen();
                if(inputHandler->getEvent()->key.keysym.sym == SDLK_LEFT)
                {
                    MainGameCamera.setCameraX(MainGameCamera.getCameraX() - -1.0f);
                }
                if(inputHandler->getEvent()->key.keysym.sym == SDLK_UP)
                {
                    MainGameCamera.setCameraY(MainGameCamera.getCameraY() - -1.0f);
                }
                if(inputHandler->getEvent()->key.keysym.sym == SDLK_RIGHT)
                {
                    MainGameCamera.setCameraX(MainGameCamera.getCameraX() + -1.0f);
                }
                if(inputHandler->getEvent()->key.keysym.sym == SDLK_DOWN)
                {
                    MainGameCamera.setCameraY(MainGameCamera.getCameraY() + -1.0f);
                }
            }
            if(inputHandler->getEvent()->type == SDL_QUIT)
            {
                quit = 1;
            }
}

void GameWindow::update()
{
    if(__updateGame)
    {
        inputHandler->update();
        importantUpdates();

        if(__vsyncEnabled)
        {
            screenManager->update(inputHandler);

            if(screenManager->getSplashScreen()->goNext())
            {
                screenManager->pushScreen(TESTSCREEN);
            }
            if(screenManager->getTestScreen()->doQuit)
            {
                std::cout << "Obeying Lua Script Error and quitting" << std::endl;
                quit = 1;
            }

            lastTimeCheck = SDL_GetTicks();
        }
        else if(lastTimeCheck + updateIntervalMs < (int)SDL_GetTicks())
        {
            screenManager->update(inputHandler);
            if(screenManager->getTestScreen()->doQuit)
            {
                std::cout << "Obeying Lua Script Error and quitting" << std::endl;
                quit = 1;
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
                __updateGame = true;
                std::cout << "Update began" << std::endl;
            }
        }

    }
}
