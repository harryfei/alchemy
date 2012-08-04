#ifndef CARD_H_H_H_
#define CARD_H_H_H_
class Card
{
    public:
        int type;               //卡片类型00，空卡，10，11,12，13元素卡，21，22,23配方卡，
                            //30,31,31效果卡
        //int status[100][100]; 
        bool isSame;            //是否相同型

        Card();     //初始函数
        void  Create(int type);     //创建函数  +++++++++++++++++++++++++++++++++
        void SetSame(bool is);    //设置相同型 
};
#endif

