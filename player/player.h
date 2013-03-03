#ifndef PLAYER_H_H_H_
#define PLAYER_H_H_H_

#include "card/card_array.h"
#include "card/card.h"
#include "utils/sigslot.h"
#include "action_def.h"
#include "string"

class Player
{
    public :
        CardOut::Signal signal_card_out;
        CardOut::Signal signal_score_added;
        Win::Signal signal_win;

        int get_hand_num();
        bool add_hand_card(Card *card);
        Card *remove_hand_card(int index);
        int get_score();
        int add_score(int point);
        void init_hand();
        void win();
        Player();
        ~Player();
    private:
        Cards hand_cards;
        int health_point;
        int power_point;
        int score_point;
};
typedef Manager<Player> PlayerManager;

#endif
