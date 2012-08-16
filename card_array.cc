#include "card_array.h"
#include "card.h" 
#include "stddef.h" 
#include "stdio.h" 
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

//增加链表
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
    return true; 
}

bool Cards::remove(int index)     
{
    CardNode *p = get_node(index);
    //实际删除 
    p->pre->next = p->next;
    p->next->pre = p->pre; 

    if(index == (total_num-1))
    {
        tail = p->pre; 
    }
    else if(index == 0)
    {
         head = p->next;
    }
    delete p;
    p = NULL;

    total_num--; 
    return true;

}
Card* Cards::get_card(int index)           //由ID号得到元素 待改 
{     
    return get_node(index)->card;
} 

int  Cards::size()             //得到链表中卡片数
{

    return total_num;

} 

/*---------private mothed ---------------------*/
CardNode* Cards::get_node(int index)           //由ID号得到元素 待改 
{     
    CardNode *p;
    p = head;
    for (int i=0; i<index; i++)
    {
        p = p->next;
    } 
    return p; 
}

bool Cards::order()
{
    return false; 
}
/*bool Cards::Order()                                //排序
{
    CardNode *MHead;
    MHead->pre = NULL;
    CardNode *MCurrent;

    CardNode  *P = Head;


    for(int i=0;i<Cdnum;i++)
    {
       if(P->Card->Type == 0x10)
       {CardNode Temp;
        Temp =  *P;
        CardNode *M;
        M = &Temp ;
    //    MHead->next
       }
    }  */ 
//}

/*bool Cards::Insert(int ctype,int indexs)//插入链表
 {        CardNode *P;                         //寻找位置
          P=Head;

          for (int i=indexs;i>0; i--)
          {
              P=P->next;
          }


          MyCard *Card;
          Card = new MyCard;
          Card->Create(ctype);
          CardNode *PCardlst;                //制作出入元素
          PCardlst->Card = Card;
          PCardlst->index=indexs+1;



          CardNode *M;
          M=P->next;                          //实际插入
          P->next = PCardlst;
//        PCardlst->pre = P;
          PCardlst->next=M;
 //       M->pre =PCardlst;


          for (int i = 0;M->index != 0 ; i++)        //修改后面的index
          {
                     (M->index)++;
                     M=M->next ;
          }
          delete Card;

          Cdnum++;                                      //改变牌数

          return true;
  } */ 
