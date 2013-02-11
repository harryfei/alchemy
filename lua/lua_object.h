#ifndef LUA_OBJECT_H_H_H_
#define LUA_OBJECT_H_H_H_
#include <lua.hpp>

class LuaBase
{
    protected:
        int lua_ref;
    public:
        LuaBase();
        virtual ~LuaBase();
        int new_lua_object(lua_State *L);
};
#endif
