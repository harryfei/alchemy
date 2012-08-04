#include "card.h"
Card::Card()     //初始函数
{
    type = 0x00;
    isSame = false; 
}


void Card::Create(int type)     //创建函数  +++++++++++++++++++++++++++++++++
{ 
    this.Type = type;
    isSame = false; 
}

void Card::SetSame(bool is)    //设置相同型
{
    this.isSame = is; 
} 

