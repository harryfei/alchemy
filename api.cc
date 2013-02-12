#include "api.h"
#include <lua.hpp>
#include <iostream>
#include "player/player.h"
#include "card/card.h"
#include "trigger/trigger.h"

int lua_log(lua_State *l)
{
    const char *string = luaL_checkstring (l,1);
    std::cout<<string<<std::endl;
    return 0;
}

int lua_score_add(lua_State *l)
{
    int score = luaL_checkint(l,1);
    Player::get_instance()->add_score(score);
    return 0;
}

int trigger_new(lua_State *L)
{
    int action,condition;
    //action
    if lua_isfunction(L, -1)
    {
        //ref will pop the object
        action = luaL_ref(L, LUA_REGISTRYINDEX);
    }
    //condition
    if lua_isfunction(L, -1)
    {
        condition = luaL_ref(L, LUA_REGISTRYINDEX);
    }
    //Trigger *trigger = new Trigger();
    TriggerManager *trigger_manager = TriggerManager::get_instance();
    int size = trigger_manager->size();
    Trigger *trigger = trigger_manager->add(size);
    trigger->new_lua_object(L);
    trigger->condition = condition;
    trigger->action = action;
    return 1;
}

void register_lib(lua_State *L,const luaL_Reg *lib, const char *lib_name)
{
	luaL_newlib(L, lib);
	lua_pushstring(L, "__index");
	lua_pushvalue(L, -2);
	lua_rawset(L, -3);
	lua_setglobal(L, lib_name);
}

void register_api(lua_State *L)
{
    static const struct luaL_Reg trigger_lib[] = {
        {"new",trigger_new},
        {NULL,NULL}
    };
    luaL_openlibs(L);
    lua_register(L,"lua_log",lua_log);
    lua_register(L,"add_score",lua_score_add);
    register_lib(L,trigger_lib,"Trigger");
}
