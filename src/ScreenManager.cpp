#include "ScreenManager.h"

ScreenManager::ScreenManager(ContentManager &__cm)
{
    //std::cout << "addr_of contentManager (screenManager init): " << &__cm << std::endl;
    //std::cout << "texture: " << __cm.getTexture("r") << std::endl << std::endl;
    testScreen = new TestScreen(__cm);
    splash = new SplashScreen(&__cm);
    title = new TitleScreen(&__cm);
}

ScreenManager::~ScreenManager()
{
    delete testScreen;
}

TestScreen *ScreenManager::getTestScreen()
{
    return testScreen;
}

SplashScreen *ScreenManager::getSplashScreen()
{
    return splash;
}

void ScreenManager::update(InputHandler *_ih)
{
    switch(CurrentScreen)
    {
case TESTSCREEN:
    testScreen->update(_ih);
    break;
case SPLASHSCREEN:
    splash->update(_ih);
    break;
case TITLESCREEN:
    splash->update(_ih);
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
    case SPLASHSCREEN:
        splash->draw(_sb);
        break;
    case TITLESCREEN:
        title->draw(_sb);
        break;
    }
    _sb->sbEnd();
}

void ScreenManager::pushScreen(ScreensEnum scr)
{
    if(CurrentScreen == SPLASHSCREEN && scr == TESTSCREEN)
    {
        delete splash;
    }
    CurrentScreen = scr;
}
