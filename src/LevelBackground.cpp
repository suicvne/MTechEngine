#include "LevelBackground.h"
#include "SpriteBatch.h"
#include "ContentManager.h"
#include "_color.h"

LevelBackground::LevelBackground()
{
    lwidth = 22 * 32;
    lheight = 19 * 32; //idk
}

LevelBackground::LevelBackground(int l_width, int l_height)
{
    lwidth = l_width;
    lheight = l_height;
}

LevelBackground::~LevelBackground()
{
    delete singleFrame;
}

void LevelBackground::draw(SpriteBatch* sb, ContentManager* cm)
{
    backgroundTileX(sb, cm);
}

/*
void LevelBackground::backgroundTile(SpriteBatch *sb)
{
    SDL_Rect area;
    area.x = singleFrame->getX();
    area.y = singleFrame->getY();
    area.w = width;
    area.h = height;

    for(int x = -2; x < lwidth / 2; x++) //give some x padding
    {
        for(int y = 0; y < lheight / 2; y++)
        {
            SDL_Texture *t;
            t = mainContentManager->getTexture(sheetname);

            sb->sbDrawTextureAreaScaled(t, x * width, y * width, area, 2.0f);
        }
    }
}*/

void LevelBackground::backgroundTileX(SpriteBatch* sb, ContentManager* cm)
{
    SDL_Color bgColor = backgroundColor->getAsSDLColor();

    sb->sbFillScreen(&bgColor);

    SDL_Rect area;
    area.x = singleFrame->getX();
    area.y = singleFrame->getY();
    area.w = width;
    area.h = height;

    int bgRepeatCount = ((lwidth*32) / (width*2));

    for(int x = -2; x < bgRepeatCount + 2; x++) //give some x padding
    {
        SDL_Texture *t;
        t = cm->getTexture(sheetname);

        sb->sbDrawTextureAreaScaled(t, (x) *
                                     (width*2), 0, area, 2.0f);
    }
}
