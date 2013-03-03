#include "lua_object.h"
#include <lua.hpp>
#include <iostream>



static int index(lua_State *l)
{
    const char *key = luaL_checkstring(l,-1);
    lua_getfield(l,-2,"__id");
    int id = luaL_checkint(l,-1);
    std::cout<<key<<id<<std::endl;
    lua_pushinteger(l,id);
    return 1;
}
static int newindex(lua_State *l)
{
    const char *key = luaL_checkstring(l,-2);
    std::cout<<key<<std::endl;
    if(lua_istable(l,-3))
    {
        //will get loop error
        std::cout<<luaL_checkint(l,-1)<<std::endl;
        lua_setfield(l,-3,key);
    }
    return 0;
}

static const struct luaL_Reg lua_object_meta[] = {
    {"__index",index},
    //{"__newindex",newindex},
    {NULL,NULL}
};

LuaBase::LuaBase()
{
    lua_ref = -1;
}
LuaBase::~LuaBase()
{
}

int LuaBase::new_lua_object(lua_State *L)
{
    lua_newtable(L);
    lua_pushinteger(L,reinterpret_cast<long>(this));
    lua_setfield(L,-2,"__id");

    luaL_newmetatable(L,"Lua_Base_Meta");
    luaL_setfuncs(L,lua_object_meta,0);
    lua_pop(L,1);
    luaL_setmetatable(L,"Lua_Base_Meta");

    if(lua_istable(L,-1))
    {
        lua_ref = luaL_ref(L, LUA_REGISTRYINDEX);
    }
    lua_rawgeti(L, LUA_REGISTRYINDEX, lua_ref);

    return lua_ref;
}
