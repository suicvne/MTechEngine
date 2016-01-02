#include "global_vars.h"
#include "SoundMixer.h"
#include "ScreenManager.h"
#include "Camera2d.h"
#include "LevelBackground.h"
#include "configfile.h"

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
ConfigFile *mainConfigFile;

std::string getResourcePath(const std::string &subDir)
{
#ifdef _WIN32
const char PATH_SEP = '\\';
#else
const char PATH_SEP = '/';
#endif
//This will hold the base resource path: Lessons/res/
//We give it static lifetime so that we'll only need to call
//SDL_GetBasePath once to get the executable path
static std::string baseRes;
if (baseRes.empty()){
    //SDL_GetBasePath will return NULL if something went wrong in retrieving the path
    char *basePath = SDL_GetBasePath();
    if (basePath){
        baseRes = basePath;
        SDL_free(basePath);
    }
    else {
        std::cerr << "Error getting resource path: " << SDL_GetError() << std::endl;
        return "";
    }
    //We replace the last bin/ with res/ to get the the resource path
    size_t pos = baseRes.rfind("bin");
    baseRes = baseRes.substr(0, pos) + "res" + PATH_SEP;
}
//If we want a specific subdirectory path in the resource directory
//append it to the base path. This would be something like Lessons/res/Lesson0
return subDir.empty() ? baseRes : baseRes + subDir + PATH_SEP;
};
