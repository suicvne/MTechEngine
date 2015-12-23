#include "TestLevelScreen.h"
#include "InputHandler.h"
#include "SpriteBatch.h"
#include "LevelObject.h"
#include "ScreenManager.h"
#include "global_vars.h"

TestLevelScreen::TestLevelScreen()
{
    lvl_object = new LevelObject();
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
    lvl_object->update(_ih);
}
