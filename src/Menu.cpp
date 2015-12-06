#include "Menu.h"

Menu::Menu(std::string text, int _x, int _y)
{
    this->menuText = text;
    x = _x;
    y = _y;
}

Menu::~Menu()
{
    //dtor
}

void Menu::setText(std::string textToSet)
{
    menuText = textToSet;
}

void Menu::setX(int _x)
{
    x = _x;
}

void Menu::setY(int _y)
{
    y = _y;
}

int Menu::getX()
{
    return x;
}

int Menu::getY()
{
    return y;
}

std::string Menu::getText()
{
    return this->menuText;
}
