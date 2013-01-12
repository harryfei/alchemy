#include "player.h"
#include "card/card_array.h"
#include "card/card.h"

Player::Player()
{
     health_point = 5;
     power_point = 3;
     score_point = 0;

     Card *card1 = new Card(1,"card1.lua");
     Card *card2 = new Card(2,"card2.lua");
     Card *card3 = new Card(3,"card3.lua");
     Card *card4 = new Card(4,"card4.lua");
     Card *card5 = new Card(5,"card5.lua");
     Card *card6 = new Card(6,"card6.lua");


     hand_cards.add(card1);
     hand_cards.add(card2);
     hand_cards.add(card3);
     hand_cards.add(card4);
     hand_cards.add(card5);
     hand_cards.add(card6);
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
    signal_card_out(card->id, card->script_name);
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

