#include "TestLevelScreen.h"
#include "InputHandler.h"
#include "SpriteBatch.h"
#include "LevelObject.h"
#include "ScreenManager.h"

#include "Camera2d.h"

#include "enginestaticvariables.h"
#include "MathsStuff.h"

TestLevelScreen::TestLevelScreen()
{
    LevelSettings s;
    s.width = MathsStuff::ceiling(800 / 32);
    s.height = MathsStuff::ceiling(600 / 32) + 1;
    lvl_object = new LevelObject(s);
}

TestLevelScreen::~TestLevelScreen()
{
    delete lvl_object;
}

void TestLevelScreen::draw(SpriteBatch *_sb, ContentManager* cm)
{
    lvl_object->draw(_sb, cm);
}

void TestLevelScreen::update(SDL_Event const &_ih)
{
    const Uint8* keys = SDL_GetKeyboardState(NULL);
 //   switch (_ih.type)
 //   {
 //   case SDL_KEYDOWN:
        if(_ih.key.keysym.scancode == SDL_SCANCODE_LSHIFT)
        {this->CameraMod = 6;}
        if(keys[SDL_SCANCODE_ESCAPE])
        {
            EngineStaticVariables::MainScreenManager->pushScreen(ScreenManager::TITLESCREEN);
        }
        if(_ih.key.keysym.sym == SDLK_l)
        {
            this->lvl_object->loadLevelFile("testlevel.bin");
        }
        if(_ih.key.keysym.sym == SDLK_s)
        {
            this->lvl_object->saveLevelFile("testlevel.bin");
        }
        if(keys[SDL_SCANCODE_LEFT])
        {
            EngineStaticVariables::MainGameCamera->setCameraX(EngineStaticVariables::MainGameCamera->getCameraX() + CameraMod);
            SDL_PumpEvents();
        }
        if(keys[SDL_SCANCODE_RIGHT])
        {
            EngineStaticVariables::MainGameCamera->setCameraX(EngineStaticVariables::MainGameCamera->getCameraX() - CameraMod);
            SDL_PumpEvents();
        }
        if(keys[SDL_SCANCODE_UP])
        {
            EngineStaticVariables::MainGameCamera->setCameraY(EngineStaticVariables::MainGameCamera->getCameraY() + CameraMod);
            SDL_PumpEvents();
        }
        if(keys[SDL_SCANCODE_DOWN])
        {
            EngineStaticVariables::MainGameCamera->setCameraY(EngineStaticVariables::MainGameCamera->getCameraY() - CameraMod);
            SDL_PumpEvents();
        }

        //break;
    /*case SDL_KEYUP:
        if(_ih.key.keysym.sym == SDLK_LSHIFT)
        {
            this->CameraMod = 2;
        }
        break;*/
    //}

    lvl_object->update(_ih);
}
