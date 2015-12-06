#pragma once
#ifndef SOUNDMIXER_H
#define SOUNDMIXER_H
#include <SDL.h>
#include <SDL_mixer.h>
#include <iostream>
#include <string>

struct GameWindow;

class SoundMixer
{
    public:
        SoundMixer(std::string resPath);
        virtual ~SoundMixer();
        void playSong();
    protected:
    private:
        bool init();
        bool loadFile();
        bool loadTestFile(std::string resPath);
        GameWindow *gw;
        Mix_Music *music = NULL;
};

#endif // SOUNDMIXER_H
