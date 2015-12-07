#include "LuaCameraWrapper.h"

LuaCameraWrapper::LuaCameraWrapper(lua_State *L)
{
    actualCamera = (Camera2d*)lua_touserdata(L, 1);
}

LuaCameraWrapper::~LuaCameraWrapper()
{}

void LuaCameraWrapper::setObject(lua_State *L)
{
    actualCamera = (Camera2d*)lua_touserdata(L, 1);
}

int LuaCameraWrapper::getCameraX(lua_State *L)
{
    lua_pushnumber(L, actualCamera->getCameraX());
    return 1;
}

int LuaCameraWrapper::getCameraY(lua_State *L)
{
    lua_pushnumber(L, actualCamera->getCameraY());
    return 1;
}

int LuaCameraWrapper::setCameraX(lua_State *L)
{
    actualCamera->setCameraX(lua_tonumber(L, 1));
    return 0;
}

int LuaCameraWrapper::setCameraY(lua_State *L)
{
    actualCamera->setCameraX(lua_tonumber(L, 1));
    return 0;
}

int LuaCameraWrapper::setCameraPosition(lua_State *L)
{
    actualCamera->setCameraPosition(lua_tonumber(L, 1), lua_tonumber(L, 2));
    return 0;
}
