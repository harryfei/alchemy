#ifndef GAME_MANAGER_H_H_H_
#define GAME_MANAGER_H_H_H_

#include "framework/action.h"
#include "player/player.h"
#include "card/card_array.h"

class GameManager :public ActionExecutor
{
    public:
        GameManager();
        ~GameManager();
    private:
        Player *player;
        void player_use_card(int index);
        void player_add_score(int score);
};


#endif
