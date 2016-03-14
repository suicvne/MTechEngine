#include "LuaSpriteBatch.h"

#include "StandardColors.h"
#include "enginestaticvariables.h"

LuaSpriteBatch::LuaSpriteBatch(lua_State *L)
{
    realSpriteBatch = (SpriteBatch*)lua_touserdata(L, 1);
}

LuaSpriteBatch::~LuaSpriteBatch()
{
    //rip
}

void LuaSpriteBatch::setObject(lua_State *L)
{
    realSpriteBatch = (SpriteBatch*)lua_touserdata(L, 1);
}

int LuaSpriteBatch::loadTexture(lua_State *L)
{
    int argc = lua_gettop(L);
    if(argc != 1)
        return 0;

    const char *fileToLoad = std::string(EngineStaticVariables::GetResourcesPath() + lua_tostring(L, 1)).c_str();
    SDL_Texture *loaded = realSpriteBatch->loadTexture(fileToLoad);
    lua_pushlightuserdata(L, loaded);
    return 1;
}

int LuaSpriteBatch::drawTextureToScreen(lua_State *L)
{
    //void SpriteBatch::sbDrawTexture(SDL_Texture *tex, int x, int y)
    int argc = lua_gettop(L);
    if(argc != 3)
        return 0;

    SDL_Texture *texture;
    int x, y;

    for(int n = 1; n <= argc; n++)
    {
        switch(n)
        {
        case 1:
            texture = (SDL_Texture*)lua_touserdata(L, n);
            break;
        case 2:
            x = lua_tonumber(L, n);
            break;
        case 3:
            y = lua_tonumber(L, n);
            break;
        }
    }

    realSpriteBatch->sbDrawTexture(texture, x, y);
    return 0;
}

int LuaSpriteBatch::drawTextureToScreenScaled(lua_State *L)
{
    int argc = lua_gettop(L);
    if(argc != 4)
        return 0;

    SDL_Texture *texture;
    int x, y;
    float scale;

    for(int n = 1; n <= argc; n++)
    {
        switch(n)
        {
        case 1:
            texture = (SDL_Texture*)lua_touserdata(L, n);
            break;
        case 2:
            x = lua_tonumber(L, n);
            break;
        case 3:
            y = lua_tonumber(L, n);
            break;
        case 4:
            scale = lua_tonumber(L, n);
        }
    }

    realSpriteBatch->sbDrawTextureScaled(texture, x, y, scale);
    return 0;
}

int LuaSpriteBatch::drawTextToScreen(lua_State *L)
{
    //void sbDrawFont(std::string msg, int x, int y, SDL_Color color, float scale, bool _upper);
    int argc = lua_gettop(L); //argument count
    if(argc != 5)
        return 0;

    const char *textToDraw;
    int x, y;
    float scale;
    bool toUpper;

    for(int n = 1; n <= argc; n++)
    {
        switch(n)
        {
        case 1:
            textToDraw = lua_tostring(L, n);
            break;
        case 2:
            x = lua_tonumber(L, n);
            break;
        case 3:
            y = lua_tonumber(L, n);
            break;
        case 4:
            scale = lua_tonumber(L, n);
            break;
        case 5:
            toUpper = lua_toboolean(L, n);
            break;
        case 6:
            break;
        }
    }
    //std::cout << "\ndraw text call" << std::endl;
    realSpriteBatch->sbDrawFont(std::string(textToDraw), x + 2, y + 2, StandardColors::black, scale, toUpper);
    realSpriteBatch->sbDrawFont(std::string(textToDraw), x, y, StandardColors::white, scale, toUpper);

    return 0;
}
