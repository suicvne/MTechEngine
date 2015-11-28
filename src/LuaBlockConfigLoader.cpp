#include "LuaBlockConfigLoader.h"

LuaBlockConfigLoader::LuaBlockConfigLoader()
{
    L = lua_open();
}

void LuaBlockConfigLoader::report_errors(lua_State *L, int status)
{
    if(status != 0)
    {
        std::cerr << "BlockReadError: " << lua_tostring(L, -1); << std::endl;
        lua_pop(L, 1);
    }
}

LuaBlockConfigLoader::~LuaBlockConfigLoader()
{
    //dtor
}
