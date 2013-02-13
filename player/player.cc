#include "player.h"
#include "card/card_array.h"
#include "card/card.h"

Player::Player()
{
    health_point = 5;
    power_point = 3;
    score_point = 0;

    CardManager *card_manager=CardManager::get_instance();
    int id = 1;
    for(id;id<=6;id++)
    {
        hand_cards.add(card_manager->fetch(id));
    }

}
Player::~Player()
{
}

Player *Player::get_instance()
{
    static Player instance;
    return &instance;
}
int Player::get_hand_num()
{
    return hand_cards.size();
}

bool Player::add_hand_card(Card *card)
{
    return hand_cards.add(card);
}

Card *Player::remove_hand_card(int index)
{
    Card *card = hand_cards.get(index);
    hand_cards.remove(index);
    signal_card_out(card->id);
    return card;
}

int Player::get_score()
{
    return score_point;
}

int Player::add_score(int point)
{
    score_point += point;
    if(score_point <0)
    {
        score_point = 0;
    }

    signal_score_added();

    return get_score();

}

