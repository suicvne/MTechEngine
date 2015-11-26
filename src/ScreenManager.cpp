#include "ScreenManager.h"

ScreenManager::ScreenManager(ContentManager *__cm)
{
    testScreen = new TestScreen(__cm);
}

ScreenManager::~ScreenManager()
{
    //dtor
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
    switch(CurrentScreen)
    {
    case TESTSCREEN:
        testScreen->draw(_sb);
        break;
    }
}

void ScreenManager::pushScreen(ScreensEnum scr)
{
    CurrentScreen = scr;
}
