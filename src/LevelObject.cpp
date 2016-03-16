#include "LevelObject.h"
#include "SpriteBatch.h"
#include "InputHandler.h"
#include "Tile.h"
#include "global_vars.h"
#include "LevelBackground.h"
#include "ContentManager.h"

#include "IO/serializationwriter.h"
#include "IO/serializationreader.h"

#include "enginestaticvariables.h"

#include "MathsStuff.h"
#include "StandardColors.h"
#include "Camera2d.h"
/**
---TODO---
1. Lua hookins
*/

/**Constructors*/
LevelObject::LevelObject()
{
    LevelSettings s;
    s.width = MathsStuff::ceiling(800 / 32);
    s.height = MathsStuff::ceiling(600 / 32);
    lvlsettings = s;

    initLevel();

    std::cout << "Size of Tile: " << sizeof(Tile) << std::endl;
}

LevelObject::LevelObject(LevelSettings __settings)
{
    lvlsettings = __settings;
    initLevel();
}

LevelObject::~LevelObject()
{
    //free(__tiles); //probably not ALL that needs to be done
    for(size_t i = 0; i < __tiles.size(); i++) //recursively free the Tile pointers
    {
        delete __tiles[i];
    }
    __tiles.clear();
}
/**End constructors*/

/**Protected*/
int LevelObject::initLevel()
{
    const int w = lvlsettings.width;
    const int h = lvlsettings.height;

    //__tiles = new Tile*[w*h]; //declare as one big chunk
                             //replace __tiles[x][y] with __tiles[x*h+y] ?
    __tiles = std::vector<Tile*>();

    for(int x = 0; x < lvlsettings.width; ++x)
    {
        for(int y = 0; y < lvlsettings.height; ++y)
        {
            __tiles.insert(__tiles.end(), EngineStaticVariables::GetBlockByID(2));
        }
    }

    background = EngineStaticVariables::GetBackgroundByID(1);
    background->lwidth = lvlsettings.width;
    background->lheight = lvlsettings.height;

    return 0;
}
/**End protected*/

/**Public*/
void LevelObject::draw(SpriteBatch* _sb, ContentManager* cm)
{
    _sb->sbBegin();

    if(background != nullptr)
        background->draw(_sb, cm);
    else
    {
        std::cerr << "Background was null!!" << std::endl;
        EngineStaticVariables::DoQuit = true;
    }

    for(int x = 0; x < lvlsettings.width; ++x)
    {
        for(int y = 0; y < lvlsettings.height; ++y)
        {
            if(!reading)
            {
                int index = x*lvlsettings.height+y;
                Tile *t = __tiles[index]; //temp allocation to get standard template for block
                int tx, ty;//, tw, th;
                if(t->getWidth() <= 0)
                {
                    tx = x * 32;
                    ty = y * 32;
                    //tw = 32;
                    //th = 32;
                }
                else
                {
                    tx = x * (t->getWidth() * 2);
                    ty = y * (t->getHeight() * 2);
                    //tw = t->getWidth();
                    //th = t->getHeight();
                }

                t->setWorldPosition(tx, ty); //just in case i guess
                t->draw(_sb, cm);
            }
        }
    }
    if(showLevelAreaDebug)
    {
        SDL_Rect levelAreaRect;
        levelAreaRect.x = 0 + EngineStaticVariables::MainGameCamera->getCameraX();
        levelAreaRect.y = 0 + EngineStaticVariables::MainGameCamera->getCameraY();
        levelAreaRect.w = (lvlsettings.width * 32);
        levelAreaRect.h = (lvlsettings.height * 32);
        _sb->sbFillRect(&StandardColors::strongRed, &levelAreaRect);
    }

    _sb->sbEnd();
}

void LevelObject::toggleLevelAreaDebug()
{
    this->showLevelAreaDebug = !showLevelAreaDebug;
}

