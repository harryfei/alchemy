#include "game_manager.h"
#include <stdio.h>
//#include <stdlib.h>
#include "framework/action.h"
#include "utils/delegate_tmpl.h"
#include "player/player.h"
#include "card/card.h"
#include <lua.hpp>
#include <string>
#include <sstream>
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
GameManager::GameManager()
{
    player = Player::get_instance();

    player->signal_card_out.connect(this,&GameManager::on_player_card_out);
    player->signal_score_added.connect(this,&GameManager::on_player_score_added);

    lua_state = luaL_newstate();
    luaL_openlibs(lua_state);
    lua_register(lua_state,"lua_log",lua_log);
    lua_register(lua_state,"add_score",lua_score_add);

}

GameManager::~GameManager()
{
}

void GameManager::on_player_score_added()
{
}

void GameManager::on_player_card_out(int id,std::string script_name)
{
    //int index = action_data;
    //Card *card = player->remove_hand_card(0);
    //std::stringstream script_name_buff;
    //script_name_buff <<"card"<<id<<".lua";
    //std::string script_name = script_name_buff.str();
    if(luaL_loadfile(lua_state, script_name.c_str()))
    {
        printf("error\n");
    }
    lua_pcall(lua_state,0,0,0);


    lua_getglobal(lua_state, "id");
    int card_id = luaL_checkint(lua_state,1);
    std::stringstream function_name_buff;
    function_name_buff <<"card_"<< card_id <<".test";
    std::string function_name = function_name_buff.str();
    lua_getglobal(lua_state, "test");
    lua_setglobal(lua_state, function_name.c_str());
    lua_getglobal(lua_state, function_name.c_str());
    lua_pcall(lua_state,0,0,0);

}
void GameManager::player_use_card(int action_data)
{
}

void GameManager::player_add_score(int action_data)
{
    int point = action_data;
    player->add_score(point);
}
