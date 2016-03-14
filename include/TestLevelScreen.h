#ifndef TESTLEVELSCREEN_H
#define TESTLEVELSCREEN_H

#include "Screen.h"

struct LevelObject;
struct InputHandler;
struct SpriteBatch;

class TestLevelScreen : public Screen
{
    public:
        TestLevelScreen();
        ~TestLevelScreen();
        void update(InputHandler *_ih);
        void draw(SpriteBatch *_sb, ContentManager* cm);
    protected:
    private:
        LevelObject *lvl_object;
        int CameraMod = 2; //rate at which the camera moves
};

#endif // TESTLEVELSCREEN_H
