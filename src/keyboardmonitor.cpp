#include "keyboardmonitor.h"

InputMonitor::InputMonitor()
{}

void InputMonitor::update(const SDL_Event &event)
{
    SDL_PumpEvents();
    int dmx, dmy; //delta mouse x & y
    SDL_GetRelativeMouseState(&dmx, &dmy);
    mouseX += dmx;
    mouseY += dmy;
    //SDL_GetMouseState(&mouseX, &mouseY);
    switch(event.type)
    {
    case SDL_KEYDOWN:
        mKeysPressed.push_back(event.key.keysym.scancode);
        break;
    case SDL_KEYUP:
        if(vectorContainsObject(event.key.keysym.scancode))
            mKeysPressed.erase(std::remove(mKeysPressed.begin(), mKeysPressed.end(), event.key.keysym.scancode), mKeysPressed.end());
        break;
    //case SDL_MOUSEMOTION: //when the mouse is moved
        //mouseX = event.motion.x; //xrel
        //mouseY = event.motion.y; //yrel
        break;
    }
}

InputMonitor::Location InputMonitor::getMouseLocation() const
{
    InputMonitor::Location location;
    location.x = mouseX;
    location.y = mouseY;
    return location;
}

bool InputMonitor::vectorContainsObject(const SDL_Scancode &k)
{
    if(std::find(mKeysPressed.begin(), mKeysPressed.end(), k) != mKeysPressed.end())
        return true;
    else return false;
}

bool InputMonitor::keyIsPressed(const SDL_Scancode k)
{
    return vectorContainsObject(k);
}

bool InputMonitor::keyIsNotPressed(const SDL_Scancode k)
{
    return !vectorContainsObject(k);
}

bool InputMonitor::keyIsTapped(const SDL_Scancode k)
{
    if(vectorContainsObject(k))
    {
        SDL_PumpEvents();
        mKeysPressed.erase(std::remove(mKeysPressed.begin(), mKeysPressed.end(), k), mKeysPressed.end());
        return true;
    }
    else
        return false;
}
