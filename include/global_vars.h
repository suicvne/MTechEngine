/*#pragma once
#ifndef GLOBAL_TILES_H_INCLUDED
#define GLOBAL_TILES_H_INCLUDED

NOTE:
In the future, these values will be defined in an external configuration file such as an xml or ini.
Until then, you will have to manually modify these and recompile. I'm very sorry.

//#define TOTAL_TILE_COUNT 3 //Increase this for more blocks
//#define TOTAL_BACKGROUND_COUNT 1 //Increase this for more backgrounds

#include <iostream>
#include <map>
#include "Tile.h"
#include "SpriteBatch.h"

struct SoundMixer;
struct ScreenManager;
struct Camera2d;
struct ContentManager;
struct LevelBackground;
struct ConfigFile;

extern std::map<int, Tile*> Tilemap;
extern std::map<int, LevelBackground*> BackgroundMap;
extern Tile *__getBlockByID(int id);
extern LevelBackground *__getBackgroundByID(int id);
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

extern ConfigFile* mainConfigFile;

extern std::string getResourcePath(const std::string &subDir);

#endif // GLOBAL_TILES_H_INCLUDED*/
