#pragma once
#ifndef GLOBAL_TILES_H_INCLUDED
#define GLOBAL_TILES_H_INCLUDED

#define TOTAL_TILE_COUNT 3

#include <iostream>
#include <map>
#include "Tile.h"
#include "ContentManager.h"
#include "SpriteBatch.h"

struct SoundMixer;

extern std::map<int, Tile*> Tilemap;
extern Tile *__getBlockByID(int id);
extern bool __updateGame;
extern bool __vsyncEnabled;
extern bool ______DO_QUIT;

extern int __internal_width;
extern int __internal_height;

extern SoundMixer* mainSoundMixer;

#endif // GLOBAL_TILES_H_INCLUDED
