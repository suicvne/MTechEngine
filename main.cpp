#include "GameWindow.h"

using namespace std;

int main(int argc, char *argv[])
{
    SDLInitArgs args;
    args.x = -1;
    args.y = -1;
    args.w = 640;
    args.h = 480;
    args._windowTitle = "SDLEngineTest2";

    GameWindow *mainGameWindow = new GameWindow(args);
    mainGameWindow->initializeSDL();

    delete mainGameWindow;

    return 0;
}
