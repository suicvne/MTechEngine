#define SDL_MAIN_HANDLED
#include <SDL.h>
#include "GameWindow.h"
#include "Camera2d.h"

using namespace std;

int main()
{
    GameWindow *mainGameWindow = new GameWindow();
    mainGameWindow->initializeSDL();

    delete mainGameWindow;

    return 0;
}
