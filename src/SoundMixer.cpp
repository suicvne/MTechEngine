#include "SoundMixer.h"

SoundMixer::SoundMixer(std::string resPath)
{
    init();
    loadTestFile(resPath);
}

SoundMixer::~SoundMixer()
{
    Mix_HaltMusic();
    Mix_FreeMusic(music);
    music = NULL;
    Mix_Quit();
}

void SoundMixer::playSong()
{
    if(Mix_PlayingMusic() == 0)
    {
        Mix_PlayMusic(music, -1);
    }
}

bool SoundMixer::loadTestFile(std::string resPath)
{
    bool success = true;

    std::string test = resPath + "/music/smb-overworld.ogg";
    std::cout << "Loading from " << test.c_str() << std::endl;
    music = Mix_LoadMUS(test.c_str());
    if(music == NULL)
    {
        std::cout << "Failed to load test song! Error: " << Mix_GetError() << std::endl;
        success = false;
    }
    return success;
}

bool SoundMixer::init()
{
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0)
    {
        std::cout << "SDL_mixer could not init! " << Mix_GetError() << std::endl;
        return false;
    }
    return true;
}
