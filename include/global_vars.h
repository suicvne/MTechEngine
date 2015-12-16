#pragma once
#ifndef GLOBAL_TILES_H_INCLUDED
#define GLOBAL_TILES_H_INCLUDED

#define TOTAL_TILE_COUNT 3 //Increase this for more blocks

#include <iostream>
#include <map>
#include "Tile.h"
#include "SpriteBatch.h"

struct SoundMixer;
struct ScreenManager;
struct Camera2d;
struct ContentManager;

extern std::map<int, Tile*> Tilemap;
extern Tile *__getBlockByID(int id);
extern bool __updateGame;
extern bool __vsyncEnabled;
extern bool ______DO_QUIT;

extern int __internal_width;
extern int __internal_height;
extern int __STANDARD_TILE_HEIGHT;
extern int __STANDARD_TILE_WIDTH;

extern SoundMixer* mainSoundMixer;
extern ScreenManager* mainScreenManager;
extern Camera2d* mainGameCamera;
extern ContentManager* mainContentManager;

#endif // GLOBAL_TILES_H_INCLUDED
