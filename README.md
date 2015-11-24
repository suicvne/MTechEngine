#ifdef WIN32

#endif

#ifdef __linux

Presuming Ubuntu:

sudo apt-get install libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev g++
Include the /usr/include/SDL2 folder and reference SDL using <SDL.h>

#endif

#ifdef __APPLE__

Unknown yet, I don't have a Mac :(

#endif
