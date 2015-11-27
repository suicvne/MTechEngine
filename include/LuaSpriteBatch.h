#ifndef LUASPRITEBATCH_H
#define LUASPRITEBATCH_H

/**
SpriteBatch bound to a lua object
*/
extern "C"
{
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}
#include "../SpriteBatch.h"
#include "luna.h"
#include <iostream>
#include <SDL.h>
#include "../GameWindow.h"

#define lua_open() luaL_newstate()


class LuaSpriteBatch
{
    public:
        static const char className[];
        static Luna<LuaSpriteBatch>::RegType methods[];

        LuaSpriteBatch(lua_State *L);
        ~LuaSpriteBatch();
        void setObject(lua_State *L);

        int drawTextToScreen(lua_State *L);
        int loadTexture(lua_State *L);
        int drawTextureToScreen(lua_State *L);
        int drawTextureToScreenScaled(lua_State *L);
    protected:
    private:
        SpriteBatch *realSpriteBatch;
};

#endif // LUASPRITEBATCH_H
