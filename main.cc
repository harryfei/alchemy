#include "game_manager.h"
#include "screen_manager.h"
#include "unistd.h"
#include "card/card_manager.h"

void init_cards()
{
    CardManager *card_manager=CardManager::get_inance();
    card_manager->add_card(1,"card1.lua");
    card_manager->add_card(2,"card2.lua");
    card_manager->add_card(3,"card3.lua");
    card_manager->add_card(4,"card4.lua");
    card_manager->add_card(5,"card5.lua");
    card_manager->add_card(6,"card6.lua");

}

int main(int argc, char *argv[])
{

    init_cards();
    GameManager game_manager;
    ScreenManager screen_manager;

    return screen_manager.loop(argc, argv);
    //return 1;
}

