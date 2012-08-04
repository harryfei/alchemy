#ifndef CARD_ARRAY_H_H_H_
#define CARD_ARRAY_H_H_H_
class CardNode        //卡牌链表
{   
    public:
        Card *card;
        int index;                     //index   从1开始
        CardNode *next;
        CardNode *pre;
        CardNode();
        ~CardNode(); 
};

class Cards              //卡牌链表增强,操作
{ 
    private :
        CardNode* head;             //头结点       头结点不存数据
        CardNode* data1;           //数据开始节点
        CardNode* last;            //尾节点
        int num;                   //链表项数目 
    public : 

        Cards();
        ~Cards();
          //bool Cards_Init();      //初始函数
        bool clear_list();         //清空链表 
         // bool Insert(int ctype,int indexs);      //在index后加入一个链表（即Card）
        bool add(int type);
        bool remove(int index);
        bool Order();                             //排序

        Card* get_from_index(int indexs);        //由Index得到卡片 

        int get_num(int type);//"00"  ,"01"等等卡片类型  的数目00 表示全部

};
#endif
