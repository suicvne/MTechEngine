#include "TitleScreen.h"

TitleScreen::TitleScreen(ContentManager *___cm)
{
    _cm = ___cm;
}

TitleScreen::~TitleScreen()
{
    //dtor
}

void TitleScreen::draw(SpriteBatch *_sb)
{
    srand(time(NULL));
    SDL_Color randomColor {rand()%255, rand()%255, rand()%255, 255};

    _sb->sbFillScreen(&randomColor);
    drawTitleCopyrightEtc(_sb);
}

void TitleScreen::update(InputHandler *_ih)
{

}

void TitleScreen::drawTitleCopyrightEtc(SpriteBatch *_sb)
{
    SDL_Color white {255, 255, 255, 255};
    int x, y;
    _sb->sbMeasureString(&x, &y, "SDL Brothers X", 3.0f, true);

    _sb->sbDrawFont("SDL Brothers X", ((800 / 2) - (x / 2)), 40, white, 3.0f, true);
    _sb->sbDrawFont("Pre Alpha Build", 0, 600-32, white, 2.0f, false);
}
