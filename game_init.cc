#include "game_init.h"
#include <lua.hpp>
#include <string>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include "card/card_manager.h"
#include "utils/file.h"

void load_lua_scripts(lua_State *L)
{
    typedef std::vector<std::string> string_vector;

    CardManager *card_manager=CardManager::get_instance();
    string_vector names = get_files("scripts","lua");
    for(string_vector::iterator name = names.begin();
            name != names.end();++name)
    {
        int id = atoi(&(*name)[4]);
        std::cout<<"Init:add card "<<id<<std::endl;
        luaL_dofile(L, ("scripts/"+*name).c_str());
        card_manager->add_card(id,*name);
    }
}
