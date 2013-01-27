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

GameManager::GameManager()
{
    init_player();
    init_lua();
}

GameManager::~GameManager()
{
}

void GameManager::init_player()
{
    player = Player::get_instance();

    player->signal_card_out.connect(this,&GameManager::on_player_card_out);
    player->signal_score_added.connect(this,&GameManager::on_player_score_added);

}
void GameManager::init_lua()
{
    lua_state = luaL_newstate();
    luaL_openlibs(lua_state);
    lua_register(lua_state,"lua_log",lua_log);
    lua_register(lua_state,"add_score",lua_score_add);

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


//void GameManager::load_card_script(std::string script_name)
//{
   //std::string path = get_script_path(script_name);

//}
void GameManager::on_player_card_out(int id,std::string script_name)
{
    std::cout << script_name << std::endl;

    std::string path = get_script_path(script_name);

    luaL_dofile(lua_state, path.c_str());

    //lua_getglobal(lua_state, "id");
    //int card_id = luaL_checkint(lua_state,1);
    //std::stringstream function_name_buff;
    //function_name_buff <<"card_"<< card_id <<".test";
    //std::string function_name = function_name_buff.str();

    lua_getglobal(lua_state, "card1");
    lua_getfield(lua_state,-1,"condition");
    lua_pcall(lua_state,0,1,0);

    bool condition = lua_toboolean(lua_state,-1);
    printf("%d\n",condition);

    if(condition)
    {
        lua_getglobal(lua_state, "card1");
        lua_getfield(lua_state,-1,"action");
        lua_pcall(lua_state,0,0,0);
    }

}

