#define SDL_MAIN_HANDLED
#include <SDL.h>
#include "GameWindow.h"
#include <stdio.h>

using namespace std;

int writeTest();
int readTest();
int launchSDLBrosX();

int main()
{
    //return writeTest();
    return readTest();
    //return launchSDLBrosX();
}

int launchSDLBrosX()
{
    GameWindow *mainGameWindow = new GameWindow();
    mainGameWindow->initializeSDL();

    delete mainGameWindow;

    return 0;
}

#include "src/IO/serializationwriter.h"
#include "src/IO/serializationreader.h"
#include <iostream>
#include <ostream>
int writeTest()
{
    //remove("test_cfile.bin");
    //remove("test_ofstream.bin");

    //char buffer[16];
    //memset(buffer, 0, sizeof(buffer));
    //MTechEngine::IO::SerializationWriter sw;
    //int pointer = 0;
    //sw.WriteBytes(buffer, pointer, 10); //00 00 00 0a (little endian int)
    //sw.WriteBytes(buffer, pointer, 10);
    //sw.WriteBytes(buffer, pointer, 10);

    //sw.WriteBytesToFile(buffer, sizeof(buffer), "test_cfile.bin");

    //ofstream ofs ("test_ofstream.bin", ofstream::out | ofstream::binary);
    //ofs.write(buffer, sizeof(buffer));
    //ofs.close();

    char buffer[16];
    memset(buffer, 0, sizeof(buffer));
    MTechEngine::IO::SerializationWriter sw;
    int pointer = 0;
    sw.WriteBytes(buffer, pointer, short(10));

    sw.WriteBytesToFile(buffer, sizeof(buffer), "testificate.bin");

    return 0;
}

int writeFullByteArray(char byteArray[], int size)
{
    for(int i = 0; i < size; i++)
    {
        std::cout << std::hex << static_cast<int>(byteArray[i]);
        std::cout<< " ";
        std::cout << std::dec;
        //printf("%02x ", &byteArray[i]);
    }
    std::cout << std::endl;
    return 0;
}

int readTest()
{
    char buffer[16];
    memset(buffer, 0, sizeof(buffer));
    MTechEngine::IO::SerializationReader sr;
    int pointer = 0;
    if(sr.ReadBytesFromFile(buffer, sizeof(buffer), "testificate.bin") != -1)
    {
        writeFullByteArray(buffer, sizeof(buffer));

        std::cout << "Pointer pre func: " << pointer << std::endl;

        short shouldBeTen = sr.ReadShort(buffer, pointer);
        std::cout << "This should be 10: " << shouldBeTen << std::endl;

        std::cout << "Pointer post func: " << pointer << std::endl;
    }
    else
    {
        std::cerr << "Error reading binary." << std::endl;
    }

    return 0;
}

