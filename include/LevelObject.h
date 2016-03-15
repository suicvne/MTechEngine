#ifndef LEVELOBJECT_H
#define LEVELOBJECT_H

#include <iostream>
#include <vector>
#include <SDL.h>

//Will contain more in the future.
//The width and height are in blocks not pixels.
struct LevelSettings
{
    int width, height;
};

//Forward declarations
struct SpriteBatch;
struct InputHandler;
struct Tile;
struct LevelBackground;
struct ContentManager;
struct SerializationWriter;
struct SerializationReader;

class LevelObject
{
    public:
        LevelObject();
        LevelObject(LevelSettings __settings);
        ~LevelObject();
        void draw(SpriteBatch* _sb, ContentManager* cm);
        void update(SDL_Event const &_ih);
        void loadLevelFile(std::string levelFile);
        void saveLevelFile(std::string levelFile);
        void toggleLevelAreaDebug();
    protected:
        int initLevel();
    private:
        //Tile** __tiles;
        std::vector<Tile*> __tiles;
        LevelSettings lvlsettings;
        LevelBackground* background;
        bool reading = false;
        bool showLevelAreaDebug = false;
};

#endif // LEVELOBJECT_H
