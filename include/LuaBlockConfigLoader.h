#ifndef LUABLOCKCONFIGLOADER_H
#define LUABLOCKCONFIGLOADER_H
extern "C"
{
    #include <lua.h>
    #include <lualib.h>
    #include <lauxlib.h>
}
#include <iostream>
#include <string>
#include <sstream>
#include "luna.h"

class LuaBlockConfigLoader
{
    public:
        LuaBlockConfigLoader();
        ~LuaBlockConfigLoader();
        void loadBlocks();
        void report_errors(lua_State *L, int status);
    protected:
    private:
        lua_State *L;
};

#endif // LUABLOCKCONFIGLOADER_H
