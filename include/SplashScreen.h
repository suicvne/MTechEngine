#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H

#include "Screen.h"
#include "ContentManager.h"
#include "SpriteBatch.h"
#include "InputHandler.h"

class SplashScreen : public Screen
{
    public:
        SplashScreen(ContentManager *___cm);
        ~SplashScreen();
        void draw(SpriteBatch *_sb);
        void update(InputHandler *_ih);
    protected:
    private:
        ContentManager *_cm;
};

#endif // SPLASHSCREEN_H
