#include "TestScreen.h"

/*

//testSprite->draw(spriteBatch);
        //spriteBatch->sbDrawFont("Top kek", 0, 0, standardColors.strongRed, 3, true);

*/

TestScreen::TestScreen(ContentManager *___cm) : Screen()
{
    _cm = ___cm;
    testSprite = new Sprite(_cm->getTexture("rayquaza"));
    std::cout << "Address of contentmanager in TestScreen: 0x" << &_cm << std::endl;
}

TestScreen::~TestScreen()
{
    delete testSprite;
}

void TestScreen::draw(SpriteBatch *_sb)
{
    testSprite->draw(_sb);
}

void TestScreen::update(InputHandler *_ih)
{
    testSprite->update(_ih);
}