void LevelObject::loadLevelFile(std::string levelFile)
{
    reading = true;
    std::cout << "Beginning reading of level from '" << levelFile << "'" << std::endl;
    MTechEngine::IO::SerializationReader reader;
    int sizeOfFile = reader.GetSizeOfFile(levelFile.c_str());
    char* buffer = new char[sizeOfFile]();
    reader.ReadBytesFromFile(buffer, sizeOfFile, levelFile.c_str());
    std::cout << "\tSize of file is " << sizeOfFile << " bytes." << std::endl;
    if(sizeOfFile < 1) //then we fucked up. file probably doesn't exist
    {
        std::cerr << "\t\tYou fucked up. File probably doesn't exist" << std::endl;
        return;
    }
    std::cout << "\t\tHeader is " << 10 << " bytes." << std::endl;
    std::cout << "\t\tLevel is " << sizeOfFile - 10 << " bytes." << std::endl;

    int levelWidth, levelHeight;
    short backgroundId;
    int pointer = 0;


    levelWidth = reader.ReadInt(buffer, pointer); //width
    levelHeight = reader.ReadInt(buffer, pointer); //height
    backgroundId = reader.ReadShort(buffer, pointer); //background id
    //we should now be at index 10

    lvlsettings.width = levelWidth;
    lvlsettings.height = levelHeight;

    std::cout << "\tSize of level is " << levelWidth << " x " << levelHeight << " blocks." << std::endl;
    std::cout << "\tBackground ID is " << backgroundId << std::endl;

    int blocksToRead = ((sizeOfFile - 10) / 10);
    std::cout << "\tBlocks we need to read: " << blocksToRead << std::endl;
    //free(this->__tiles);
    __tiles.clear();
    //this->__tiles = new Tile*[blocksToRead](); //yay for pointers old method used a Tile*[] / Tile**
    for(int i = 0; i < blocksToRead; i++)
    {
        short blockId = reader.ReadShort(buffer, pointer);
        std::cout << "\tBlock ID: " << blockId << std::endl;
        int x = reader.ReadInt(buffer, pointer);
        int y = reader.ReadInt(buffer, pointer);
        Tile* block = EngineStaticVariables::GetBlockByID((int)blockId);
        if(block == nullptr)
            block = EngineStaticVariables::GetBlockByID(-1); //air

        std::cout << "\t" << i << ". " << "Block at " << x << ", " << y << " is " << block->getBlockName() << std::endl;
        std::cout << "\t\t" << "Size: " << block->getWidth() << " x " << block->getHeight() << std::endl;
        std::cout << "\t\tPointer: " << pointer << ". i: " << i << "  blocksToRead: " << blocksToRead << std::endl;
        __tiles[x*levelHeight*y] = block;

        if(pointer >= sizeOfFile)
            break;
    }

    std::cout << "Done!" << std::endl << std::endl;
    reading = false;
}

void LevelObject::saveLevelFile(std::string levelFile)
{
    std::cout << "Beginning serialization of level to '" << levelFile << "'" << std::endl;

    MTechEngine::IO::SerializationWriter serializer;

    //The header is 4 + 4 + 2 = 10
    //The storage of a block id & its width and height takes up 2 + 4 + 4 = 10 bytes
    int levelWidth = lvlsettings.width; //just copying this for convienence sake
    int levelHeight = lvlsettings.height;
    int blockCount = levelWidth * levelHeight; //totalBlockCount
    int bytesSize = 10 + (blockCount * 10);
    char* buffer = new char[bytesSize](); //this is permitted as it's made on the heap
    std::cout << "\tSize of level file (in bytes) = " << bytesSize << std::endl;
    serializer.WriteBytesToFile(buffer, sizeof(buffer), levelFile.c_str()); //overwrite old file
    int pointer = 0; //pointer needed for the serializer

    serializer.WriteBytes(buffer, pointer, levelWidth); //width
    serializer.WriteBytes(buffer, pointer, levelHeight); //height

    serializer.WriteBytes(buffer, pointer, ((short)this->background->id)); //background index

    for(int x = 0; x < levelWidth; x++)
    {
        for(int y = 0; y < levelHeight; y++)
        {
            Tile* toWrite = this->__tiles[x*levelHeight+1];
            serializer.WriteBytes(buffer, pointer, ((short)toWrite->getId())); //id
            serializer.WriteBytes(buffer, pointer, x); //x
            serializer.WriteBytes(buffer, pointer, y); //y
        }
    }

    serializer.WriteBytesToFile(buffer, bytesSize, levelFile.c_str());

    free(buffer); //i hope

    std::cout << "Hopefully saved!!" << std::endl;
}

void LevelObject::update(SDL_Event const &_ih)
{
    for(int x = 0; x < lvlsettings.width; x++)
    {
        for(int y = 0; y < lvlsettings.height; y++)
        {
            Tile* tile = __tiles[x*lvlsettings.height+y];
            if(tile != nullptr)
                tile->update();
        }
    }
}
/**End protected*/
