#PLEASE READ THIS
This is the legacy branch for MTechEngine using CodeBlocks as the IDE. I have since moved to Qt Creator as my IDE. This branch remains as a burial point to CodeBlocks who will always be remembered as a bad IDE in my eyes.

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
