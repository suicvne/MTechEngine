#include "LuaSDL_Texture.h"

LuaSDL_Texture::LuaSDL_Texture(lua_State *L)
{
    realTexture = (SDL_Texture*)lua_touserdata(L, 1);
}

LuaSDL_Texture::~LuaSDL_Texture()
{
    //dtor
}

void LuaSDL_Texture::setObject(lua_State *L)
{
    realTexture = (SDL_Texture*)lua_touserdata(L, 1);
}
