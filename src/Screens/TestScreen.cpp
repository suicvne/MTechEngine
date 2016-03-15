/*--------------------------------------------------

src/Screens/TestScreen.cpp

TestScreen is literally what it implies: a test screen.
The screen was mostly developed to test Lua integration in depth/test the screen system in general.

The screen executes whatever the contents of the test.lua file is located in the res/screens/test/ folder.

----------------------------------------------------*/
#include "TestScreen.h"
#include "GameWindow.h"
#include "LuaBlockConfigLoader.h"
/**
the luna hook ins
*/
#include "enginestaticvariables.h"
#include "ScreenManager.h"

int LUA_GetBlock(lua_State *L)
{
    Tile *t = new Tile();
    //*t = (*Tilemap)[lua_tonumber(L, 1)];
    *t = *(EngineStaticVariables::Tilemap[lua_tonumber(L, 1)]);
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
#include "LuaCameraWrapper.h"
const char LuaSpriteBatch::className[] = "LuaSpriteBatch";
const char LuaSDL_Texture::className[] = "LuaSDL_Texture";
const char LuaContentManager::className[] = "LuaContentManager";
const char LuaBlockWrapper::className[] = "LuaBlockWrapper";
const char LuaCameraWrapper::className[] = "LuaCameraWrapper";
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
Luna<LuaCameraWrapper>::RegType LuaCameraWrapper::methods[] = {
    method(LuaCameraWrapper, getCameraX),
    method(LuaCameraWrapper, getCameraY),
    method(LuaCameraWrapper, setCameraX),
    method(LuaCameraWrapper, setCameraY),
    method(LuaCameraWrapper, setCameraPosition),
    {0, 0}
};

TestScreen::TestScreen(ContentManager *___cm) : Screen()
{
    doQuit = false;
    _cm = ___cm;
}

bool doneInit = false;
TestScreen::~TestScreen()
{
    //free(L);
    if(doneInit)
        delete L;
}

void TestScreen::finalInitLua()
{
    L = lua_open();
    luaL_openlibs(L);

    Luna<LuaSpriteBatch>::Register(L);
    Luna<LuaContentManager>::Register(L);
    Luna<LuaSDL_Texture>::Register(L);
    Luna<LuaBlockWrapper>::Register(L);
    Luna<LuaCameraWrapper>::Register(L);

    luaL_openlibs(L);
    //lua_register(L, "MakeVector2i", LUA_makeVector2i);
    lua_register(L, "BlockByID", LUA_GetBlock);

    lua_pushlightuserdata(L, (void*)_localSb);
    lua_setglobal(L, "sprBatch");

    /*lua_pushlightuserdata(L, (void*)_cm);
    lua_setglobal(L, "mainContentManager");*/

    lua_pushlightuserdata(L, (void*)EngineStaticVariables::MainGameCamera);
    lua_setglobal(L, "mainGameCamera");

    doneInit = true;

    std::string path(EngineStaticVariables::GetResourcesPath());
    path.append("screens/test/test.lua");
    std::cout << "Script from: " << path << std::endl;

    s = luaL_loadfile(L, path.c_str());
    if(s != 0)
    {
        report_errors(L, s);
        std::cout << "Obeying Lua script load rules and exiting" << std::endl;
        doQuit = true;
    }
        //std::cerr << "Couldn't load test.lua!" << std::endl;
    lua_pcall(L, 0, LUA_MULTRET, 0); //apparently necessary to initialize the initial globals
    onLoadFunction();
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
    if(lua_isnil(L, -1))
    {
        std::cout << "No onUpdate function" << std::endl;
    }
    else if(lua_pcall(L, 0, 0, 0) != 0)
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

void TestScreen::onInputFunction(SDL_Keycode keycode)
{
    lua_getglobal(L, "onKeyDown");
    lua_pushnumber(L, (int)keycode);
    if(lua_isnil(L, -1))
    {
        std::cout << "No onKeyDown function" << std::endl;
    }
    else if(lua_pcall(L, 1, 0, 0) != 0)
    {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "onKeyDown Error", lua_tostring(L, -1), NULL);
        //std::cerr << "onUpdate error: " << lua_tostring(L, -1) << std::endl;
        lua_pop(L, 1);

        doQuit = true;
    }
}

void TestScreen::onLoadFunction()
{
    lua_getglobal(L, "onLoad");
    if(lua_isnil(L, -1))
    {
        std::cout << "No onLoad function" << std::endl;
    }
    else if(lua_pcall(L, 0, 0, 0) != 0)
    {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "onLoad Error", lua_tostring(L, -1), NULL);
        lua_pop(L, 1);
        doQuit = true;
    }
}

void TestScreen::update(SDL_Event const &_ih)
{
    onUpdateFunction();
    if(_ih.type == SDL_KEYDOWN) //TODO: abstract to specific type of input (instead of raw keycode, jump button, etc.."
    {
        if(_ih.key.keysym.sym == SDLK_ESCAPE)
        {
            //mainScreenManager->pushScreen(TITLESCREEN);
        }
        onInputFunction(_ih.key.keysym.sym);
    }
}
