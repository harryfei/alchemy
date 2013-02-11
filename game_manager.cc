#include "game_manager.h"
#include <stdio.h>
#include "framework/action.h"
#include "utils/delegate_tmpl.h"
#include "player/player.h"
#include "card/card.h"
#include "trigger/trigger.h"
#include <lua.hpp>
#include <string>
#include <sstream>
#include <iostream>


int GameManager::lua_log(lua_State *l)
{
    const char *string = luaL_checkstring (l,1);
    printf("%s\n",string);
    return 0;
}

int GameManager::lua_score_add(lua_State *l)
{
    int score = luaL_checkint(l,1);
    Player::get_instance()->add_score(score);
    return 0;
}

int GameManager::trigger_new(lua_State *L)
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
    //Trigger *trigger = (Trigger *)lua_newuserdata(L, sizeof(Trigger));
    Trigger *trigger = new Trigger();
    trigger->new_lua_object(L);
    trigger->condition = condition;
    trigger->action = action;
    return 1;
}

GameManager::GameManager()
{
    init_player();
    init_lua();
}

GameManager::~GameManager()
{
    lua_close(lua_state);
}

void GameManager::init_player()
{
    player = Player::get_instance();

    player->signal_card_out.connect(this,&GameManager::on_player_card_out);
    player->signal_score_added.connect(this,&GameManager::on_player_score_added);

}
void GameManager::init_lua()
{
    static const struct luaL_Reg trigger_lib[] = {
        {"new",GameManager::trigger_new},
        {NULL,NULL}
    };
    lua_state = luaL_newstate();
    luaL_openlibs(lua_state);
    lua_register(lua_state,"lua_log",lua_log);
    lua_register(lua_state,"add_score",lua_score_add);

    register_lib(trigger_lib,"Trigger");

}
void GameManager::init_object_map()
{
    if (luaL_newmetatable(lua_state, "object_map")) {
        lua_newtable(lua_state);
        lua_pushliteral(lua_state, "kv");
        lua_setfield(lua_state, -2, "__mode");
        lua_setmetatable(lua_state, -2);
    }

}
void GameManager::register_lib(const luaL_Reg *lib, const char *lib_name)
{
	luaL_newlib(lua_state, lib);
	lua_pushstring(lua_state, "__index");
	lua_pushvalue(lua_state, -2);
	lua_rawset(lua_state, -3);
	lua_setglobal(lua_state, lib_name);

}
void GameManager::on_player_score_added()
{
}

std::string GameManager::get_script_path(std::string name)
{
    std::stringstream path_buff;
    path_buff<<"scripts/"<< name;
    return path_buff.str();
}


void GameManager::load_card_script(std::string script_name)
{
   std::string path = get_script_path(script_name);
   luaL_dofile(lua_state, path.c_str());
}

void GameManager::on_player_card_out(int id,std::string script_name)
{
    load_card_script(script_name);

    std::stringstream class_buff;
    class_buff<<"card"<< id;
    std::string class_name= class_buff.str();

    lua_getglobal(lua_state, class_name.c_str());
    lua_getfield(lua_state,-1,"trigger");

    //Trigger *trigger = (Trigger *)lua_touserdata(lua_state, -1);

    //execute_trigger(trigger);
}

void GameManager::execute_trigger(Trigger *trigger)
{
    printf("%d %d\n",trigger->action,trigger->condition);
    lua_rawgeti(lua_state, LUA_REGISTRYINDEX, trigger->condition);
    lua_pcall(lua_state,0,1,0);
    bool condition = lua_toboolean(lua_state,-1);
    if(condition)
    {
        lua_rawgeti(lua_state, LUA_REGISTRYINDEX, trigger->action);
        lua_pcall(lua_state,0,0,0);
    }

}

