/**
  About {{filename}}.h/{{filename}}.cpp
  By: Mike

*/

#ifndef ENGINESTATICVARIABLES_H
#define ENGINESTATICVARIABLES_H

#include <iostream>
#include <map>
#include "Tile.h"

class SoundMixer;
class ScreenManager;
class Camera2d;
class ContentManager;
class LevelBackground;
class ConfigFile;
class InputMonitor;

class EngineStaticVariables
{
    ///TODO: figure out unamed namespace declaration?
public:
    static int TOTAL_TILE_COUNT;
    static int TOTAL_BACKGROUND_COUNT;
    static int InternalWidth;
    static int InternalHeight;
    static bool DoQuit;
    static bool UpdateGame;
    const static int TargetFramerate;
    //Static variables
    const static Uint8* currentKeystate;
    static std::map<int, Tile*> Tilemap;
    static std::map<int, LevelBackground*> BackgroundMap;
    static SoundMixer* MainSoundMixer;
    static Camera2d* MainGameCamera;
    static ScreenManager* MainScreenManager;
    static InputMonitor* MainKeyboardInputWatcher;
    //Methods
    static Tile* GetBlockByID(int id);
    static LevelBackground* GetBackgroundByID(int id);
    static std::string GetResourcesPath();
    static Tile* airTile;
};

#endif // ENGINESTATICVARIABLES_H
