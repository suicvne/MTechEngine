#include "TestScreen.h"
#include "../GameWindow.h"
#include "LuaSpriteBatch.h"
<<<<<<< HEAD
#include "LuaSDL_Texture.h"
#include "LuaContentManager.h"
=======
>>>>>>> parent of 0b89ccb... Texture loading and drawing via lua
const char LuaSpriteBatch::className[] = "LuaSpriteBatch";
const char LuaSDL_Texture::className[] = "LuaSDL_Texture";
const char LuaContentManager::className[] = "LuaContentManager";
#define method(class, name) {#name, &class::name}
Luna<LuaSpriteBatch>::RegType LuaSpriteBatch::methods[] = {
    method(LuaSpriteBatch, drawTextToScreen),
    {0, 0}
};
Luna<LuaContentManager>::RegType LuaContentManager::methods[] = {
    method(LuaContentManager, addTexture),
    method(LuaContentManager, getTexture),
    {0, 0}
};

TestScreen::TestScreen(ContentManager &___cm) : Screen()
{
    std::cout << "Address of contentmanager arg in TestScreen: " << &___cm << std::endl;
    _cm = &___cm;

    testSprite = new Sprite(_cm->getTexture("r"));
    //std::cout << "Address of contentmanager in TestScreen: " << _cm << std::endl;
    L = lua_open();
    luaL_openlibs(L);
}

TestScreen::~TestScreen()
{
    delete testSprite;
    delete L;
}

bool doneInit = false;

void TestScreen::finalInitLua()
{
    Luna<LuaSpriteBatch>::Register(L);
    Luna<LuaContentManager>::Register(L);
    Luna<LuaSDL_Texture>::Register(L);

    lua_pushlightuserdata(L, (void*)_localSb);
    lua_setglobal(L, "sprBatch");

    lua_pushlightuserdata(L, (void*)_cm);
    lua_setglobal(L, "mainContentManager");


    doneInit = true;

    std::string path(GameWindow::getResourcePath(""));
    path.append("test.lua");

    s = luaL_loadfile(L, path.c_str());
    if(s != 0)
        std::cerr << "Couldn't load test.lua!" << std::endl;
    lua_pcall(L, 0, LUA_MULTRET, 0);
}

void TestScreen::onLoopFunction()
{
    lua_getglobal(L, "onLoop");
    //State, arg count, result count, ?
    if(lua_pcall(L, 0, 0, 0) != 0)
    {
        std::cerr << "onLoop error: " << lua_tostring(L, -1) << std::endl;
    }
}

void TestScreen::onUpdateFunction()
{
    lua_getglobal(L, "onUpdate");
    //State, arg count, result count, ?
    if(lua_pcall(L, 0, 0, 0) != 0)
    {
        std::cerr << "onUpdate error: " << lua_tostring(L, -1) << std::endl;
    }
}

void TestScreen::report_errors(lua_State *L, int status)
{
    if (status != 0)
	{
		std::cerr << "-- " << lua_tostring(L, -1) << std::endl;
		lua_pop(L, 1); //remove error message
	}
}

void TestScreen::draw(SpriteBatch *_sb)
{
    _localSb = _sb;
    testSprite->draw(_sb);
    if(!doneInit)
        finalInitLua();
    onLoopFunction();

    report_errors(L, s);
    //_sb->sbDrawFont("f CPP", 0, 0, clr.strongGreen, float(3), true);
}

void TestScreen::update(InputHandler *_ih)
{
    onUpdateFunction();
}
