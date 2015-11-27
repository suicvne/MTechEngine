#include "Tile.h"

Tile::Tile(std::string _sheetname)
{
    sheetName = _sheetname;

    SDL_Rect temp = {0, 0, 16, 16};
    area = temp;
}

Tile::Tile(std::string _sheetname, SDL_Rect _area)
{
    sheetName = _sheetname;
    area = _area;
}

Tile::Tile(std::string _sheetname, bool animated, int _framec, SDL_Rect *_frames[])
{
    sheetName = _sheetname;
    this->animated = animated;
    if(animated)
    {
        frameCount = _framec;
        frames = _frames;
    }
}

Tile::~Tile()
{
    delete[]frames;
}

void Tile::setPosition(int _x, int _y)
{
    x = _x;
    y = _y;
}

int Tile::getX(){return x;}
int Tile::getY(){return y;}
int Tile::getWidth(){return width;}
int Tile::getHeight(){return height;}

void Tile::update()
{
    if(animated)
    {
    }
    //TODO: update animation and such
}

