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
    protected:
    private:
        std::vector<std::string> vectorFromMessage(std::string msg);
        std::string message;
        std::vector<std::string> messageSplitToVector;
        bool shown;
        const int MAX_WIDTH = 350;
        const int MAX_HEIGHT = 250;
        const int MAX_CHAR_PER_LINE = 25;
};

#endif // MESSAGEBOX_H
