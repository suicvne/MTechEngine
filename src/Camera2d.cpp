#include "Camera2d.h"

Camera2d::Camera2d()
{
    CamX = 0;
    CamY = 0;
}

Camera2d::Camera2d(float x, float y)
{
    CamX = x;
    CamY = y;
}

float Camera2d::getCameraX()
{
    return CamX;
}

float Camera2d::getCameraY()
{
    return CamY;
}

float Camera2d::setCameraPosition(float __x, float __y)
{
    CamX = __x;
    CamY = __y;
}

float Camera2d::setCameraX(float __x)
{
    CamX = __x;
}

float Camera2d::setCameraY(float __y)
{
    CamY = __y;
}

Camera2d::~Camera2d()
{
    //dtor
}
