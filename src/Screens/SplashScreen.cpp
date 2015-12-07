#include "SplashScreen.h"
#include "global_vars.h"
#include "ScreenManager.h"

SplashScreen::SplashScreen(ContentManager *___cm)
{
    _cm = ___cm;
}

SplashScreen::~SplashScreen()
{
    //dtor
}

void SplashScreen::draw(SpriteBatch *_sb)
{
    SDL_Color white {255, 255, 255, 255};
    SDL_Texture *logo = _cm->getTexture("company_logo");
    _sb->sbFillScreen(&white);
    int x, y;
    getCenter(&x, &y, logo);
    _sb->sbDrawTextureConstant(logo, x, y);
}

void SplashScreen::getCenter(int *_x, int *_y, SDL_Texture *textureToQuery)
{
    SDL_Rect textureArea;
    SDL_QueryTexture(textureToQuery, NULL, 0, &textureArea.w, &textureArea.h);

    *_x = (800 / 2) - (textureArea.w / 2);
    *_y = (600 / 2) - (textureArea.h / 2);
}

void SplashScreen::update(InputHandler *_ih)
{
    localCounter++;
    if(localCounter >= 60)
    {
        //next = true; //next screen after 1.5 seconds
        mainScreenManager->pushScreen(TITLESCREEN);
    }
}
