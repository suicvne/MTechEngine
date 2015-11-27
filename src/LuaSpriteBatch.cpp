#include "LuaSpriteBatch.h"

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
    realSpriteBatch->sbDrawFont(std::string(textToDraw), x, y, SDL_Color{0, 255, 0, 255}, scale, toUpper);

    return 0;
}
