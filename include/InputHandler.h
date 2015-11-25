#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <iostream>
#include <SDL.h>

class InputHandler
{
    public:
        struct __inputState
        {
            SDL_Keycode keysDown;
        } InputState;
        InputHandler();
        virtual ~InputHandler();
        void update();
    protected:
    private:
        SDL_Event event;
};

#endif // INPUTHANDLER_H
