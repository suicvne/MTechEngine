/**
  About mtechapplication.h/mtechapplication.cpp
  By: Mike

  This will (eventually) be the base class that will later become individual
  MTechApplications instead of requiring direct modification of the framework.
*/

#ifndef MTECHAPPLICATION_H
#define MTECHAPPLICATION_H

#include <iostream>
#include <SDL.h>

//forward declaration
struct SpriteBatch;
struct InputHandler;
struct ContentManager;

class MTechApplication
{
public:
    virtual void LoadResources(ContentManager *cm, SpriteBatch *spriteBatch) = 0;
    virtual std::string getConfigFilePath() = 0;
    virtual void update(SDL_Event const &_ih) = 0;
    virtual void draw(SpriteBatch *spriteBatch, ContentManager *cm) = 0;
};

#endif // MTECHAPPLICATION_H
