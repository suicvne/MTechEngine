#include "GameWindow.h"

using namespace std;

int main()
{
    GameWindow *mainGameWindow = new GameWindow("Kek");

    mainGameWindow->draw();

    cout << "Hello world!" << endl;
    return 0;
}
