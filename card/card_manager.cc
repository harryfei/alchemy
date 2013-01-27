#include "card/card_manager.h"
#include "card/card.h"

CardManager *CardManager::get_inance()
{
    static CardManager instance;
    return  &instance;
}

void CardManager::clear()
{
    cards_map.clear();
}

void CardManager::add_card(int id,std::string script_name)
{
    Card card = Card(id,script_name);

    cards_map[id] = card;
}

Card *CardManager::fetch_card(int id)
{
    return &(cards_map[id]);
}

CardManager::CardManager()
{
}

CardManager::~CardManager()
{
}

