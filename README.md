# MTechEngine
A 2D Game Engine written in C++ with Lua scripting capabilities (heavy WIP)

# Building
##Dependencies
* Qt 5.4+ (okay, any version of Qt should work for right now as no Qt libraries are used)
* SDL2 (Win32 included)
* SDL2_image (Win32 included)
* SDL2_ttf (Win32 included)
* SDL2_mixer (Win32 included)
* Lua 5.1 (Win32 included)
* Compiler:
  * Linux: g++ that supports C++11
  * Windows: g++ that supports C++11 (if using Qt creator, use the MingW kit)
  * Mac OS X: Unknown, help pls
  
**NOTE**: On Windows, I have included all the Dlls and libs you will need. They are located in the .Libraries folder. The .pro file already includes the `LIBS +=` definition to link to these.

##Actual Building
* By GUI: load the .pro into Qt Creator and click build. Then, copy the res folder into the directory with the executable.
  * Windows: Be sure to copy all the dlls from `.Libraries/Win32/Stripped/dll` into there as well.
* By command prompt: TODO

# About Example Game
The example game will eventually just be a simple Super Mario Bros. 1 clone.
