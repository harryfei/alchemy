#ifndef PLAYER_H_H_H_
#define PLAYER_H_H_H_

#include "card/card_array.h"
class Player
{
    public :
        Player();
        ~Player();

        int get_hand_num();
        bool add_hand_card();
    private:
        Cards *hand_cards;
        //Cards *desk_cards;

        int health_point;
        int power_point;
        int score_point;

};

#endif
