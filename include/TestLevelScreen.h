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
        void draw(SpriteBatch *_sb);
    protected:
    private:
        LevelObject *lvl_object;
};

#endif // TESTLEVELSCREEN_H
