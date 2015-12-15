#include "LevelObject.h"
#include "SpriteBatch.h"
#include "InputHandler.h"
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
    delete this->_wtiles;
    delete this->_htiles;
}
/**End constructors*/

/**Protected*/
int LevelObject::initLevel()
{
    __tiles = new int[lvlsettings.width][lvlsettings.height];
    for(int x = 0; x < _wtiles; x++)
    {
        for(int y = 0; y < _htiles; y++)
        {
            __tiles[x][y] = -1; //initializing to -1 which is air
        }
    }
    return 0;
}
/**End protected*/

/**Public*/
void LevelObject::draw(SpriteBatch *_sb)
{

}

void LevelObject::update(InputHandler *_ih)
{

}
/**End protected*/
