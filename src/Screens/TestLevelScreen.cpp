#include "TestLevelScreen.h"
#include "InputHandler.h"
#include "SpriteBatch.h"
#include "LevelObject.h"
#include "ScreenManager.h"

#include "Camera2d.h"

#include "enginestaticvariables.h"

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

void TestLevelScreen::draw(SpriteBatch *_sb, ContentManager* cm)
{
    lvl_object->draw(_sb, cm);
}

void TestLevelScreen::update(InputHandler *_ih)
{
    if(_ih->getEvent()->key.keysym.sym == SDLK_ESCAPE)
    {
        EngineStaticVariables::MainScreenManager->pushScreen(ScreenManager::TITLESCREEN);
    }
    lvl_object->update(_ih);
}
