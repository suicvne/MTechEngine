#ifndef LUABLOCKCONFIGLOADER_H
#define LUABLOCKCONFIGLOADER_H
extern "C"
{
    #include <lua.h>
    #include <lualib.h>
    #include <lauxlib.h>
}
#include <iostream>
#include <string>
#include <sstream>
#include <SDL.h>
#include "luna.h"
#include "GameWindow.h"
#include "Tile.h"
#include "_vector2i.h"
#include <vector>

#define SSTR( x ) dynamic_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()

class LuaBlockConfigLoader
{
    public:
        LuaBlockConfigLoader();
        ~LuaBlockConfigLoader();
        void loadBlocks();
        void loadBackgrounds();
        void report_errors(lua_State *L, int status);
        SDL_Rect **rectArrayFromVectorArray(_vector2i **arr, int frameCount, int w, int h);
    protected:
    private:
        lua_State *L = 0;
};

#endif // LUABLOCKCONFIGLOADER_H
