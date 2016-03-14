#pragma once
#ifndef MESSAGEBOX_H
#define MESSAGEBOX_H
#include <string>
#include <vector>
struct SpriteBatch;
struct InputHandler;

class MessageBox
{
    public:
        MessageBox(std::string msg);
        ~MessageBox();
        void draw(SpriteBatch *_sb);
        void update(InputHandler *_ih);
        void setVisible(bool vis);
        bool getVisibility()
        {
            return showMessage;
        };
    protected:
    private:
        std::vector<std::string> vectorFromMessage();
        std::string message;
        std::vector<std::string> messageSplitToVector;
        bool soundPlayed, showMessage;
        const int MAX_WIDTH = 420;
        const int MAX_HEIGHT = 250;
        const int MAX_CHAR_PER_LINE = 25;
        int opacityMod, frameCount;
};

#endif // MESSAGEBOX_H
