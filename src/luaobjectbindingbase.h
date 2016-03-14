#ifndef LUAOBJECTBINDINGBASE_H_
#define LUAOBJECTBINDINGBASE_H_
#include <luna.h>

#ifndef method
#define method(class, name) {#name, &class::name}
#endif //method

struct lua_State;

template<class T>
class LuaCppObject
{
public:
  LuaCppObject(T objectToBind)
  {
    object = objectToBind;
  }
  LuaCppObject(T objectToBind, Luna<T>::RegType methodsForLua[]) : LuaCppObject(objectToBind)
  {
    methods = methodsForLua;
  }
  LuaCppObject(T objectToBind, Luna<T>::RegType methodsForLua[], const char classNameForLua[])
    : LuaCppObject(objectToBind, methodsForLua)
  {
    className = classNameForLua;
  }
  void registerLuaObject(lua_State *L)
  {
    if(className != nullptr && methods != nullptr)
      Luna<typeof(this)>::Register(L);
  }
  T const getObject(){return object;}
  const char* getClassName(){return &className;}

private:
  static const char className[]; //Class name in Lua space
  static Luna<T>::RegType methods[]; //methods for use in Lua
  T object;
};
#endif
