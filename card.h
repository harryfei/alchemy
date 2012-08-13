#ifndef CARD_H_H_H_
#define CARD_H_H_H_

#include <string>
using namespace std;
class Card
{
    public:
        int id;          
        string effect_string;

        Card(int id,string string effect_string);   
};
#endif 
