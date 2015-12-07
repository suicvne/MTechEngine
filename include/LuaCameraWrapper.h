#ifndef LUACAMERAWRAPPER_H
#define LUACAMERAWRAPPER_H
extern "C"
{
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}
#include <SDL.h>
#include <SDL_image.h>
#include "luna.h"
#include "Camera2d.h"

#define lua_open() luaL_newstate()

class LuaCameraWrapper
{
    public:
        static const char className[];
        static Luna<LuaCameraWrapper>::RegType methods[];
        LuaCameraWrapper(lua_State *L);
        ~LuaCameraWrapper();
        void setObject(lua_State *L);
        int getCameraX(lua_State *L);
        int getCameraY(lua_State *L);
        int setCameraX(lua_State *L);
        int setCameraY(lua_State *L);
        int setCameraPosition(lua_State *L);
    protected:
    private:
        Camera2d *actualCamera;
};

#endif // LUACAMERAWRAPPER_H
