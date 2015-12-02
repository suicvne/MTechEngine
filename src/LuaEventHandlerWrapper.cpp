#include "LuaEventHandlerWrapper.h"

LuaEventHandlerWrapper::LuaEventHandlerWrapper(lua_State *L)
{
    actualInputHandler = (InputHandler*)lua_touserdata(L, 1);
}

LuaEventHandlerWrapper::~LuaEventHandlerWrapper()
{
    //dtor
}

void LuaEventHandlerWrapper::setObject(lua_State *L)
{
    actualInputHandler = (InputHandler*)lua_touserdata(L, 1);
}
