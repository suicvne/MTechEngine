#ifndef CONTENTMANAGER_H
#define CONTENTMANAGER_H

#include <iostream>
#include <map>
#include <SDL.h>
#include <SDL_image.h>

class ContentManager
{
    public:
        ContentManager();
        virtual ~ContentManager();

        SDL_Texture* getTexture(std::string textureName);
        void addTexture(std::string, SDL_Texture *texture);
    protected:
    private:
        std::map<std::string, SDL_Texture*> __textureMap;
};

#endif // CONTENTMANAGER_H
