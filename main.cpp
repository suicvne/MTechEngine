#define SDL_MAIN_HANDLED
#include <SDL.h>
#include "GameWindow.h"

using namespace std;

int main()
{
    GameWindow *mainGameWindow = new GameWindow();
    mainGameWindow->initializeSDL();

    delete mainGameWindow;

    return 0;
}
