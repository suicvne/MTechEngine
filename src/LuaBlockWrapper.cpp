#include "LuaBlockWrapper.h"

LuaBlockWrapper::LuaBlockWrapper(lua_State *L)
{
    actualTile = (Tile*)lua_touserdata(L, 1);
}

LuaBlockWrapper::~LuaBlockWrapper()
{
    //dtor
}

void LuaBlockWrapper::setObject(lua_State *L)
{
    actualTile = (Tile*)lua_touserdata(L, 1);
}

int LuaBlockWrapper::getWorldX(lua_State *L)
{
    lua_pushnumber(L, actualTile->getWorldX());
    return 1;
}

int LuaBlockWrapper::getWorldY(lua_State *L)
{
    lua_pushnumber(L, actualTile->getWorldY());
    return 1;
}

int LuaBlockWrapper::setWorldX(lua_State *L)
{
    actualTile->setWorldX(lua_tonumber(L, 1));
    return 0;
}

int LuaBlockWrapper::setWorldY(lua_State *L)
{
    actualTile->setWorldY(lua_tonumber(L, 1));
    return 0;
}

int LuaBlockWrapper::drawBlockToScreen(lua_State *L)
{
    //this is a bit daring
    //it will take the spritebatch as an argument and draw it at the block's internal x/y coordinate
    //it will also take the contentmanager to you know...do content manager things

    SpriteBatch *sb = (SpriteBatch*)lua_touserdata(L, 1);
    ContentManager *cm = (ContentManager*)lua_touserdata(L, 2);
    if(sb == NULL)
    {
        lua_pushstring(L, "The passed SpriteBatch was NULL!");
        lua_error(L);
        return 1;
    }
    if(cm == NULL)
    {
        lua_pushstring(L, "The passed ContentManager was NULL!");
        lua_error(L);
        return 1;
    }
    SDL_Texture *tex = cm->getTexture(actualTile->getSheetName());
    if(tex == NULL)
    {
        lua_pushstring(L, "Texture was null!");
        lua_error(L);
        return 1;
    }
    if(actualTile->getAnimated())
    {
        sb->sbDrawTextureAreaScaled(tex, actualTile->getWorldX(), actualTile->getWorldY(), actualTile->currentFrameAsRect(), 2);
    }
    else
    {
        sb->sbDrawTextureAreaScaled(tex, actualTile->getWorldX(), actualTile->getWorldY(), actualTile->areaAsRect(), 2);
    }
    return 0;
}

int LuaBlockWrapper::getBlockUpdateInterval(lua_State *L)
{

    lua_pushnumber(L, actualTile->getFrameUpdateInterval());
    return 1;
}

int LuaBlockWrapper::setCurrentBlockFrame(lua_State *L)
{
    actualTile->setCurrentFrame(lua_tonumber(L, 1));
    return 0;
}

int LuaBlockWrapper::getTotalFrames(lua_State *L)
{
    lua_pushnumber(L, actualTile->getFrameCount());
    return 1;
}

int LuaBlockWrapper::getBlockName(lua_State *L)
{
    lua_pushstring(L, actualTile->getBlockName().c_str());
    return 1;
}
