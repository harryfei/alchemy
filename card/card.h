#ifndef CARD_H_H_H_
#define CARD_H_H_H_

#include <string>
class Card
{
    public:
        int id;
        //char *effect_string;
        std::string script_name;

        Card(int id,std::string script_name);
};
#endif
