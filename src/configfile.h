/**
  About configfile.cpp/configfile.h

  This file is a convienence class for storing common properties of the engine.
  Properties stored in here include the GameName, MaxBlocks, MaxBackgrounds, etc.
  */

#ifndef CONFIGFILE_H
#define CONFIGFILE_H

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <stdexcept>


class ConfigFile
{
public:
    ConfigFile(std::string filename);
    void readFile(); //load the file.
    void saveFile(); //saves the file.
    std::string getWindowTitle(){return this->gameName;};
    int getWindowWidth(){return this->winWidth;};
    int getWindowHeight(){return this->winHeight;};
    int getWindowX(){return this->winX;};
    int getWindowY(){return this->winY;};
    bool getVsync(){return this->useVsync;};
private:
    std::string __filename; //internal filename used for quick saving later
    /**Begin Properties*/
    std::string gameName; //The name of the game, also shown on the title bar
    int MaxBlocks; //Maximum number of blocks to load
    int MaxBackgrounds; //Maximum number of backgrounds to load
    int winHeight, winWidth, winX, winY;
    bool useVsync;
    /**End properties*/
};

#endif // CONFIGFILE_H
