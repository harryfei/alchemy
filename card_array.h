#ifndef CARD_ARRAY_H_H_H_
#define CARD_ARRAY_H_H_H_

#include "Card.h"
class CardNode        //卡牌链表
{   
    public:
        Card *card;
        int index;                     //index   从1开始
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
        CardNode* last;            //the tail node
        int num;                   //链表项数目 
    public : 
        Cards();
        ~Cards(); 

        bool add(Card card);
        bool remove(int index);
        bool order();                             //排序
        bool clear_list();         //清空链表 
        Card* get_from_index(int indexs);        //由Index得到卡片 

        int get_num();

};
#endif
