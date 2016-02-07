/**
  About {{filename}}.h/{{filename}}.cpp
  By: Mike

*/

#include "baseengine.h"
//#include "global_vars.h"

///TODO: fix this
#define __internal_width 800
#define __internal_height 600
///TODO: fix this


BaseEngine::BaseEngine(MTechApplication *application)
{
    __application = application;
}

BaseEngine::~BaseEngine()
{
    std::cout << "Destroying game objects" << std::endl;
    SDL_Quit();
    SDL_DestroyWindow(mainGameWindow);
    SDL_DestroyRenderer(sdlRenderer);
    SDL_DestroyTexture(targetTexture);
}

int BaseEngine::runApplication()
{
    if(__application != nullptr)
    {
        ConfigFile mainConfig = ConfigFile(__application->getConfigFilePath().c_str());
        mainConfig.readFile();
        if(InitializeSDL(mainConfig))
        {
            __application->LoadResources(contentManager, spriteBatch);

            width = mainConfig.getWindowWidth();
            height = mainConfig.getWindowHeight();

            ____UPDATE = true;
            return gameLoop();
        }
        else
        {
            return -2; //SDL initialization error
        }
    }
    else
        return -1; //couldn't run application

    return -3;
}

int BaseEngine::gameLoop()
{
    while(____DO_QUIT == false)
    {
        importantUpdate();
        __application->update(inputHandler);
        //important draw
        {
            if(____UPDATE)
            {
                spriteBatch->sbSetRenderTarget(targetTexture);
                spriteBatch->sbSetMainGameCamera(mainCamera);
                __application->draw(spriteBatch);
                spriteBatch->sbSetRenderTarget(nullptr);

                spriteBatch->sbBegin();
                spriteBatch->sbDrawTextureScaledConstant(targetTexture, 0, 0, width, height);
                spriteBatch->sbEnd();
            }
        }
        //TODO: application update and draw events
    }
    return 0;
}

/**
 * @brief MTechEngine::importantEvents These take precedence over Lua updates
 */
