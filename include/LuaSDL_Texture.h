#ifndef LUASDL_TEXTURE_H
#define LUASDL_TEXTURE_H
/**
SDL_Texture bound to a lua object
*/
extern "C"
{
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}
#include <SDL.h>
#include <SDL_image.h>
#include "luna.h"
#include <iostream>

#define lua_open() luaL_newstate()

class LuaSDL_Texture
{
    public:
        static const char className[];
        static Luna<LuaSDL_Texture>::RegType methods[];

        LuaSDL_Texture(lua_State *L);
        ~LuaSDL_Texture();
        void setObject(lua_State *L);
        int setTexture(lua_State *L);
    protected:
    private:
        SDL_Texture *realTexture;
};

#endif // LUASDL_TEXTURE_H
