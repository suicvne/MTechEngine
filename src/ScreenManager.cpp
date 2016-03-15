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
case TESTSCREEN:
    //testScreen->update(_ih);
    break;
case SPLASHSCREEN:
    splash->update(_ih);
    break;
case TITLESCREEN:
    title->update(_ih);
    break;
case TESTLEVEL:
    testLvlScreen->update(_ih);
    break;
    }
}

void ScreenManager::draw(SpriteBatch *sb, ContentManager *cm)
{
    switch(CurrentScreen)
    {
    case TESTSCREEN:
        //testScreen->draw(sb, cm);
        break;
    case SPLASHSCREEN:
        splash->draw(sb, cm);
        break;
    case TITLESCREEN:
        title->draw(sb, cm);
        break;
    case TESTLEVEL:
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
