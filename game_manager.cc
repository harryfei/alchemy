#include "game_manager.h"
#include <stdio.h>
#include "framework/action.h"
#include "utils/delegate_tmpl.h"
#include "player/player.h"
#include <lua.hpp>
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

    if(luaL_loadfile(lua_state,"test.lua"))
    {
        printf("error\n");
    }
    lua_pcall(lua_state,0,0,0);

}

GameManager::~GameManager()
{
}

void GameManager::on_player_score_added()
{
}

void GameManager::on_player_card_out()
{
    lua_getglobal(lua_state, "test");
    lua_pcall(lua_state,0,0,0);

}
void GameManager::player_use_card(int action_data)
{
    int index = action_data;
    player->remove_hand_card(index);
}

void GameManager::player_add_score(int action_data)
{
    int point = action_data;
    player->add_score(point);
}
