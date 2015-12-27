#include "TestLevelScreen.h"
#include "InputHandler.h"
#include "SpriteBatch.h"
#include "LevelObject.h"
#include "ScreenManager.h"
#include "global_vars.h"
#include "Camera2d.h"

TestLevelScreen::TestLevelScreen()
{
    LevelSettings s;
    s.width = 300;
    s.height = 19;
    lvl_object = new LevelObject(s);
}

TestLevelScreen::~TestLevelScreen()
{
    delete lvl_object;
}

void TestLevelScreen::draw(SpriteBatch *_sb)
{
    lvl_object->draw(_sb);
}

void TestLevelScreen::update(InputHandler *_ih)
{
    if(_ih->getEvent()->key.keysym.sym == SDLK_ESCAPE)
    {
        mainScreenManager->pushScreen(TITLESCREEN);
    }
    else if(_ih->getEvent()->key.keysym.sym == SDLK_RIGHT)
    {
        mainGameCamera->setCameraX(mainGameCamera->getCameraX() + -2);
    }
    lvl_object->update(_ih);
}
