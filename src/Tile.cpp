#include "Tile.h"

Tile::Tile()
{
    currentFrame = 0;
    id = 0;
}

Tile::~Tile()
{
    //dtor
}

void Tile::setId(int id)
{
    this->id = id;
}

int Tile::getId() const
{
    return this->id;
}

void Tile::update()
{
    if(animated)
    {
        currentFrame = counter / frameUpdateInterval;
        ++counter;
        if(counter / frameUpdateInterval >= frameCount - 1) //might have to add/remove minus 1
        {
            counter = 0;
        }
    }
}

void Tile::draw(SpriteBatch *spr, ContentManager *cm)
{
    if(animated)
    {
        if(cm->getTexture(sheetName) != nullptr)
            spr->sbDrawTextureAreaScaled(cm->getTexture(sheetName), worldX, worldY, currentFrameAsRect(), 2);
    }
    else
    {
        if(cm->getTexture(sheetName) != nullptr)
            spr->sbDrawTextureAreaScaled(cm->getTexture(sheetName), worldX, worldY, areaAsRect(), 2);
    }
}

/**
Getters
*/
int Tile::getWorldX()
{return worldX;}

int Tile::getWorldY()
{return worldY;}

int Tile::getWidth()
{
    return width;
}

int Tile::getHeight()
{return height;}

std::string Tile::getSheetName()
{return sheetName;}

_vector2i *Tile::getNonAnimatedArea()
{return area;}

bool Tile::getAnimated()
{return animated;}

int Tile::getFrameCount()
{return frameCount;}

int Tile::getFrameUpdateInterval()
{return frameUpdateInterval;}

int Tile::getCurrentFrame()
{return currentFrame;}

std::vector<_vector2i> Tile::getAllFrames()
{return frames;}

std::string Tile::getBlockName()
{return blockName;}

SDL_Rect Tile::areaAsRect()
{
    SDL_Rect temp;
    temp.x = area->getX();
    temp.y = area->getY();
    temp.w = width;
    temp.h = height;

    return temp;
}

SDL_Rect Tile::currentFrameAsRect()
{
    _vector2i frame = frames[currentFrame];
    SDL_Rect temp;
    temp.x = frame.getX();
    temp.y = frame.getY();
    temp.w = width;
    temp.h = height;

    return temp;
}

/**
Setters
*/
void Tile::setWorldPosition(int x, int y)
{
    worldX = x;
    worldY = y;
}
void Tile::setWorldX(int __x)
{
    worldX = __x;
}
void Tile::setWorldY(int __y)
{
    worldY = __y;
}
void Tile::setBlockSize(int w, int h)
{
    width = w;
    height = h;
}
void Tile::setSheetName(std::string _sheetname)
{
    sheetName = _sheetname;
}
void Tile::setNonAnimatedArea(_vector2i *_nanimarea)
{
    area = _nanimarea;
}
void Tile::setAnimated(bool __anim)
{
    animated = __anim;
}
void Tile::setFrameCount(int framec)
{
    frameCount = framec;
}
void Tile::setFrameUpdateInterval(int __interval)
{
    frameUpdateInterval = __interval;
}
void Tile::setCurrentFrame(int __curframe)
{
    currentFrame = __curframe;
}
void Tile::setAnimatedFrames(std::vector<_vector2i> __frames)
{
    frames = __frames;
}
void Tile::setBlockName(std::string __bn)
{
    blockName = __bn;
}
