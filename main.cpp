#include "GameWindow.h"

using namespace std;

int main(int argc, char *argv[])
{
    GameWindow *mainGameWindow = new GameWindow();

    mainGameWindow->draw();

    return 0;
}
