#include "LevelObject.h"
#include "SpriteBatch.h"
#include "InputHandler.h"
#include "Tile.h"
#include "global_vars.h"

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
}

LevelObject::LevelObject(LevelSettings __settings)
{
    lvlsettings = __settings;
}

LevelObject::~LevelObject()
{
    delete __tiles; //probably not ALL that needs to be done
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
            __tiles[x*lvlsettings.height+y] = __getBlockByID(-1);
        }
    }

    return 0;
}
/**End protected*/

/**Public*/
void LevelObject::draw(SpriteBatch *_sb)
{
    for(int x = 0; x < lvlsettings.width; ++x)
    {
        for(int y = 0; y < lvlsettings.height; ++y)
        {
            Tile *t = __tiles[x*lvlsettings.height+y]; //temp allocation to get standard template for block
            int tx = x * t->getWidth();
            int ty = y * t->getHeight();
            int tw = t->getWidth();
            int th = t->getHeight();
            t->setWorldPosition(tx, ty); //just in case i guess

        }
    }
}

void LevelObject::update(InputHandler *_ih)
{

}
/**End protected*/
