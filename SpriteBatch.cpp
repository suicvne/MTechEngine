#include "SpriteBatch.h"
#include "GameWindow.h"


SpriteBatch::SpriteBatch(SDL_Renderer *renderer)
{
    __renderer = renderer;
    if(TTF_Init() != 0)
    {
        std::cout << "Couldn't init SDL_ttf! " << SDL_GetError() << std::endl;
        SDL_Quit();
        return;
    }

    const std::string resPath = GameWindow::getResourcePath("") + "gamefont.ttf";

    mainGameFont = TTF_OpenFont(resPath.c_str(), 8);
    if(mainGameFont == nullptr)
    {
        std::cout << "Error loading gamefont.ttf: " << SDL_GetError() << std::endl;
    }
}

SpriteBatch::~SpriteBatch()
{}

SDL_Texture* SpriteBatch::loadTexture(const std::string &file, SDL_Renderer *ren)
{
    SDL_Texture *texture = NULL;
    texture = IMG_LoadTexture(ren, file.c_str());

    if(texture == nullptr)
    {
        std::cout << "Error loading texture: " << SDL_GetError() << std::endl;
    }

    return texture;
}

void SpriteBatch::sbBegin()
{
    if(drawingInProgress)
        throw "sbBegin already called!";
    SDL_RenderClear(__renderer);
    drawingInProgress = true;
}

void SpriteBatch::sbDrawFont(std::string msg, int x, int y, SDL_Color color, float scale, bool _upper)
{
    std::transform(msg.begin(), msg.end(), msg.begin(), _upper == true ? ::toupper : ::tolower);

    SDL_Texture *textToRender = drawFontToTexture(msg, color);
    //sbDrawTexture(textToRender, x, y);
    sbDrawTextureScaled(textToRender, x, y, scale);

    SDL_DestroyTexture(textToRender);
}

SDL_Texture *SpriteBatch::drawFontToTexture(std::string msg, SDL_Color color)
{
    if(msg == "")
        msg = " ";


    SDL_Surface *surface = TTF_RenderText_Blended(mainGameFont, msg.c_str(), color);
    if(surface == nullptr)
    {
        std::cout << "Error rendering font: " << SDL_GetError() << std::endl;
        return nullptr;
    }

    SDL_Texture *txt = SDL_CreateTextureFromSurface(__renderer, surface);
    if(txt == nullptr)
    {
        std::cout << "Error creating texture from surface: " << SDL_GetError() << std::endl;
        return nullptr;
    }

    SDL_FreeSurface(surface);
    return txt;
}

void SpriteBatch::sbDrawTexture(SDL_Texture *tex, int x, int y)
{
    if(!drawingInProgress)
        throw "sbBegin must be called.";
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;

    SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
    SDL_RenderCopy(__renderer, tex, NULL, &dst);
}


void SpriteBatch::sbDrawTextureScaled(SDL_Texture *tex, int x, int y, float scale)
{
    if(!drawingInProgress)
        throw "sbBegin must be called.";

    SDL_Rect dst;
    dst.x = x;
    dst.y = y;

    SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);

    dst.w = int(float(dst.w) * scale);
    dst.h = int(float(dst.h) * scale);

    SDL_RenderCopy(__renderer, tex, NULL, &dst);
}

void SpriteBatch::sbEnd()
{
    if(!drawingInProgress)
        throw "sbBegin never called!";
    SDL_RenderPresent(__renderer);
    drawingInProgress = false;
}
