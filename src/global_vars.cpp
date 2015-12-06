#pragma once
#include "global_vars.h"
#include "SoundMixer.h"

std::map<int, Tile*> Tilemap; //= new std::map<int, Tile*>();
bool __updateGame = true;
bool __vsyncEnabled = false;
bool ______DO_QUIT = false;

Tile *__getBlockByID(int id)
{
    return Tilemap[id];
};

int __internal_width = 800;
int __internal_height = 600;

SoundMixer *mainSoundMixer;
