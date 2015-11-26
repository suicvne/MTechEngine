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

        SDL_Texture* getTexture(const char* textureName);
        void addTexture(const char*, SDL_Texture *texture);
    protected:
    private:
        std::map<const char*, SDL_Texture*> __textureMap;
};

#endif // CONTENTMANAGER_H
