#ifndef LEVELOBJECT_H
#define LEVELOBJECT_H

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

class LevelObject
{
    public:
        LevelObject();
        LevelObject(LevelSettings __settings);
        ~LevelObject();
        void draw(SpriteBatch *_sb);
        void update(InputHandler *_ih);
    protected:
        int initLevel();
    private:
        Tile **__tiles;
        LevelSettings lvlsettings;
};

#endif // LEVELOBJECT_H
