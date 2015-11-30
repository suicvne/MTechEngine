#ifndef GLOBAL_TILES_H_INCLUDED
#define GLOBAL_TILES_H_INCLUDED

#define TOTAL_TILE_COUNT 2

#include <iostream>
#include <map>
#include "Tile.h"
#include "ContentManager.h"
#include "../SpriteBatch.h"

extern std::map<int, Tile*> *Tilemap;
extern bool __updateGame;


#endif // GLOBAL_TILES_H_INCLUDED
