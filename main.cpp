#include "GameWindow.h"

using namespace std;

int main(int argc, char *argv[])
{
    /*for(int i = 1; i < argc; i++)
    {
        cout << i << ": " << argv[i] << endl;
        if(argv[i] == "--debug")
        {
        }
    }*/

    SDLInitArgs args;
    args.x = 100;
    args.y = 100;
    args.w = 640;
    args.h = 480;
    args._windowTitle = "SDLEngineTest2";

    GameWindow *mainGameWindow = new GameWindow(args);
    mainGameWindow->initializeSDL();

    delete mainGameWindow;

    return 0;
}
