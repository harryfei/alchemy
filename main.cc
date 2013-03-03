#include "game_manager.h"
#include "screen_manager.h"
#include "network_manager.h"

void init(){
    auto player_manager = PlayerManager::get_instance();
    auto player = player_manager->add(1);
    auto other = player_manager->add(2);
}
int main(int argc, char *argv[])
{
    bool is_server = false;
    if (argc>1){
        is_server = true;
    }
    //The order must be network > screen > game.
    //this is because the signal slot execute order.
    init();
    NetworkManager network_manager;
    network_manager.init(is_server);
    ScreenManager screen_manager;
    GameManager game_manager;

    int ret = screen_manager.loop(1,argv);
    network_manager.destory();
    return ret;
}

