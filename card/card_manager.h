#ifndef CARD_MANAGER_H_H_H_
#define CARD_MANAGER_H_H_H_
//#include <string>
#include "card/card.h"
#include <map>

class CardManager
{
    public:
        static CardManager *get_inance();
        void clear();
        Card *fetch_card(int id);
        void add_card(int id,std::string script_name);
    private:
        CardManager();
        ~CardManager();
        std::map<int, Card> cards_map;
};

#endif
