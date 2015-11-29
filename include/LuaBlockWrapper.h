#ifndef LUABLOCKWRAPPER_H
#define LUABLOCKWRAPPER_H
extern "C"
{
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}
#include <SDL.h>
#include <SDL_image.h>
#include "luna.h"
#include "Tile.h"
#include "../SpriteBatch.h"
#include "ContentManager.h"

#define lua_open() luaL_newstate()

class LuaBlockWrapper
{
    public:
        //boring
        static const char className[];
        static Luna<LuaBlockWrapper>::RegType methods[];
        LuaBlockWrapper(lua_State *L);
        ~LuaBlockWrapper();
        void setObject(lua_State *L);
        //boring
        //fun
        int getWorldX(lua_State *L);
        int getWorldY(lua_State *L);
        int setWorldX(lua_State *L);
        int setWorldY(lua_State *L);
        int getBlockName(lua_State *L);
        int drawBlockToScreen(lua_State *L);
        int getBlockUpdateInterval(lua_State *L);
        int setCurrentBlockFrame(lua_State *L);
        int getTotalFrames(lua_State *L);
        //fun
    protected:
    private:
        Tile *actualTile;
};

#endif // LUABLOCKWRAPPER_H
