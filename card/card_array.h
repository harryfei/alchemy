#ifndef CARD_ARRAY_H_H_H_
#define CARD_ARRAY_H_H_H_

#include "card.h"
class CardNode        //卡牌链表
{
    public:
        Card *card;

        CardNode *next;
        CardNode *pre;
        CardNode(Card *card);
        ~CardNode();
};


/*
 * The card list oprator class
 */
class Cards
{
    private :
        CardNode* head;             //the head node
        CardNode* tail;            //the tail node
        int total_num;                   //链表项数目

        CardNode* get_node(int index);
    public :
        Cards();
        ~Cards();

        bool add(Card *card);
        bool remove(int index);
        bool insert(Card *card,int index);
        bool clear();
        bool wash();
        int size();
        Card* get_card(int index);        //由Index得到卡片

};
#endif
