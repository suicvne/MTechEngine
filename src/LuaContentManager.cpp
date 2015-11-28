#include "LuaContentManager.h"

LuaContentManager::LuaContentManager(lua_State *L)
{
    realContentManager = (ContentManager*)lua_touserdata(L, 1);
}

LuaContentManager::~LuaContentManager()
{
    //dtor
}

void LuaContentManager::setObject(lua_State *L)
{
    realContentManager = (ContentManager*)lua_touserdata(L, 1);
}

int LuaContentManager::getTexture(lua_State *L)
{
    int argc = lua_gettop(L);
    if(argc == 0)
        return 0;
    if (argc > 1) //require exactly 1 argument
        return 0;

    std::string textureToFind = std::string(lua_tostring(L, 1));
    SDL_Texture *fff = realContentManager->getTexture(textureToFind);

    if(fff != NULL)
    {
        lua_pushlightuserdata(L, fff);
        //delete fff; //experimental
        return 1;
    }
    return 0;
}

int LuaContentManager::addTexture(lua_State *L)
{
    int argc = lua_gettop(L);
    if(argc == 0)
        return 0;
    if(argc > 2)
        return 0;

    std::string key = std::string(lua_tostring(L, 1));
    SDL_Texture *text = (SDL_Texture*)lua_touserdata(L, 2);
    realContentManager->addTexture(key, text);


    return 0;
}
