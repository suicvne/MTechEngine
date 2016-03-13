#include "LevelObject.h"
#include "SpriteBatch.h"
#include "InputHandler.h"
#include "Tile.h"
#include "global_vars.h"
#include "LevelBackground.h"
#include "ContentManager.h"

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
    background->draw(_sb, cm);

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
            //t->draw(_sb, mainContentManager);
        }
    }
}

void LevelObject::update(InputHandler *_ih)
{
    _ih->getEvent();
}
/**End protected*/
