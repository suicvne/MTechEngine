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
}

void SoundMixer::playSoundEffect(int index)
{
    if(Mix_PlayChannel(-1, soundEffectsList[index], 0) == -1)
    {
        std::cerr << "Error playing sound effect: " << Mix_GetError() << std::endl;
    }
}

void SoundMixer::loadSound(std::string resPath)
{
    std::cout << "===BEGIN SOUND LOADING===" << std::endl;

    int counter = 1;

    std::string path(resPath);
    path.append("/sound/slide.ogg");
    Mix_Chunk *chunk = Mix_LoadWAV(path.c_str());
    if(chunk != NULL)
    {
        soundEffectsList[counter] = chunk;
        std::cout << "Added effect with index " << counter << std::endl;
    }
    counter++;

    path = std::string(resPath);
    path.append("/sound/do.ogg");
    chunk = Mix_LoadWAV(path.c_str());
    if(chunk != NULL)
    {
        soundEffectsList[counter] = chunk;
        std::cout << "Added effect with index " << counter << std::endl;
    }
    counter++;

    path = std::string(resPath);
    path.append("/sound/message.ogg");
    chunk = Mix_LoadWAV(path.c_str());
    if(chunk != NULL)
    {
        soundEffectsList[counter] = chunk;
        std::cout << "Added effect with index " << counter << std::endl;
    }
    counter++;

    std::cout << "===END SOUND LOADING===" << std::endl;
}

bool SoundMixer::loadTestFile(std::string resPath)
{
    loadSound(resPath);
    bool success = true;

    std::string test = resPath + "/music/smb-overworld.ogg";
    std::cout << "Loading from " << test.c_str() << std::endl;
    music = Mix_LoadMUS(test.c_str());
    if(music == NULL)
    {
        std::cout << "Failed to load test song! Error: " << Mix_GetError() << std::endl;
        success = false;
    }
    else
    {
        //Mix_PlayMusic(this->music, 1);
    }
    return true;
}

bool SoundMixer::init()
{
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0)
    {
        std::cerr << "SDL_mixer could not init! " << Mix_GetError() << std::endl;
        return false;
    }
    return true;
}
