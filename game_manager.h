#ifndef GAME_MANAGER_H_H_H_
#define GAME_MANAGER_H_H_H_

#include "player/player.h"
#include "card/card_array.h"
#include "utils/sigslot.h"
#include "trigger/trigger.h"
#include <lua.hpp>
#include <string>

class GameManager :public sigslot::has_slots<>
{
    public:
        GameManager();
        ~GameManager();
    private:
        Player *player;
        lua_State *lua_state;
        void init_lua();
        void init_player();
        void on_player_score_added(int score);
        void on_player_card_out(int id);
        void execute_trigger(Trigger *trigger);

        static int trigger_new(lua_State *l);
        static int lua_log(lua_State *l);
        static int lua_score_add(lua_State *l);
};

#endif
