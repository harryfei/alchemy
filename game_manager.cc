#include "game_manager.h"

#include "game_init.h"
#include "framework/action.h"
#include "utils/delegate_tmpl.h"
#include "player/player.h"
#include "card/card.h"
#include "trigger/trigger.h"
#include "api.h"
#include <lua.hpp>
#include <string>
#include <sstream>
#include <iostream>


GameManager::GameManager()
{
    init_lua();
    load_lua_scripts(lua_state);
    init_player();
}

GameManager::~GameManager()
{
    lua_close(lua_state);
}

void GameManager::init_player()
{
    player = Player::get_instance();
    player->init_hand();

    player->signal_card_out.connect(this,&GameManager::on_player_card_out);
    player->signal_score_added.connect(this,&GameManager::on_player_score_added);

}
void GameManager::init_lua()
{
    lua_state = luaL_newstate();
    register_api(lua_state);

}
void GameManager::on_player_score_added()
{
}

void GameManager::on_player_card_out(int id)
{

    std::stringstream class_buff;
    class_buff<<"card"<< id;
    std::string class_name= class_buff.str();

    lua_getglobal(lua_state, class_name.c_str());
    lua_getfield(lua_state,-1,"trigger");

    lua_getfield(lua_state,-1,"__id");
    int trigger_id = luaL_checkinteger(lua_state,-1);
    Trigger *trigger = (Trigger *)trigger_id;
    execute_trigger(trigger);
}

void GameManager::execute_trigger(Trigger *trigger)
{
    //std::cout<<trigger->action<<" "<<trigger->condition<<std::endl;
    lua_rawgeti(lua_state, LUA_REGISTRYINDEX, trigger->condition);
    lua_pcall(lua_state,0,1,0);
    bool condition = lua_toboolean(lua_state,-1);
    if(condition)
    {
        lua_rawgeti(lua_state, LUA_REGISTRYINDEX, trigger->action);
        lua_pcall(lua_state,0,0,0);
    }

}

