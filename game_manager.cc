#include "game_manager.h"
#include "framework/action.h"
#include "utils/delegate_tmpl.h"
#include "player/player.h"

GameManager::GameManager()
{
    player = Player::get_instance();
    bind(member_func(this,&GameManager::player_use_card),1);
    bind(member_func(this,&GameManager::player_add_score),2);

}

GameManager::~GameManager()
{
}

void GameManager::player_use_card(int action_data)
{
    int index = action_data;
    player->remove_hand_card(index);
    Action action;
    action.action_type = 2;
    action.action_data = 3;
    send_action(action);
}

void GameManager::player_add_score(int action_data)
{
    int point = action_data;
    player->add_score(point);
}
