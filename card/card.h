#ifndef CARD_H_H_H_
#define CARD_H_H_H_

#include <string>
#include "lua/lua_object.h"
#include "base/manager_tmpl.h"

class Card:public LuaBase
{
    public:
        int id;

        Card(int id);
        Card();
};

typedef Manager<Card> CardManager;
#endif
