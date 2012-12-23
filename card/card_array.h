#ifndef CARD_ARRAY_H_H_H_
#define CARD_ARRAY_H_H_H_

#include "card.h"

class CardNode;
/*
 * The card list oprator class
 */
class Cards
{
    private :
        CardNode* head;             //the head node
        CardNode* tail;            //the tail node
        int total_num;

        CardNode* get_node(int index);
        void fix_index();
    public :
        Cards();
        ~Cards();

        bool add(Card *card);
        bool remove(int index);
        bool insert(Card *card,int index);
        bool clear();
        bool wash();
        int size();
        Card* get(int index);

};
#endif
