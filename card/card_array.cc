#include "card/card_array.h"
#include "card/card.h"
#include <stddef.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

class CardNode        //卡牌链表
{
    public:
        Card *card;

        CardNode *next;
        CardNode *pre;
        CardNode(Card *card);
        ~CardNode();
};
CardNode::CardNode(Card *card)
{
    this->card = card;
    pre = NULL;
    next = NULL;
}
CardNode::~CardNode()
{
}
//-------------------------------Cards类
/*---------public mothed ---------------------*/
Cards::Cards()
{


    head = NULL;
    tail = head;
    total_num = 0;
}

Cards::~Cards()
{
    clear();
}

bool Cards::clear()
{
    int i = 0;
    while(i<total_num)
    {
        CardNode* p;
        p = head;
        head = head->next;
        delete p;
        i++;
    }
    total_num = 0;
    head = NULL;
    tail = NULL;
    return true;

}

bool Cards::wash()
{
    Card* card_bullet[total_num];
    CardNode *here = head;
    for(int i=0;i<total_num;i++)
    {
        card_bullet[i] = here->card;
        here = here->next;
    }

    int is_exist[total_num];
    for(int i=0;i<total_num;i++)
    {
         is_exist[i]=0;
    }

    here = head;
    srand((unsigned)time(NULL));
    for(int i=0;i<total_num;i++)
    {
        int m;
        while(1)
        {
            m = rand()%total_num;
            if(is_exist[m] == 1)
            {
                continue;
            }
            else
            {
                is_exist[m] = 1;
                break;
            }
        }

        here->card = card_bullet[m];
        here = head->next;
    }

}

bool Cards::add(Card *card)
{
    CardNode *new_node = new CardNode(card);

    if(total_num == 0)
    {
        head = new_node;
        head->pre = new_node;
        head->next = new_node;
        tail = head;
    }
    else
    {
        tail->next = new_node;
        new_node->pre = tail;
        tail = new_node;
    }

    total_num++;
    fix_index();
    return true;
}

bool Cards::remove(int index)
{
    CardNode *p = get_node(index);


    if(index == (total_num-1))
    {
        tail = p->pre;
    }
    else if(index == 0)
    {
        head = p->next;
    }
    else
    {
        p->pre->next = p->next;
        p->next->pre = p->pre;
    }


    delete p;
    p = NULL;

    total_num--;
    fix_index();
    return true;

}
Card* Cards::get(int index)
{
    return get_node(index)->card;
}

int  Cards::size()
{

    return total_num;

}
bool Cards::insert(Card *card,int index)
{
    CardNode *new_node = new CardNode(card);
    CardNode* node = get_node(index);

    CardNode* next = node->next;
    node->next = new_node;
    new_node->pre = node;
    new_node->next = next;
    next->pre = new_node;

    total_num++;
    fix_index();
    return true;
}

CardNode* Cards::get_node(int index)
{
    CardNode *p;
    p = head;
    for (int i=0; i<index; i++)
    {
        p = p->next;
    }
    return p;
}

void Cards::fix_index()
{
    if(head == NULL || tail == NULL || total_num == 0)
    {
        head=NULL;
        tail=head;
        total_num =0;
    }
}
