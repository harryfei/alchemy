#ifndef GAME_MANAGER_H_H_H_
#define GAME_MANAGER_H_H_H_

#include "player/player.h"
#include "card/card_array.h"
#include "utils/sigslot.h"

class GameManager :public sigslot::has_slots<>
{
    public:
        GameManager();
        ~GameManager();
    private:
        Player *player;
        void player_use_card(int index);
        void player_add_score(int score);
        void on_player_score_added();
        void on_player_card_out();
};


#endif
