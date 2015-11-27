#ifndef LUABLOCKCONFIGLOADER_H
#define LUABLOCKCONFIGLOADER_H
extern "C"
{
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <sstream>
#include "luna.h"
#include "ContentManager.h"
#include "global_tiles.h"
#include "../GameWindow.h"

#define lua_open() luaL_newstate()

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
