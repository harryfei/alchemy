#include "Card.h"

CardNode::CardNode(Card *card)
{ 
    this.card = card; 
}
CardNode::~CardNode()
{ 

}
//-------------------------------Cards类


/*---------public mothed ---------------------*/
Cards::Cards()
{
    head = NULL; 
    last = head; 
    num = 0; 
} 

Cards::~Cards()
{ 
    clear();
    
}

bool Cards::clear()
{ 
    while(head!=NULL)
    {
        CardNode* p;
        p = head;
        head = head->next;
        delete p;
    } 
    head = NULL;
    return true;
} 

//增加链表
bool Cards::add(Card *card)         
{
    CardNode *new_node = new CardNord(card); 

    tail->next = new_node;
    new_node->pre = tail;
    tail = new_node;

    total_num++; 
    return true; 
}

bool Cards::remove(int index)     
{
    CardNode *p = get_node(index);
    //实际删除 
    p->pre->next = p->next;
    p->next->pre = p->pre; 

    delete p;
    p = NULL; 
    num--; 

    return true;

}
Card* Cards::get_from_index(int index)           //由ID号得到元素 待改 
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
