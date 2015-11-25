#include "InputHandler.h"

InputHandler::InputHandler()
{
}

InputHandler::~InputHandler()
{}

void InputHandler::update()
{
    while(SDL_PollEvent(&event))
    {
        InputHandler::InputState.keysDown = event.key.keysym.sym;
    }
}
