#include "game_manager.h"
#include <stdio.h>
#include "framework/action.h"
#include "utils/delegate_tmpl.h"
#include "player/player.h"

GameManager::GameManager()
{
    player = Player::get_instance();

    player->signal_card_out.connect(this,&GameManager::on_player_card_out);
    player->signal_score_added.connect(this,&GameManager::on_player_score_added);

}

GameManager::~GameManager()
{

}

void GameManager::on_player_score_added()
{
}

void GameManager::on_player_card_out()
{
    player->add_score(3);

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
