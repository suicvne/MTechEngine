#include "LuaEventHandlerWrapper.h"

LuaEventHandlerWrapper::LuaEventHandlerWrapper(lua_State *L)
{
    actualInputHandler = (SDL_Event*)lua_touserdata(L, 1);
}

LuaEventHandlerWrapper::~LuaEventHandlerWrapper()
{
    //dtor
}

void LuaEventHandlerWrapper::setObject(lua_State *L)
{
    actualInputHandler = (SDL_Event*)lua_touserdata(L, 1);
}
