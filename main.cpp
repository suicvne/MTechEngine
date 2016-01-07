#define SDL_MAIN_HANDLED
#include <SDL.h>
#include "GameWindow.h"

using namespace std;

int serializationTest();
int launchSDLBrosX();

int main()
{
    //return serializationTest();
    return launchSDLBrosX();
}

int launchSDLBrosX()
{
    GameWindow *mainGameWindow = new GameWindow();
    mainGameWindow->initializeSDL();

    delete mainGameWindow;

    return 0;
}

#include "src/IO/serializationwriter.h"
#include <iostream>
#include <ostream>
int serializationTest()
{
    remove("test_cfile.bin");
    remove("test_ofstream.bin");

    char buffer[16];
    memset(buffer, 0, sizeof(buffer));
    MTechEngine::IO::SerializationWriter sw;
    int pointer = 0;
    sw.WriteBytes(buffer, pointer, 10); //00 00 00 0a (little endian int)
    sw.WriteBytes(buffer, pointer, 10);
    sw.WriteBytes(buffer, pointer, 10);

    sw.WriteBytesToFile(buffer, sizeof(buffer), "test_cfile.bin");

    ofstream ofs ("test_ofstream.bin", ofstream::out | ofstream::binary);
    ofs.write(buffer, sizeof(buffer));
    ofs.close();
    return 0;
}

