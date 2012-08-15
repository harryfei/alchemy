#ifndef CARD_ARRAY_H_H_H_
#define CARD_ARRAY_H_H_H_

#include "Card.h"
class CardNode        //卡牌链表
{   
    public:
        Card *card; 

        CardNode *next;
        CardNode *pre;
        
        CardNode(Card card);
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

        bool add(Card card);
        bool remove(int index);
        bool order();                             //排序
        bool clear();         //清空链表 

        int size();
        Card* get_card(int index);        //由Index得到卡片 

};
#endif
