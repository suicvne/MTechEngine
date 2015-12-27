#pragma once
#include "global_vars.h"
#include "SoundMixer.h"
#include "ScreenManager.h"
#include "Camera2d.h"
#include "LevelBackground.h"

std::map<int, Tile*> Tilemap; //= new std::map<int, Tile*>();
std::map<int, LevelBackground*> BackgroundMap;
bool __updateGame = true;
bool __vsyncEnabled = false;
bool ______DO_QUIT = false;

Tile *__getBlockByID(int id)
{
    if(id < 0)
    {
        Tile t = Tile();
        t.setBlockName("Air");
        t.setBlockSize(32, 32);
        return &t;
    }
    return Tilemap[id];
};

LevelBackground *__getBackgroundByID(int id)
{
    if(id < 0)
    {
        /**TODO: Return a black background placeholder*/
    }
    return BackgroundMap[id];
}

int __internal_width = 800;
int __internal_height = 600;
int __STANDARD_TILE_HEIGHT = 32;
int __STANDARD_TILE_WIDTH = 32;

SoundMixer *mainSoundMixer;
ScreenManager *mainScreenManager;
Camera2d *mainGameCamera;
ContentManager *mainContentManager;
