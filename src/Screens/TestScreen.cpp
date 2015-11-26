#include "TestScreen.h"
#include "../GameWindow.h"

/*

//testSprite->draw(spriteBatch);
        //spriteBatch->sbDrawFont("Top kek", 0, 0, standardColors.strongRed, 3, true);

*/

static int lbDrawText(lua_State *L)
{
    int argc = lua_gettop(L); //arg count
    const char *textToPrint = "";
    bool uppercase = false;
    if(argc < 2)
    {
        return -4;
    }
    for(int n = 1; n <= argc; n++)
    {
        if(n == 1)
            textToPrint = lua_tostring(L, n);
        if(n == 2)
            uppercase = lua_toboolean(L, n);
    }
    //TestScreen::_localSb->sbDrawFont(textToPrint, 0, 0, SDL_Color{0, 255, 0, 255}, float(3), uppercase);
    std::cout << "Placeholder: " << textToPrint << " (upper: " << uppercase << ")" << std::endl;
    lua_pushnumber(L, 0);
    return 0;
}

TestScreen::TestScreen(ContentManager &___cm) : Screen()
{
    std::cout << "Address of contentmanager arg in TestScreen: " << &___cm << std::endl;
    _cm = &___cm;

    testSprite = new Sprite(_cm->getTexture("r"));
    //std::cout << "Address of contentmanager in TestScreen: " << _cm << std::endl;
    L = lua_open();
    luaL_openlibs(L);
    lua_register(L, "drawText", lbDrawText);

    std::string path(GameWindow::getResourcePath(""));
    path.append("test.lua");

    int s = luaL_loadfile(L, path.c_str());
    if(s != 0)
        std::cerr << "Couldn't load test.lua!" << std::endl;
    s = lua_pcall(L, 0, LUA_MULTRET, 0);
}

TestScreen::~TestScreen()
{
    delete testSprite;
}

void TestScreen::draw(SpriteBatch *_sb)
{
    _localSb = _sb;
    testSprite->draw(_sb);
    //_sb->sbDrawFont("f CPP", 0, 0, clr.strongGreen, float(3), true);
}

void TestScreen::update(InputHandler *_ih)
{
    testSprite->update(_ih);
}