void BaseEngine::importantEvents()
{
    if(inputHandler->getEvent()->type == SDL_WINDOWEVENT)
    {
        switch(inputHandler->getEvent()->window.event)
        {
        case SDL_WINDOWEVENT_RESIZED:
            windowResize();
            break;
        case SDL_WINDOWEVENT_MINIMIZED:
            ____UPDATE = false;
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
        ____DO_QUIT = true;
    }
}

void BaseEngine::windowResize()
{
    int w, h;
    SDL_GetWindowSize(mainGameWindow, &w, &h);
    scaleGameW = w / __internal_width;
    scaleGameH = h / __internal_height;

    width = w;
    height = h;
    SDL_DestroyTexture(targetTexture);
    targetTexture = SDL_CreateTexture(sdlRenderer, SDL_GetWindowPixelFormat(mainGameWindow), SDL_TEXTUREACCESS_TARGET, __internal_width, __internal_height);
    SDL_Rect viewport;
    SDL_RenderGetViewport(sdlRenderer, &viewport);

    if(viewport.w != width || viewport.h != height)
    {
        SDL_Rect newWindowSize;
        newWindowSize.w = w;
        newWindowSize.h = h;
        SDL_RenderSetViewport(sdlRenderer, &newWindowSize);
    }
}

void BaseEngine::toggleFullscreen()
{
    __fullscreen++;
    if(__fullscreen > 2)
        __fullscreen = 0;

    int res;
    switch(__fullscreen)
    {
    case 0:
        res = SDL_SetWindowFullscreen(mainGameWindow, 0);
        break;
    case 1:
        res = SDL_SetWindowFullscreen(mainGameWindow, SDL_WINDOW_FULLSCREEN);
        break;
    case 2:
        res = SDL_SetWindowFullscreen(mainGameWindow, SDL_WINDOW_FULLSCREEN_DESKTOP);
        break;
    }
    if(res != 0)
    {
        std::cerr << "Error doing fullscreen: " << SDL_GetError() << std::endl;
        SDL_SetWindowFullscreen(mainGameWindow, 0);
    }
}

void BaseEngine::importantUpdate()
{
    if(____UPDATE)
    {
        inputHandler->update();
        importantEvents();
    }
    else
    {
        inputHandler->update();
        if(inputHandler->getEvent()->type == SDL_WINDOWEVENT)
        {
            if(inputHandler->getEvent()->window.event == SDL_WINDOWEVENT_RESTORED)
            {
                ____UPDATE = true;
                std::cout << "Update began" << std::endl;
            }
        }
    }
}

void BaseEngine::importantDraw()
{

}

bool BaseEngine::InitializeSDL(ConfigFile &configFile)
{
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return false;
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest"); //give it that retro look and feel

    mainGameWindow = SDL_CreateWindow(configFile.getWindowTitle().c_str(),
                                      configFile.getWindowX() == -1 ? SDL_WINDOWPOS_UNDEFINED : configFile.getWindowX(),
                                      configFile.getWindowY() == -1 ? SDL_WINDOWPOS_UNDEFINED : configFile.getWindowY(),
                                      configFile.getWindowWidth(),
                                      configFile.getWindowHeight(),
                                      SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    SDL_Surface *iconSurface = IMG_Load(std::string(getResourcePath("") + "/icon.png").c_str());
    SDL_SetWindowIcon(mainGameWindow, iconSurface);
    SDL_FreeSurface(iconSurface);

    if(mainGameWindow == nullptr)
    {
        std::cerr << "SDL_CreateWindow error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return false;
    }

    sdlRenderer = SDL_CreateRenderer(mainGameWindow, -1, SDL_RENDERER_ACCELERATED | configFile.getVsync() ? SDL_RENDERER_PRESENTVSYNC : 0);
    if(configFile.getVsync())
    {
        std::cout << "Launching the game with vsync" << std::endl;
        __vsyncEnabled = true;
    }

    if(sdlRenderer == nullptr)
    {
        SDL_DestroyWindow(mainGameWindow);
        std::cout << "SDL_CreateRenderer error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return false;
    }

    mainEventLoop = new SDL_Event();
    ____DO_QUIT = false;

    spriteBatch = new SpriteBatch(sdlRenderer);
    inputHandler = new InputHandler();
    mainSoundMixer = new SoundMixer(getResourcePath(""));
    mainCamera = new Camera2d(0, 0);
    contentManager = new ContentManager();

    targetTexture = SDL_CreateTexture(sdlRenderer, 0, SDL_TEXTUREACCESS_TARGET, configFile.getWindowWidth(), configFile.getWindowHeight());
    spriteBatch->sbSetRenderTarget(targetTexture);

    //TODO: get the target ref rate and divide by 2 to get the right update interval
    updateIntervalMs = 30;
    lastTimeCheck = SDL_GetTicks();

    return true;
}

std::string BaseEngine::getResourcePath(const std::string &subDir)
{
#ifdef _WIN32
const char PATH_SEP = '\\';
#else
const char PATH_SEP = '/';
#endif
//This will hold the base resource path: Lessons/res/
//We give it static lifetime so that we'll only need to call
//SDL_GetBasePath once to get the executable path
static std::string baseRes;
if (baseRes.empty()){
    //SDL_GetBasePath will return NULL if something went wrong in retrieving the path
    char *basePath = SDL_GetBasePath();
    if (basePath){
        baseRes = basePath;
        SDL_free(basePath);
    }
    else {
        std::cerr << "Error getting resource path: " << SDL_GetError() << std::endl;
        return "";
    }
    //We replace the last bin/ with res/ to get the the resource path
    size_t pos = baseRes.rfind("bin");
    baseRes = baseRes.substr(0, pos) + "res" + PATH_SEP;
}
//If we want a specific subdirectory path in the resource directory
//append it to the base path. This would be something like Lessons/res/Lesson0
return subDir.empty() ? baseRes : baseRes + subDir + PATH_SEP;
}

