#include "InputHandler.h"

InputHandler::InputHandler()
{
}

InputHandler::~InputHandler()
{}

SDL_Event *InputHandler::getEvent()
{
    return &event;
}

void InputHandler::update()
{
    SDL_PollEvent(&event);
    //while(SDL_PollEvent(&event))
    //{
    //    InputHandler::InputState.keysDown = event.key.keysym.sym;
    //}
}
