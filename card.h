#ifndef CARD_H_H_H_
#define CARD_H_H_H_ 

class Card
{
    public:
        int id;          
        char *effect_string;

        Card(int id,char *effect_string);   
};
#endif 
