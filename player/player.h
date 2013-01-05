#ifndef PLAYER_H_H_H_
#define PLAYER_H_H_H_

#include "card/card_array.h"
#include "card/card.h"
#include "utils/sigslot.h"

class Player
{
    public :
        sigslot::signal0<> signal_card_out;
        sigslot::signal0<> signal_score_added;

        int get_hand_num();
        bool add_hand_card(Card *card);
        Card *remove_hand_card(int index);
        int get_score();
        int add_score(int point);
        static Player *get_instance();
    private:
        Player();
        ~Player();
        Cards hand_cards;
        int health_point;
        int power_point;
        int score_point;

};

#endif
