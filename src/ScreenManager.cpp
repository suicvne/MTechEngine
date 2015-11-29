#include "ScreenManager.h"

ScreenManager::ScreenManager(ContentManager &__cm)
{
    //std::cout << "addr_of contentManager (screenManager init): " << &__cm << std::endl;
    //std::cout << "texture: " << __cm.getTexture("r") << std::endl << std::endl;
    testScreen = new TestScreen(__cm);
}

ScreenManager::~ScreenManager()
{
    delete testScreen;
}

TestScreen *ScreenManager::getTestScreen()
{
    return testScreen;
}

void ScreenManager::update(InputHandler *_ih)
{
    switch(CurrentScreen)
    {
case TESTSCREEN:
    testScreen->update(_ih);
    break;
    }
}

void ScreenManager::draw(SpriteBatch *_sb)
{
    _sb->sbBegin();
    switch(CurrentScreen)
    {
    case TESTSCREEN:
        testScreen->draw(_sb);
        break;
    }
    _sb->sbEnd();
}

void ScreenManager::pushScreen(ScreensEnum scr)
{
    CurrentScreen = scr;
}
