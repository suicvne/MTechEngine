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

void Camera2d::setCameraPosition(float __x, float __y)
{
    CamX = __x;
    CamY = __y;
}

void Camera2d::setCameraX(float __x)
{
    CamX = __x;
}

void Camera2d::setCameraY(float __y)
{
    CamY = __y;
}

SDL_Rect Camera2d::RectangleFromCamera()
{
    SDL_Rect cam;
    cam.x = CamX;
    cam.y = CamY;

    return cam;
}

Camera2d::~Camera2d()
{
    //dtor
}
