#include "LuaBlockConfigLoader.h"

int LUA_makeVector2i(lua_State *L)
{
    _vector2i *returnVal = new _vector2i();
    int x, y;
    x = lua_tonumber(L, 1);
    y = lua_tonumber(L, 2);
    returnVal->setX(x);
    returnVal->setY(y);
    lua_pushlightuserdata(L, returnVal);
    return 1;
}

LuaBlockConfigLoader::LuaBlockConfigLoader()
{
    L = lua_open();
}

void LuaBlockConfigLoader::report_errors(lua_State *L, int status)
{
    if(status != 0)
    {
        std::cout << "BlockReadError: " << lua_tostring(L, -1) << std::endl;
        lua_pop(L, 1);
    }
}

void LuaBlockConfigLoader::loadBlocks()
{
    for(int i = 1; i <= TOTAL_TILE_COUNT; i++)
    {
        std::ostringstream __s;
        __s << GameWindow::getResourcePath("") << "blocks/block" << i << ".lua";
        std::string path(__s.str());

        int status = luaL_loadfile(L, path.c_str());
        if(status != 0)
        {
            report_errors(L, status);
            continue;
        }
        else
        {
            lua_register(L, "Vector2i", LUA_makeVector2i);

            lua_pcall(L, 0, 0, 0);

            Tile *t = new Tile();
            _vector2i **frmsVector;
            lua_getglobal(L, "__name");
            lua_getglobal(L, "__id");
            lua_getglobal(L, "__width");
            lua_getglobal(L, "__height");
            lua_getglobal(L, "__animated");
            lua_getglobal(L, "__sheet");
            lua_getglobal(L, "__frames");
            lua_getglobal(L, "__framecount");
            lua_getglobal(L, "__frameupdate");
            t->setBlockName(std::string(lua_tostring(L, -9)));
            t->setBlockSize(lua_tonumber(L, -7), lua_tonumber(L, -6));
            t->setAnimated(lua_toboolean(L, -5));
            t->setSheetName(std::string(lua_tostring(L, -4)));

            frmsVector = ((_vector2i**)lua_touserdata(L, -3));

            SDL_Rect **frames = rectArrayFromVectorArray(frmsVector, lua_tonumber(L, -2), t->getWidth(), t->getHeight());
            t->setAnimatedFrames(frames);
            //t->setAnimatedFrames();
            t->setFrameCount(lua_tonumber(L, -2));
            t->setFrameUpdateInterval(lua_tonumber(L, -1));

            Tilemap[i] = t;

            std::cout << "Added block-" << i << " with name '" << t->getBlockName() << "'." << std::endl;
            std::cout << "Sheetname: " << t->getSheetName() << std::endl;
            std::cout << "Test: " << Tilemap[i]->getSheetName() << std::endl;

            //frames = Tilemap[i]->getAllFrames();

            std::cout << "Another test: " << frames[0]->x << ", " << frames[0]->y <<std::endl;
        }
    }
}

SDL_Rect **LuaBlockConfigLoader::rectArrayFromVectorArray(_vector2i **arr, int frameCount, int w, int h)
{
    SDL_Rect *rectArray[frameCount];
    for(int i = 0; i < frameCount; i++)
    {
        SDL_Rect temp;
        temp.x = arr[i]->getX();
        temp.y = arr[i]->getY();
        temp.w = w;
        temp.h = h;

        std::cout << w << ", " << h << std::endl;

        rectArray[i] = &temp;
    }

    return rectArray;
}

LuaBlockConfigLoader::~LuaBlockConfigLoader()
{
    //dtor
}
