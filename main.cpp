#include "GameWindow.h"

using namespace std;

int main(int argc, char *argv[])
{
    cout << "asdf: " << argv[0] << endl;
    for(int i = 0; i < argc; i++)
    {
        cout << i << ": " << argv[i] << endl;
        if(argv[i] == "--debug")
        {
            #define __SDLENGINE_DEBUG
        }
    }

    #ifdef __SDLENGINE_DEBUG
    cout << "Starting engine in debug mode" << endl;
    #endif // __SDLENGINE_DEBUG

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
