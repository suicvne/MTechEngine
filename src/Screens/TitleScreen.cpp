#include "TitleScreen.h"
#include "global_vars.h"

TitleScreen::TitleScreen(ContentManager *___cm)
{
    _cm = ___cm;
    this->menuOptions.push_back(new Menu("load test world", 295, 255));

    totalOptions = menuOptions.size();
    currentSelection = 0;
}

TitleScreen::~TitleScreen()
{
}

void TitleScreen::draw(SpriteBatch *_sb)
{
    srand(time(NULL));

    SDL_Color randomColor {192, 248, 248, 255};

    _sb->sbFillScreen(&randomColor);

    SDL_Texture *bgTex = _cm->getTexture("bg_index");
    SDL_Rect texArea {5, 18, 255, 223};
    _sb->sbDrawTextureAreaScaledConstant(bgTex, 0, 0, texArea, 2.0f);
    _sb->sbDrawTextureAreaScaledConstant(bgTex, 255*2, 0, texArea, 2.0f);

    SDL_Color black{0,0,0,255};
    SDL_Rect boxArea;
    boxArea.w = 300;
    boxArea.h = 200;
    boxArea.x = ((__internal_width / 2) - (boxArea.w / 2));
    boxArea.y = ((__internal_height / 2) - (boxArea.h / 2));

    _sb->sbFillRect(&black, &boxArea);

    drawOptions(_sb);

    drawTitleCopyrightEtc(_sb);
}

void TitleScreen::drawOptions(SpriteBatch *_sb)
{
    SDL_Color white{255,255,255,255};
    for(int i = 0; i < menuOptions.size(); i++)
    {
        _sb->sbDrawFont(menuOptions[i]->getText(), menuOptions[i]->getX(), menuOptions[i]->getY(), white, 2.0f, false);
        if(i == currentSelection)
        {
            _sb->sbDrawTextureScaledConstant(_cm->getTexture("selection"), menuOptions[i]->getX() - 28, menuOptions[i]->getY(), 2.0f);
        }
    }
}

void TitleScreen::update(InputHandler *_ih)
{
    if(_ih->getEvent()->type == SDL_KEYDOWN)
    {
        if(_ih->getEvent()->key.keysym.sym == SDLK_UP)
        {
            currentSelection++;
            if(currentSelection > totalOptions)
                currentSelection = 0;
        }
        if(_ih->getEvent()->key.keysym.sym == SDLK_DOWN)
        {
            currentSelection--;
            if(currentSelection < totalOptions)
                currentSelection = (menuOptions.size() - 1);
        }
    }
}

void TitleScreen::drawTitleCopyrightEtc(SpriteBatch *_sb)
{
    SDL_Color white {255, 255, 255, 255};
    int x, y;
    _sb->sbMeasureString(&x, &y, "SDL Brothers X", 3.0f, true);

    _sb->sbDrawFont("SDL Brothers X", ((__internal_width / 2) - (x / 2)), 40, white, 3.0f, true);
    _sb->sbDrawFont("Pre Alpha Build", 0, 600-24, white, 2.0f, false);
}
