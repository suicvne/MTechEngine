#include "configfile.h"
#include "customalgorithms.h" //include this here to avoid multiple instance errors
/**
  first code file of 2016 nice
*/

//More than likely, the file will be located in 'res/game_config.cfg'
ConfigFile::ConfigFile(std::string filename)
{
    this->__filename = filename;
    //Load defaults
    this->gameName = "MTechEngine";
    this->MaxBackgrounds = 1;
    this->MaxBlocks = 3;
}

void ConfigFile::readFile()
{
    using namespace std;
    string line;
    ifstream mainInputStream(__filename);
    if(mainInputStream.is_open())
    {
        while(getline(mainInputStream, line))
        {
            //name=Super SDL Brothers X
            if(begins_with(line, std::string("#"))) //ignore comments
            {} //here for completion sake
            else if(begins_with(line, std::string("name")))
            {
                gameName = line.substr(line.find('='), line.length());
            }
            else if(begins_with(line, std::string("max_blocks")))
            {
                this->MaxBlocks = atoi(line.substr(line.find('='), line.length()).c_str());
            }
            else if(begins_with(line, std::string("max_backgrounds")))
            {
                this->MaxBackgrounds = atoi(line.substr(line.find('='), line.length()).c_str());
            }
            else if(begins_with(line, std::string("width")))
            {
                this->winWidth = atoi(line.substr(line.find('='), line.length()).c_str());
            }
            else if(begins_with(line, std::string("height")))
            {
                this->winHeight = atoi(line.substr(line.find('='), line.length()).c_str());
            }
            else if(begins_with(line, std::string("start_x")))
            {
                this->winX = atoi(line.substr(line.find('='), line.length()).c_str());
            }
            else if(begins_with(line, std::string("start_y")))
            {
                this->winY = atoi(line.substr(line.find('='), line.length()).c_str());
            }
            else if(begins_with(line, std::string("use_vsync")))
            {
                if(toLower(line) == "true")
                    this->useVsync = true;
                else
                    this->useVsync = false;
            }
        }
        mainInputStream.close();
    }
    else
        throw std::runtime_error(std::string("Failed loading config file: ") + this->__filename);
}

void ConfigFile::saveFile()
{
    std::ofstream outStream(this->__filename);
    if(outStream.is_open())
    {
        outStream << "name=" << this->gameName;
        outStream << "max_blocks=" << this->MaxBlocks;
        outStream << "max_backgrounds=" << this->MaxBackgrounds;
        outStream << "width=" << this->winWidth;
        outStream << "height=" << this->winHeight;
        outStream << "start_x=" << this->winX;
        outStream << "start_y=" << this->winY;
        outStream << "use_vsync=" << ((this->useVsync) ? "true" : "false");

        outStream.close();
    }
    else
        throw std::runtime_error(std::string("Failed writing config file: ") + this->__filename);
}
