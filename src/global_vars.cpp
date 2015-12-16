#pragma once
#include "global_vars.h"
#include "SoundMixer.h"
#include "ScreenManager.h"
#include "Camera2d.h"

std::map<int, Tile*> Tilemap; //= new std::map<int, Tile*>();
bool __updateGame = true;
bool __vsyncEnabled = false;
bool ______DO_QUIT = false;

Tile *__getBlockByID(int id)
{
    if(id < 0)
        return NULL;
    return Tilemap[id];
};

int __internal_width = 800;
int __internal_height = 600;
int __STANDARD_TILE_HEIGHT = 32;
int __STANDARD_TILE_WIDTH = 32;

SoundMixer *mainSoundMixer;
ScreenManager *mainScreenManager;
Camera2d *mainGameCamera;
