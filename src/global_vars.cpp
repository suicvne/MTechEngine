#include "global_vars.h"


std::map<int, Tile*> Tilemap; //= new std::map<int, Tile*>();
bool __updateGame = true;
bool __vsyncEnabled = false;
Tile *__getBlockByID(int id)
{

    return Tilemap[id];
};
