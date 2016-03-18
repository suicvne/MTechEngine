#ifndef KEYBOARDMONITOR_H
#define KEYBOARDMONITOR_H

/**
  This class does keyboard input polling..and stuff.
  Anyway, this class should be kept in a static instance so you can access it anywhere you'd need keyboard input.
  */

#include <SDL.h>
#include <iostream>
#include <algorithm>
#include <map>
#include <vector>

class InputMonitor
{
public:
    typedef struct {
        int x, y;
    } Location;
    InputMonitor();
    void update(SDL_Event const &event);
    bool keyIsPressed(SDL_Scancode const k);
    bool keyIsNotPressed(SDL_Scancode const k);
    bool keyIsTapped(SDL_Scancode const k);
    InputMonitor::Location getMouseLocation() const;
private:
    bool vectorContainsObject(SDL_Scancode const &k);
    std::vector<SDL_Scancode> mKeysPressed;
    int mouseX = 0, mouseY = 0;
};

#endif // KEYBOARDMONITOR_H
