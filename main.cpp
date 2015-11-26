#include <SDL.h>
#include "GameWindow.h"

using namespace std;

int main(int argc, char *argv[])
{
    std::map<const char*, SDL_Texture*> testMap;
    testMap["kek"] = 0;

    SDLInitArgs args;
    args.x = -1;
    args.y = -1;
    args.w = 800;
    args.h = 600;
    args._windowTitle = "SDL Brothers X";

    GameWindow *mainGameWindow = new GameWindow(args);
    mainGameWindow->initializeSDL();

    delete mainGameWindow;

    return 0;
}
