#include "LuaBlockConfigLoader.h"

LuaBlockConfigLoader::LuaBlockConfigLoader()
{
    L = lua_open();
}

void LuaBlockConfigLoader::report_errors(lua_State *L, int status)
{
	if (status != 0)
	{
		std::cerr << "-- " << lua_tostring(L, -1) << std::endl;
		lua_pop(L, 1); //remove error message
	}
}

LuaBlockConfigLoader::~LuaBlockConfigLoader()
{
    delete L;
}

void LuaBlockConfigLoader::loadBlocks()
{
    for(int i = 0; i < 300; i++) //temp block count of 300
    {
        std::ostringstream __s;
        __s << GameWindow::getResourcePath("") << "/blocks/block" << i << ".lua";
        std::string path(__s.str());
        int s = luaL_loadfile(L, path.c_str());
    }
}
