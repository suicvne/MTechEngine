#include "LuaBlockConfigLoader.h"

int LUA_makeVector2i(lua_State *L)
{
    _vector2i *returnVal = new _vector2i(lua_tonumber(L, 1), lua_tonumber(L, 2));
    lua_pushlightuserdata(L, returnVal);
    //std::cout << "Pushed vector with " << returnVal->getX() << ", " << returnVal->getY() << std::endl;
    return 1;
}

LuaBlockConfigLoader::LuaBlockConfigLoader()
{
    L = lua_open();
}

void LuaBlockConfigLoader::report_errors(lua_State *L, int status)
{
    if(status != 0)
    {
        std::cout << "BlockReadError: " << lua_tostring(L, -1) << std::endl;
        lua_pop(L, 1);
    }
}

void LuaBlockConfigLoader::loadBlocks()
{
    for(int i = 1; i <= TOTAL_TILE_COUNT; i++)
    {
        std::ostringstream __s;
        __s << GameWindow::getResourcePath("") << "blocks/block" << i << ".lua";
        std::string path(__s.str());

        int status = luaL_loadfile(L, path.c_str());
        if(status != 0)
        {
            report_errors(L, status);
            continue;
        }
        else
        {
            lua_register(L, "Vector2i", LUA_makeVector2i);

            lua_pcall(L, 0, 0, 0);

            Tile *t = new Tile();
            lua_getglobal(L, "__name");
            lua_getglobal(L, "__id");
            lua_getglobal(L, "__width");
            lua_getglobal(L, "__height");
            lua_getglobal(L, "__animated");
            lua_getglobal(L, "__sheet");
            lua_getglobal(L, "__frames");
            lua_getglobal(L, "__framecount");
            lua_getglobal(L, "__frameupdate");
            t->setBlockName(std::string(lua_tostring(L, -9)));
            t->setBlockSize(lua_tonumber(L, -7), lua_tonumber(L, -6));
            std::cout << "Block size (from lua): " << lua_tonumber(L, -7) << " x " << lua_tonumber(L, -6) <<std::endl;
            std::cout << "Block size (from Tile): " << t->getWidth() << " x " << t->getHeight() <<  std::endl;
            t->setAnimated(lua_toboolean(L, -5));
            t->setSheetName(std::string(lua_tostring(L, -4)));
            if(lua_istable(L, -3)) //assume animation frames table
            {
                int totalFrames = lua_tonumber(L, -2);
                int _frmUpdateInt = lua_tonumber(L, -1);
                //std::cout << "Total frames: " <<totalFrames << "; Update Interval: " << _frmUpdateInt <<std::endl;

                t->setFrameCount(totalFrames); //set frame count in advanced because we'll be modifying the stack soon
                t->setFrameUpdateInterval(_frmUpdateInt); //set this in advanced too

                //_vector2i *frames[totalFrames]; //temporary allocation
                std::vector<_vector2i> frames(totalFrames);

                lua_gettable(L, -3);
                int internalCounter = 0; //use the opposite of this value to offset the Lua value reader
                for(int g = 1; g <= t->getFrameCount(); g++)
                {
                    std::string key = SSTR(g); //stack is at -9
                    lua_getfield(L, -3 + -internalCounter, key.c_str()); //-10

                    _vector2i theFrame = *(_vector2i*)lua_touserdata(L, -1); //-1 is on top?
                    frames[g - 1] = theFrame;

                    internalCounter++;
                }

                t->setAnimatedFrames(frames);
                //t->setAnimatedFrames(frames);
                //delete frames; //tested safe
            }
            else //non animated
            {
                _vector2i *singleFrame = (_vector2i*)lua_touserdata(L, -3); //another temp allocation, DONT delete AFTER
                //std::cout << "Area (Directly from Lua): " << singleFrame->getX() << ", " << singleFrame->getY() << std::endl;
                t->setNonAnimatedArea(singleFrame);
                t->setAnimated(false);
                t->setFrameCount(0);
                t->setFrameUpdateInterval(0);
            }

            (*Tilemap)[i] = t;

            std::cout << "Added block-" << i << " with name '" << t->getBlockName() << "'." << " (Animated: " << t->getAnimated() << ")" << std::endl;
        }
    }
    std::cout << "All blocks initialized" << std::endl;
}

SDL_Rect **LuaBlockConfigLoader::rectArrayFromVectorArray(_vector2i **arr, int frameCount, int w, int h)
{
    SDL_Rect *rectArray[frameCount];
    for(int i = 0; i < frameCount; i++)
    {
        SDL_Rect temp;
        temp.x = arr[i]->getX();
        temp.y = arr[i]->getY();
        temp.w = w;
        temp.h = h;

        std::cout << w << ", " << h << std::endl;

        rectArray[i] = &temp;
    }

    return rectArray;
}

LuaBlockConfigLoader::~LuaBlockConfigLoader()
{
    //dtor
    lua_close(L);
}
