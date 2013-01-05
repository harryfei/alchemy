#include "game_manager.h"
#include "framework/action.h"
#include "utils/delegate_tmpl.h"
#include "player/player.h"

GameManager::GameManager()
{
    player = Player::get_instance();
    bind(mem_func(this,&GameManager::player_use_card),ACTION_DISCARD);
    bind(mem_func(this,&GameManager::player_add_score),ACTION_SCORE_ADD);

}

GameManager::~GameManager()
{
}

void GameManager::player_use_card(int action_data)
{
    int index = action_data;
    player->remove_hand_card(index);
    send_action(ACTION_SCORE_ADD, 3);
}

void GameManager::player_add_score(int action_data)
{
    int point = action_data;
    player->add_score(point);
}
