#include "player.h"
#include "card/card_array.h"

Player::Player()
{
     health_point = 5;
     power_point = 3;
     score_point = 0;

     hand_cards = new Cards;
     //desk_cards = new Cards;

}
Player::~Player()
{
    delete hand_cards;
    //delete desk_cards;
}


int Player::get_hand_num()
{
    int count = hand_cards->size();
    return count;
}
