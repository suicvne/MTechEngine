/**
  About {{filename}}.h/{{filename}}.cpp
  By: Mike

*/

#include "enginestaticvariables.h"
#include "Camera2d.h"
#include "SoundMixer.h"
#include "Tile.h"
#include "ScreenManager.h"
#include "LevelBackground.h"

#include <SDL.h>

int EngineStaticVariables::TOTAL_TILE_COUNT = 3;
int EngineStaticVariables::TOTAL_BACKGROUND_COUNT = 1;
int EngineStaticVariables::InternalWidth = 800;
int EngineStaticVariables::InternalHeight = 600;

const int EngineStaticVariables::TargetFramerate = 60;

std::map<int, Tile*> EngineStaticVariables::Tilemap;
std::map<int, LevelBackground*> EngineStaticVariables::BackgroundMap;

SoundMixer* EngineStaticVariables::MainSoundMixer = new SoundMixer(EngineStaticVariables::GetResourcesPath());
Camera2d* EngineStaticVariables::MainGameCamera = new Camera2d(0, 0);
ScreenManager* EngineStaticVariables::MainScreenManager = new ScreenManager();

//methods
Tile* EngineStaticVariables::GetBlockByID(int id)
{
    if(id < 0)
    {
        Tile t = Tile();
        t.setBlockName("Air");
        t.setBlockSize(32, 32);
        return &t;
    }
    return Tilemap[id];
}

LevelBackground* EngineStaticVariables::GetBackgroundByID(int id)
{
    return BackgroundMap[id];
}

std::string EngineStaticVariables::GetResourcesPath()
{
    return std::string(SDL_GetBasePath() + std::string("/res"));
}
