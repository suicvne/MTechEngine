#ifndef LEVELOBJECT_H
#define LEVELOBJECT_H

#include <iostream>

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
        void update(InputHandler* _ih);
        void loadLevelFile(std::string levelFile);
        void saveLevelFile(std::string levelFile);
    protected:
        int initLevel();
    private:
        Tile** __tiles;
        LevelSettings lvlsettings;
        LevelBackground* background;
};

#endif // LEVELOBJECT_H
