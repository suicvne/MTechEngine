#include "LevelObject.h"
#include "SpriteBatch.h"
#include "InputHandler.h"
#include "Tile.h"
#include "global_vars.h"
#include "LevelBackground.h"
#include "ContentManager.h"

#include "io/serializationwriter.h"
#include "io/serializationreader.h"

#include "enginestaticvariables.h"

/**
---TODO---
1. Lua hookins
*/

/**Constructors*/
LevelObject::LevelObject()
{
    LevelSettings s;
    s.width = 25;
    s.height = 19;
    lvlsettings = s;

    initLevel();
}

LevelObject::LevelObject(LevelSettings __settings)
{
    lvlsettings = __settings;
    initLevel();
}

LevelObject::~LevelObject()
{
    free(__tiles); //probably not ALL that needs to be done
}
/**End constructors*/

/**Protected*/
int LevelObject::initLevel()
{
    const int w = lvlsettings.width;
    const int h = lvlsettings.height;

    __tiles = new Tile*[w*h]; //declare as one big chunk
                             //replace __tiles[x][y] with __tiles[x*h+y] ?

    for(int x = 0; x < lvlsettings.width; ++x)
    {
        for(int y = 0; y < lvlsettings.height; ++y)
        {
            __tiles[x*lvlsettings.height+y] = EngineStaticVariables::GetBlockByID(-1);
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
            Tile *t = __tiles[x*lvlsettings.height+y]; //temp allocation to get standard template for block
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
                tx = x * t->getWidth();
                ty = y * t->getHeight();
                //tw = t->getWidth();
                //th = t->getHeight();
            }

            t->setWorldPosition(tx, ty); //just in case i guess
            t->draw(_sb, cm);
        }
    }
}

void LevelObject::loadLevelFile(std::string levelFile)
{
    std::cout << "Beginning reading of level from '" << levelFile << "'" << std::endl;
    MTechEngine::IO::SerializationReader reader;
    int sizeOfFile = reader.GetSizeOfFile(levelFile.c_str());
    char* buffer = new char[sizeOfFile]();
    reader.ReadBytesFromFile(buffer, sizeOfFile, levelFile.c_str());
    std::cout << "\tSize of file is " << sizeOfFile << " bytes." << std::endl;
    std::cout << "\t\tHeader is " << 10 << " bytes." << std::endl;
    std::cout << "\t\tLevel is " << sizeOfFile - 10 << std::endl;

    int levelWidth, levelHeight;
    short backgroundId;
    int pointer = 0;

    levelWidth = reader.ReadInt(buffer, pointer); //width
    levelHeight = reader.ReadInt(buffer, pointer); //height
    backgroundId = reader.ReadShort(buffer, pointer); //background id
    //we should now be at index 10

    std::cout << "\tSize of level is " << levelWidth << " x " << levelHeight << " blocks." << std::endl;
    std::cout << "\tBackground ID is " << backgroundId << std::endl;
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
            serializer.WriteBytes(buffer, pointer, ((short)toWrite->getId()));
            serializer.WriteBytes(buffer, pointer, x);
            serializer.WriteBytes(buffer, pointer, y);
        }
    }

    serializer.WriteBytesToFile(buffer, bytesSize, levelFile.c_str());

    free(buffer); //i hope

    std::cout << "Hopefully saved!!" << std::endl;
}

void LevelObject::update(InputHandler *_ih)
{
    _ih->getEvent();
}
/**End protected*/
