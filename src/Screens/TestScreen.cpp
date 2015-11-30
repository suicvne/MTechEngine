#include "TestScreen.h"
#include "../GameWindow.h"
#include "LuaBlockConfigLoader.h"
/**
the luna hook ins
*/
//int LUA_makeVector2i(lua_State *L)
//{
//    _vector2i *returnVal = new _vector2i(lua_tonumber(L, 1), lua_tonumber(L, 2));
//    lua_pushlightuserdata(L, returnVal);
//    //std::cout << "Pushed vector with " << returnVal->getX() << ", " << returnVal->getY() << std::endl;
//    return 1;
//} //makes vector2i for stuff
#include "global_vars.h"

int LUA_GetBlock(lua_State *L)
{
    Tile *t = (*Tilemap)[lua_tonumber(L, 1)];
    if(t != NULL)
    {
        lua_pushlightuserdata(L, t);
        return 1;
    }
    else
        return 0;
}
#include "LuaSpriteBatch.h"
#include "LuaSDL_Texture.h"
#include "LuaContentManager.h"
#include "LuaBlockWrapper.h"
const char LuaSpriteBatch::className[] = "LuaSpriteBatch";
const char LuaSDL_Texture::className[] = "LuaSDL_Texture";
const char LuaContentManager::className[] = "LuaContentManager";
const char LuaBlockWrapper::className[] = "LuaBlockWrapper";
#define method(class, name) {#name, &class::name}
Luna<LuaSpriteBatch>::RegType LuaSpriteBatch::methods[] = {
    method(LuaSpriteBatch, drawTextToScreen),
    method(LuaSpriteBatch, loadTexture),
    method(LuaSpriteBatch, drawTextureToScreen),
    method(LuaSpriteBatch, drawTextureToScreenScaled),
    {0, 0}
};
Luna<LuaContentManager>::RegType LuaContentManager::methods[] = {
    method(LuaContentManager, addTexture),
    method(LuaContentManager, getTexture),
    {0, 0}
};
Luna<LuaSDL_Texture>::RegType LuaSDL_Texture::methods[] = {
    {0, 0}
};
Luna<LuaBlockWrapper>::RegType LuaBlockWrapper::methods[] = {
    method(LuaBlockWrapper, getWorldX),
    method(LuaBlockWrapper, getWorldY),
    method(LuaBlockWrapper, getBlockName),
    method(LuaBlockWrapper, setWorldX),
    method(LuaBlockWrapper, setWorldY),
    method(LuaBlockWrapper, drawBlockToScreen),
    method(LuaBlockWrapper, setCurrentBlockFrame),
    method(LuaBlockWrapper, getBlockUpdateInterval),
    method(LuaBlockWrapper, getTotalFrames),
    {0, 0}
};

TestScreen::TestScreen(ContentManager &___cm) : Screen()
{
    doQuit = false;
    std::cout << "Address of contentmanager arg in TestScreen: " << &___cm << std::endl;
    _cm = &___cm;

    //std::cout << "Address of contentmanager in TestScreen: " << _cm << std::endl;
    L = lua_open();
    luaL_openlibs(L);
}

TestScreen::~TestScreen()
{
    delete L;
}

bool doneInit = false;

void TestScreen::finalInitLua()
{
    Luna<LuaSpriteBatch>::Register(L);
    Luna<LuaContentManager>::Register(L);
    Luna<LuaSDL_Texture>::Register(L);
    Luna<LuaBlockWrapper>::Register(L);

    luaL_openlibs(L);
    //lua_register(L, "MakeVector2i", LUA_makeVector2i);
    lua_register(L, "BlockByID", LUA_GetBlock);

    lua_pushlightuserdata(L, (void*)_localSb);
    lua_setglobal(L, "sprBatch");

    lua_pushlightuserdata(L, (void*)_cm);
    lua_setglobal(L, "mainContentManager");

    doneInit = true;

    std::string path(GameWindow::getResourcePath(""));
    path.append("test.lua");
    std::cout << "Script from: " << path << std::endl;

    s = luaL_loadfile(L, path.c_str());
    if(s != 0)
    {
        report_errors(L, s);
        std::cout << "Obeying Lua script load rules and exiting" << std::endl;
        doQuit = true;
    }
        //std::cerr << "Couldn't load test.lua!" << std::endl;
    lua_pcall(L, 0, LUA_MULTRET, 0);
}

void TestScreen::onLoopFunction()
{
    lua_getglobal(L, "onLoop");
    //State, arg count, result count, ?
    if(lua_pcall(L, 0, 0, 0) != 0)
    {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "onLoop Error", lua_tostring(L, -1), NULL);
        lua_pop(L, 1);

        doQuit = true;
    }
}

void TestScreen::onUpdateFunction()
{
    lua_getglobal(L, "onUpdate");

    if(lua_pcall(L, 0, 0, 0) != 0)
    {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "onUpdate Error", lua_tostring(L, -1), NULL);
        //std::cerr << "onUpdate error: " << lua_tostring(L, -1) << std::endl;
        lua_pop(L, 1);

        doQuit = true;
    }
}

void TestScreen::report_errors(lua_State *L, int status)
{
    if (status != 0)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "General Lua Error", lua_tostring(L, -1), NULL);
		lua_pop(L, 1); //remove error message

		doQuit = true;
	}
}

void TestScreen::draw(SpriteBatch *_sb)
{
    _localSb = _sb;
    if(!doneInit)
        finalInitLua();
    onLoopFunction();

    report_errors(L, s);
    //_sb->sbDrawFont("f CPP", 0, 0, clr.strongGreen, float(3), true);
}

void TestScreen::update(InputHandler *_ih)
{
    //_ih->update();
    onUpdateFunction();
}
