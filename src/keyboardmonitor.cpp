#include "keyboardmonitor.h"

KeyboardMonitor::KeyboardMonitor()
{}

void KeyboardMonitor::update(const SDL_Event &event)
{
    SDL_PumpEvents();
    switch(event.type)
    {
    case SDL_KEYDOWN:
        mKeysPressed.push_back(event.key.keysym.scancode);
        break;
    case SDL_KEYUP:
        if(vectorContainsObject(event.key.keysym.scancode))
            mKeysPressed.erase(std::remove(mKeysPressed.begin(), mKeysPressed.end(), event.key.keysym.scancode), mKeysPressed.end());
        break;
    }
}

bool KeyboardMonitor::vectorContainsObject(const SDL_Scancode &k)
{
    if(std::find(mKeysPressed.begin(), mKeysPressed.end(), k) != mKeysPressed.end())
        return true;
    else return false;
}

bool KeyboardMonitor::keyIsPressed(const SDL_Scancode k)
{
    return vectorContainsObject(k);
}

bool KeyboardMonitor::keyIsNotPressed(const SDL_Scancode k)
{
    return !vectorContainsObject(k);
}

bool KeyboardMonitor::keyIsTapped(const SDL_Scancode k)
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
