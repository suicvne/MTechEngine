#include "GameWindow.h"

SDL_Texture *testTexture;

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

    testTexture = spriteBatch->loadTexture(GameWindow::getResourcePath() + "rayquaza.png", mainRenderer);

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
    if(testTexture != NULL)
        spriteBatch->sbDrawTexture(testTexture, 100, 100);
    spriteBatch->sbEnd();
}

void GameWindow::update()
{
    SDL_PollEvent(mainEventLoop);
}

std::string GameWindow::getResourcePath(const std::string &subDir)
{
	//We need to choose the path separator properly based on which
	//platform we're running on, since Windows uses a different
	//separator than most systems
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
