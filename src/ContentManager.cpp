#include "ContentManager.h"

ContentManager::ContentManager()
{
}

ContentManager::~ContentManager()
{
    std::cout << "Destroyed content manager" << std::endl;
    //delete &__textureMap;
}

SDL_Texture* ContentManager::getTexture(std::string textureName)
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

void ContentManager::addTexture(std::string textureName, SDL_Texture *texture)
{
    __textureMap[textureName] = texture;
    std::cout << "Added texture (" << texture << ") with key " << textureName << std::endl;
}
