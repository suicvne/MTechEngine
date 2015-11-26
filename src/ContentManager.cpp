#include "ContentManager.h"

ContentManager::ContentManager()
{
    //__textureMap = new std::map<std::string, SDL_Texture*>;

}

ContentManager::~ContentManager()
{
    delete &__textureMap;
}

SDL_Texture* ContentManager::getTexture(const char* textureName)
{
    if(__textureMap.find(textureName) != __textureMap.end())
    {
        return __textureMap[textureName];
    }
    else
    {
        std::cout << "Couldn't find texture with key '" << textureName << "'!" << std::endl;
    }
    return 0;
}

void ContentManager::addTexture(const char* textureName, SDL_Texture *texture)
{
    __textureMap["kek"] = texture;
    __textureMap[textureName] = texture;
}
