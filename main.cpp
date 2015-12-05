#include <SDL.h>
#include "GameWindow.h"
#include "Camera2d.h"

using namespace std;


int main(int argc, char *argv[])
{
    SDLInitArgs args;
    args.x = -1;
    args.y = -1;
    args.w = 800;
    args.h = 600; //true width and height
    args.vsync = true;
    args._windowTitle = "MTechEngine 1";

    GameWindow *mainGameWindow = new GameWindow(args);
    mainGameWindow->initializeSDL();

    delete mainGameWindow;

    return 0;
}
