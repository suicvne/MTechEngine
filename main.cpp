#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <stdio.h>
#include "GameWindow.h"
#include "mtechapplication.h"
#include "baseengine.h"
#include "ScreenManager.h"
#include "LuaBlockConfigLoader.h"
#include "enginestaticvariables.h"

//using namespace std;

class SuperSDLBrothersX : public MTechApplication
{
public:
    SuperSDLBrothersX()
    {}
    virtual ~SuperSDLBrothersX()
    {}
    virtual void LoadResources(ContentManager *cm, SpriteBatch *spriteBatch) override
    {
        try
        {
            this->loadTextures(cm, spriteBatch);
            this->loadBlockConfigsAndBackgrounds();
            EngineStaticVariables::MainScreenManager->pushScreen(ScreenManager::SPLASHSCREEN);
        }
        catch(std::exception &e)
        {
            std::cerr << "Exception: " << e.what() << std::endl;
        }
    }
    virtual void draw(SpriteBatch *spriteBatch, ContentManager *cm) override
    {
        EngineStaticVariables::MainScreenManager->draw(spriteBatch, cm);
    }
    virtual void update(SDL_Event const &_ih) override
    {
        EngineStaticVariables::MainScreenManager->update(_ih);
    }
    std::string getConfigFilePath()
    {
        return EngineStaticVariables::GetResourcesPath() + "/game_config.cfg";
    }
private:
    void loadTextures(ContentManager *cm, SpriteBatch *spriteBatch)
    {
        SDL_Texture *text; //temporary texture allocater
        text = spriteBatch->loadTexture(std::string(SDL_GetBasePath() + std::string("/res/tiles/full.png")));
        cm->addTexture("test_sheet", text);
        text = spriteBatch->loadTexture(std::string(SDL_GetBasePath() + std::string("/res/logo.png")));
        cm->addTexture("company_logo", text);
        text = spriteBatch->loadTexture(std::string(SDL_GetBasePath() + std::string("/res/bg/all.png")));
        cm->addTexture("bg_index", text);
        text = spriteBatch->loadTexture(std::string(SDL_GetBasePath() + std::string("/res/selection.png")));
        cm->addTexture("selection", text);
        text = spriteBatch->loadTexture(std::string(SDL_GetBasePath() + std::string("/res/sdlbros.png")));
        cm->addTexture("sdlbroslogo", text);
    }
    void loadBlockConfigsAndBackgrounds()
    {
        LuaBlockConfigLoader *lbcfl = new LuaBlockConfigLoader();
        lbcfl->loadBlocks();
        lbcfl->loadBackgrounds();
        delete lbcfl;
    }
};

int largerNumberSerializerTest();
int launchSDLBrosX();
int newApplicationTypeTest();

int main()
{
    return newApplicationTypeTest();
}


int newApplicationTypeTest()
{
    //Our instance of MTechApplication
    SuperSDLBrothersX *sdlBros = new SuperSDLBrothersX();
    //The base engine initiated with the application
    BaseEngine *e = new BaseEngine(sdlBros);
    //We run the application
    e->runApplication();

    delete e;
    delete sdlBros;
    return 0;
}

/*
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
}*/
