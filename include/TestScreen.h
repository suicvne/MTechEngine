#pragma once
#ifndef TESTSCREEN_H
#define TESTSCREEN_H
#include "Screen.h"
#include "Sprite.h"
#include "StandardColors.h"
extern "C"
{
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

#define lua_open() luaL_newstate()

//int lbDrawText(lua_State *L);

class TestScreen : public Screen
{
    public:
        TestScreen(ContentManager &___cm);
        ~TestScreen();
        void draw(SpriteBatch *_sb);
        void update(InputHandler *_ih);
    protected:
    private:
        SpriteBatch *_localSb;
        ContentManager *_cm;
        Sprite *testSprite;
        StandardColors clr;
        lua_State *L;
};

#endif // TESTSCREEN_H
