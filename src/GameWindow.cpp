#include "GameWindow.h"
#include "Camera2d.h"
#include "LevelBackground.h"

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
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
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
    ______DO_QUIT = false;
    spriteBatch = new SpriteBatch(mainRenderer);
    inputHandler = new InputHandler();
    mainSoundMixer = new SoundMixer(getResourcePath(""));
    mainGameCamera = new Camera2d(0, 0);
    //mainGameCamera->setCameraPosition(0.0f, 0.0f);

    initBlocks();
    loadTextures();

    __update = true;

    targetTexture = SDL_CreateTexture(mainRenderer, 0, SDL_TEXTUREACCESS_TARGET, initArgs.w, initArgs.h);
    spriteBatch->sbSetRenderTarget(targetTexture);

    //TODO: get the target refresh rate and divide it by half to get the update interval in ms
    updateIntervalMs = 30;
    lastTimeCheck = SDL_GetTicks();
    while(______DO_QUIT == false)
    {
        GameWindow::update();
        GameWindow::draw();
    }
}

void GameWindow::loadTextures()
{
    mainContentManager = new ContentManager();

    SDL_Texture *txture;
    txture = spriteBatch->loadTexture(getResourcePath("") + "tiles/full.png", &mainRenderer);
    mainContentManager->addTexture("test_sheet", txture);
    txture = spriteBatch->loadTexture(getResourcePath("") + "logo.png", &mainRenderer);
    mainContentManager->addTexture("company_logo", txture);
    txture = spriteBatch->loadTexture(getResourcePath("") + "bg/all.png", &mainRenderer);
    mainContentManager->addTexture("bg_index", txture);
    txture = spriteBatch->loadTexture(getResourcePath("") + "selection.png", &mainRenderer);
    mainContentManager->addTexture("selection", txture);
    txture = spriteBatch->loadTexture(getResourcePath("") + "sdlbros.png", &mainRenderer);
    mainContentManager->addTexture("sdlbroslogo", txture);

    mainScreenManager = new ScreenManager(mainContentManager);

    mainScreenManager->pushScreen(SPLASHSCREEN);
}

GameWindow::~GameWindow()
{
    std::cout << "Destroying game objects" << std::endl;
    delete mainSoundMixer;
    SDL_Quit();
    SDL_DestroyWindow(GameWindow::gameWindow);
    SDL_DestroyRenderer(GameWindow::mainRenderer);
    delete mainScreenManager;
    delete mainEventLoop;
}

void GameWindow::draw()
{
    if(__updateGame)
    {
        spriteBatch->sbSetRenderTarget(targetTexture);
        spriteBatch->sbSetMainGameCamera(mainGameCamera);
        mainScreenManager->draw(spriteBatch);
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
    lbcfl->loadBackgrounds();
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

    std::cout << std::endl << "===BEGIN BACKGROUND SANITY CHECK===" << std::endl;
    for(int i = 1; i <= TOTAL_BACKGROUND_COUNT; i++)
    {
        LevelBackground *lb;
        lb = BackgroundMap[i];
        if(lb == NULL)
        {
            std::cout << "Background with index " << i << " was null?!?!?!" << std::endl;
        }

        std::cout << "Test: Background \"" << lb->bgname << "\"" << std::endl;
        std::cout << " Area: " << lb->singleFrame->getX() << ", " << lb->singleFrame->getY() << std::endl;
    }
    std::cout << "===BEGIN BACKGROUND SANITY CHECK===" << std::endl << std::endl;
}

void GameWindow::windowResize()
{
    int w, h;
    SDL_GetWindowSize(GameWindow::gameWindow, &w, &h);
    scaleGameW = w / __internal_width;
    scaleGameH = h / __internal_height;

    width = w;
    height = h;
    SDL_DestroyTexture(targetTexture);
    targetTexture = SDL_CreateTexture(mainRenderer, SDL_GetWindowPixelFormat(gameWindow), SDL_TEXTUREACCESS_TARGET, __internal_width, __internal_height);
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
                    break;
                case SDL_WINDOWEVENT_MINIMIZED:
                    __updateGame = false;
                    std::cout << "Update stopped" << std::endl;
                    break;
                }
            }
        if(inputHandler->getEvent()->type == SDL_KEYDOWN)
            {
                if(inputHandler->getEvent()->key.keysym.sym == SDLK_F11)
                    toggleFullscreen();
            }
            if(inputHandler->getEvent()->type == SDL_QUIT)
            {
                ______DO_QUIT = 1;
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
            mainScreenManager->update(inputHandler);

            if(mainScreenManager->getTestScreen()->doQuit)
            {
                std::cout << "Obeying Lua Script Error and quitting" << std::endl;
                ______DO_QUIT = 1;
            }
            if(mainScreenManager->getCurrentScreen() == TESTSCREEN)
            {
                mainSoundMixer->playSong(); //only play test song on test screen
            }

            lastTimeCheck = SDL_GetTicks();
        }
        else if(lastTimeCheck + updateIntervalMs < (int)SDL_GetTicks())
        {
            mainScreenManager->update(inputHandler);
            if(mainScreenManager->getTestScreen()->doQuit)
            {
                std::cout << "Obeying Lua Script Error and quitting" << std::endl;
                ______DO_QUIT = 1;
            }

            lastTimeCheck = SDL_GetTicks();
        }
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
