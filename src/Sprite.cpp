#include "Sprite.h"

Sprite::Sprite(SDL_Texture *tex)
{
    texture = tex;
}

Sprite::~Sprite()
{
    //dtor
}

void Sprite::draw(SpriteBatch *_sb)
{
    if(!_sb->isDrawing())
        _sb->sbBegin();

    _sb->sbDrawTexture(texture, x, y);

    if(_sb->isDrawing())
        _sb->sbEnd();
}

void Sprite::update(InputHandler *_ih)
{
    if(_ih->InputState.keysDown == SDLK_UP)
        y--;
    if(_ih->InputState.keysDown == SDLK_RIGHT)
        x++;
    if(_ih->InputState.keysDown == SDLK_LEFT)
        x--;
    if(_ih->InputState.keysDown == SDLK_DOWN)
        y++;
}
