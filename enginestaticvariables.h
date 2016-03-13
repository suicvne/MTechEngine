/**
  About {{filename}}.h/{{filename}}.cpp
  By: Mike

*/

#ifndef ENGINESTATICVARIABLES_H
#define ENGINESTATICVARIABLES_H

#include <iostream>
#include <map>
#include "Tile.h"

struct SoundMixer;
struct ScreenManager;
struct Camera2d;
struct ContentManager;
struct LevelBackground;
struct ConfigFile;

class EngineStaticVariables
{
    ///TODO: figure out unamed namespace declaration?
public:
    const static int TOTAL_TILE_COUNT;
    const static int TOTAL_BACKGROUND_COUNT;
    const static int InternalWidth;
    const static int InternalHeight;
    //Static variables
    static std::map<int, Tile*> Tilemap;
    static std::map<int, LevelBackground*> BackgroundMap;
    static SoundMixer* MainSoundMixer;
    static Camera2d* MainGameCamera;
    static ScreenManager* MainScreenManager;
    //Methods
    static Tile* GetBlockByID(int id);
    static LevelBackground* GetBackgroundByID(int id);
    static std::string GetResourcesPath();
};

#endif // ENGINESTATICVARIABLES_H
