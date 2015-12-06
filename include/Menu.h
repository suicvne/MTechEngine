#pragma once
#ifndef MENU_H
#define MENU_H
#include <string>

class Menu
{
    public:
        Menu(std::string text, int _x, int _y);
        ~Menu();
        std::string getText();
        void setText(std::string textToSet);
        int getX();
        int getY();
        void setX(int _x);
        void setY(int _y);
    private:
        std::string menuText;
        int x, y;

};

#endif // MENU_H
