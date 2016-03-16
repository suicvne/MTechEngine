#include "LevelBackground.h"
#include "SpriteBatch.h"
#include "ContentManager.h"
#include "_color.h"

LevelBackground::LevelBackground()
{
    lwidth = 22 * 32;
    lheight = 19 * 32; //idk
    this->localTexture = nullptr;
}

LevelBackground::LevelBackground(int l_width, int l_height)
{
    lwidth = l_width;
    lheight = l_height;
    this->localTexture = nullptr;
}

SDL_Texture* LevelBackground::generateTextureFromWidthAndHeight(SpriteBatch* _sb, ContentManager* cm)
{
    std::cout << "Hello!" << std::endl;

    printf("%d    %d", this->width, lwidth);

    int tW, tH; //texture width and height
    //should give a bit of padding.
    //size of level + 2x where x is the width of the texture. height not worried about
    std::cout << "calculating tw" << std::endl;
    tW = (lwidth * 32) + (2 * this->width);
    std::cout << "calculating th" << std::endl;
    tH = (lheight * 32);
    printf("generated size: %d x %d\n", tW, tH);

    SDL_Texture* theTexture = SDL_CreateTexture(_sb->sbGetRenderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, tW, tH);

    SDL_Texture* oldTarget = _sb->sbGetTarget();
    _sb->sbSetRenderTarget(theTexture);

    SDL_Rect _areaToUse;
    _areaToUse.x = singleFrame->getX();
    _areaToUse.y = singleFrame->getY();
    _areaToUse.w = width;
    _areaToUse.h = height;
    for(int x = -2; x < (tW / 2); x++)
    {
        SDL_Texture *t;
        t = cm->getTexture(sheetname);

        _sb->sbDrawTextureAreaScaled(t, x * tH, tH, _areaToUse, 2.0f);
    }

    _sb->sbSetRenderTarget(oldTarget);

    return theTexture; //for now
}

LevelBackground::~LevelBackground()
{
    delete singleFrame;
}

void LevelBackground::draw(SpriteBatch* sb, ContentManager* cm)
{
    backgroundTileX(sb, cm, nullptr);
}

void LevelBackground::draw(SpriteBatch *_sb, ContentManager *cm, SDL_Rect* area)
{
    //std::cout << "ayy lmao" << std::endl;
    /*if(this->localTexture == nullptr)
    {
        std::cout << "nullcheck worked?!" << std::endl;
        localTexture = generateTextureFromWidthAndHeight(_sb, cm);
    }
    SDL_Rect massiveAreaForTesting;
    massiveAreaForTesting.w = 3000;
    massiveAreaForTesting.h = 3000;
    massiveAreaForTesting.x = 0;
    massiveAreaForTesting.y = 0;
    _sb->sbDrawTextureArea(this->localTexture, 0, 0, massiveAreaForTesting);*/
    backgroundTileX(_sb, cm, area);
}

void LevelBackground::backgroundTile(SpriteBatch* sb, ContentManager* cm, SDL_Rect* area)
{
    SDL_Rect _areaToUse;
    if(area == nullptr)
    {
        _areaToUse.x = singleFrame->getX();
        _areaToUse.y = singleFrame->getY();
        _areaToUse.w = width;
        _areaToUse.h = height;
    }
    else
        _areaToUse = *area;

    for(int x = 0; x < lwidth / 2; x++) //give some x padding
    {
        for(int y = 0; y < lheight / 2; y++)
        {
            SDL_Texture *t;
            t = cm->getTexture(sheetname);

            sb->sbDrawTextureAreaScaled(t, x * width, y * width, _areaToUse, 2.0f);
        }
    }
}

void LevelBackground::backgroundTileX(SpriteBatch* sb, ContentManager* cm, SDL_Rect* area)
{
    SDL_Color bgColor = backgroundColor->getAsSDLColor();

    sb->sbFillScreen(&bgColor);

    SDL_Rect _areaToUse;
    _areaToUse.x = singleFrame->getX();
    _areaToUse.y = singleFrame->getY();
    _areaToUse.w = width;
    _areaToUse.h = height;

    int bgRepeatCount = ((lwidth*32) / (width*2));


    for(int x = 0; x < bgRepeatCount + 2; x++) //give some x padding
    {
        SDL_Texture *t;
        t = cm->getTexture(sheetname);

        sb->sbDrawTextureAreaScaled(t, (x) *
                                     (width*2), 0, _areaToUse, 2.0f);
    }
}
