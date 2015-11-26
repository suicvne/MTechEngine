#include "TestScreen.h"

/*

//testSprite->draw(spriteBatch);
        //spriteBatch->sbDrawFont("Top kek", 0, 0, standardColors.strongRed, 3, true);

*/

TestScreen::TestScreen(ContentManager &___cm) : Screen()
{
    std::cout << "Address of contentmanager arg in TestScreen: " << &___cm << std::endl;
    _cm = &___cm;

    testSprite = new Sprite(_cm->getTexture("r"));
    //std::cout << "Address of contentmanager in TestScreen: " << _cm << std::endl;
}

TestScreen::~TestScreen()
{
    delete testSprite;
}

void TestScreen::draw(SpriteBatch *_sb)
{
    testSprite->draw(_sb);
    _sb->sbDrawFont("Fuck CPP", 0, 0, clr.strongGreen, float(3), true);
}

void TestScreen::update(InputHandler *_ih)
{
    testSprite->update(_ih);
}
