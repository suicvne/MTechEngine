#ifndef LUAEVENTHANDLERWRAPPER_H
#define LUAEVENTHANDLERWRAPPER_H
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
#include "InputHandler.h"

#define lua_open() luaL_newstate()

class LuaEventHandlerWrapper
{
    public:
        //boring
        static const char className[];
        static Luna<LuaEventHandlerWrapper>::RegType methods[];
        LuaEventHandlerWrapper(lua_State *L);
        ~LuaEventHandlerWrapper();
        void setObject(lua_State *L);
        //boring
    protected:
    private:
        InputHandler *actualInputHandler;
};

#endif // LUAEVENTHANDLERWRAPPER_H
