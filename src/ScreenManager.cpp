///TODO: delet this
/// up to u to make ur own. easy enough

#include "ScreenManager.h"

ScreenManager::ScreenManager()
{
    //std::cout << "addr_of contentManager (screenManager init): " << &__cm << std::endl;
    //std::cout << "texture: " << __cm.getTexture("r") << std::endl << std::endl;
    //testScreen = new TestScreen();
    splash = new SplashScreen();
    title = new TitleScreen();
}

/**
 * @brief ScreenManager::initTestLevelScreen
 * This is to be done after loading of all backgrounds/resources.
 */
void ScreenManager::initTestLevelScreen()
{
    testLvlScreen = new TestLevelScreen();
}

ScreenManager::~ScreenManager()
{
    delete testLvlScreen;
    delete title;
}

TestScreen *ScreenManager::getTestScreen()
{
    return nullptr;
    //return testScreen;
}

SplashScreen *ScreenManager::getSplashScreen()
{
    return splash;
}

void ScreenManager::update(SDL_Event const &_ih)
{
    switch(CurrentScreen)
    {
case ScreenManager::TESTSCREEN:
    //testScreen->update(_ih);
    break;
case ScreenManager::SPLASHSCREEN:
    splash->update(_ih);
    break;
case ScreenManager::TITLESCREEN:
    title->update(_ih);
    break;
case ScreenManager::TESTLEVEL:
    testLvlScreen->update(_ih);
    break;
    }
}

void ScreenManager::draw(SpriteBatch *sb, ContentManager *cm)
{
    switch(CurrentScreen)
    {
    case ScreenManager::TESTSCREEN:
        //testScreen->draw(sb, cm);
        break;
    case ScreenManager::SPLASHSCREEN:
        splash->draw(sb, cm);
        break;
    case ScreenManager::TITLESCREEN:
        title->draw(sb, cm);
        break;
    case ScreenManager::TESTLEVEL:
        testLvlScreen->draw(sb, cm);
        break;
    }
}

void ScreenManager::pushScreen(ScreensEnum scr)
{
    if(CurrentScreen == SPLASHSCREEN && scr != SPLASHSCREEN)
    {
        delete splash; //transitioning, why keep the splash in memory?
    }
    CurrentScreen = scr;
}
