CardNode::CardNode()
{ 
    card = new Card; 
}
CardNode::~CardNode()
{ 
    delete  card;
}
//-------------------------------Cards类
Cards::Cards()
{
    head = new CardNode; 
    last = head;

    head->next = NULL;
    head->pre = NULL; 
    head->index = 0;

    num = 0;
}
 


Cards::~Cards()
{
    if(ClearList())
    { 
        delete head; 
    } 
}
/*bool Cards::Cards_Init()                   //初始函数
 {
  //  PHead = new CardList;
      PHead->next = PHead;
      PHead->pre =  PHead;
      PHead->index =0;
      num =0 ;
      return true;
 }    */

bool Cards::clear_list()
{

    while(head->next !=NULL)
    {
        CardNode* p;
        p = head->next;
        head->next = p->next;
        delete p;
    }
    return true;
}


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





bool Cards::add(int type)          //增加链表
{

    CardNode *m = new CardNode;              //制作增加元素

    m->card->type = type;
    m->card->isSame = false;
    m->index = num+1;
    m->next = NULL; 

    CardNode *p = head;
    while(p->next!=NULL)
    {
        p=p->next;
    } 

    p->next=m;
    m->pre=p; 

    Last = m; 

    data1= head->next; 
 
    m =NULL; 
    num++;                                      //改变牌数
    return true; 
}

bool Cards::Remove(int index)           //移除链表         修改
{
    CardNode *p;
    p = head;
    for (int i=0; i<index; i++)
    {
        p = p->next;
    } 
    //实际删除 
    p->pre->next = p->next;
    p->next->pre = p->pre;
    CardNode* n=p->next;

    while (n->next != NULL)        //修改后面的index
    {
        (n->index)--;
        n=n->next ;
    } 
    (n->index)--;

    delete p;
    p = NULL;

    num--;                                       //修改牌数
    data1 = head->next; 
    return true;

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
//重排ID 
//}


Card* Cards::get_from_index(int indexs)           //由ID号得到元素 待改 
{     
    CardNode *p;
    p = head;
    for (int i=0; i<index; i++)
    {
        p = p->next;
    } 
    return P->card; 
}



int  Cards::get_num(int type)             //得到链表中卡片数
{
    if (type == 0x00)
        return num;
    else
    { 
        int result=0;
        CardNode *p=head;
        for (int i = num;i>0; i--)
        {
            if( p->card->type  == type)
            result++;
            p = p->next;
        }

        return result;

    }

}

