#ifndef LUACONTENTMANAGER_H
#define LUACONTENTMANAGER_H
extern "C"
{
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}
#include <SDL.h>
#include <SDL_image.h>
#include "luna.h"
#include "ContentManager.h"

#define lua_open() luaL_newstate()

class LuaContentManager
{
    public:
        static const char className[];
        static Luna<LuaContentManager>::RegType methods[];

        LuaContentManager(lua_State *L);
        ~LuaContentManager();
        void setObject(lua_State *L);
        int getTexture(lua_State *L);
        int addTexture(lua_State *L);
    protected:
    private:
        ContentManager *realContentManager;
};

#endif // LUACONTENTMANAGER_H
