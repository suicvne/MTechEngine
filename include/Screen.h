#pragma once
#ifndef SCREEN_H
#define SCREEN_H
#include "SpriteBatch.h"
#include "InputHandler.h"
#include "ContentManager.h"

class Screen
{
    public:
        Screen(){}
        ~Screen(){};
        virtual void draw(SpriteBatch* _sb, ContentManager* cm) = 0;
        virtual void update(InputHandler* _ih) = 0;
    protected:
    private:
        //NOTE: use std::vector for controls when you start to implement them
};

#endif // SCREEN_H
